# Producers

## 1. Overview

Producers write data to topics (which are made of partitions).

* Producers know to which partition to write to (and which Kafka broker has it).
* In case of Kafka broker failures, Producers will automatically recover.
* This is how scalability is achieved - topic is divided into partitions, one or many producers put messages in each
  partition.

## 2. How is data sent

When we send the data:

1. The producer will serialize the key and the value objects to byte arrays so they can be sent over the network.
2. Next, if you did not specify the partition, the data is sent to a partitioner.
3. Then the producer knows which topic and partition the record will go to, so it adds the record to a batch of records
   that will also be sent to the same topic and partition.
4. A separate thread is responsible for sending those batches of records to the appropriate Kafka brokers.
    * This is the producer background I/O thread (`kafka-producer-network-thread`).
    * It does all the producer's network work:
        * Takes full batches from memory and sends to the brokers.
        * Reads the brokers' responses.
        * For each completed record, calls that record's callback (if any callback was specified).
5. When the broker receives the messages, it sends back a response.
    * If the messages were successfully written to Kafka, it will return a `RecordMetadata` object with the details.
    * If the broker failed, it will return an error. When the producer receives an error, it may retry sending the
      message a few more times before giving up and returning an error.

```
                 +--------------------------------------------+
                 |                +-----------------------+   |
                 |                |                       v   v
                 |                |              +--------------------+
                 |                |              |   ProducerRecord   |
                 |                |              | +----------------+ |
                 |                |              | |     Topic      | |
When successful, |If can't retry, |              | +----------------+ |
return metadata  |throw exception |              | |  [Partition]   | |
                 |                |              | +----------------+ |
                 |                |              | |     [Key]      | |
                 |                |              | +----------------+ |
                 |                |              | |     Value      | |
                 |                |              | +----------------+ |
                 |                |              +--------------------+
                 |                |                         |
                 |                |                         | Send()
                 |                |                         |
                 |   +- - - - - - | - - - - - - - - - - - - | - - - - - - - - - - - +
                 |                |                         v
                 |   :            |                  +------------+                 :
                 |                |                  | Serializer |
                 |   :            |                  +------------+                 :
                 |                |                         |
                 |   :            |                         v                       :
                 |                |                  +-------------+
                 |   :            |                  | Partitioner |                :
                 |                |                  +-------------+
                 |   :            |                         |                       :
                 |                |               +---------+----------+
                 |   :            |               v                    v            :
                 |                |       +---------------+    +---------------+
                 |   :            |       |    Topic A    |    |    Topic B    |    :
                 |                |       |  Partition 0  |    |  Partition 1  |
                 |   :           / \   Yes| +-----------+ |    | +-----------+ |    :
                 |           < Retry? > ->| |  Batch 0  | |    | |  Batch 0  | |
                 |   :           \ /      | +-----------+ |    | +-----------+ |    :
                 |                ^       | |  Batch 1  | |    | |  Batch 1  | |
                 |   :            | Yes   | +-----------+ |    | +-----------+ |    :
                 |               / \      | |  Batch 2  | |    | |  Batch 2  | |
                 +------------< Fail? >   | +-----------+ |    | +-----------+ |    :
                                 \ /      +---------------+    +---------------+
                     :            ^               |                    |            :
                                  |               +---------+----------+
                     +- - - - - - | - - - - - - - - - - - - | - - - - - - - - - - - +
                                  |                         v
                                  |                .-----------------.
                                  |               (   Kafka broker    )
                                  |                '-----------------'
                                  +-------------------------+
```

Redraw from https://www.oreilly.com/library/view/kafka-the-definitive/9781491936153/.

## 3. Different approaches

Method `send()` returns a `Future` object, so you can choose an approach:

* Fire and forget - just leave it as-is. The message will be placed in a buffer and sent in a separate thread, but you
  don't know if it this was successful.
* Synchronous send - invoke `get()` on the `Future` object.
    * The tradeoff is the performance - there could be a 2ms to a few seconds wait depending on how busy the Kafka
      cluster is.
    * You can get both retryable and non-retryable exceptions. The retry policy is configurable.
* Asynchronous send - invoke `send()` with a callback function.
    * Callbacks need to implement Kafka `Callback` interface.
    * The callbacks are invoked in the internal producer background I/O thread, so:
        * They are invoked in sequence, so they run in the order the records were sent.
        * When the thread is executing them, it is not sending data, so do not perform any lengthy, blocking operations.

## 4. Configuration

### 4.1 Producer Acknowledgements (ACKs)

Producer can choose to receive acknowledgement of data writes:

* `acks = 0`:
    * Producer won't wait for acknowledgement (possible data loss).
    * Highest throughput possible, the producer can send messages as fast as the network supports, no waiting for any
      response from any server.
* `acks = 1`:
    * Producer will wait for leader acknowledgement (limited data loss).
    * If there is an error (e.g. leader crashed and a new one has not been elected yet), it will receive an error
      response and can retry sending the message.
    * The messages can still be lost if they were acknowledged, but the leader crashed and there was no replication.
* `acks = all`:
    * Producer will wait for acknowledgements from all - leader and in-sync replicas.

Since Kafka 3.0 the default setting is `acks = all`.

#### Why `acks = all` can sometimes hurt

In Kafka, we define the end-to-end latency - measured between producing a record and consuming it.

In the normal, day-to-day functioning, when producer does not meet its limits, the `acks` setting does not affect the
end-to-end latency.

There can be multiple problems with `acks = all`:

* **In-flight requests** - at most N unanswered requests per broker (`max.in.flight.requests.per.connection`, 5 by
  default). If the replication is slow, the responses will be slow, producer reaches the cap and waits.
* **Memory** - records waiting to be sent sit in a buffer (`buffer.memory`). If the producer falls behind and the buffer
  fills, `send()` blocks in your thread and after `max.block.ms` it throws.

So there could be a problem when responses are slow enough to hit the limits:

* Throughput is hurt - less records are finally produced per amount of time.
* Producer latency increases.
* End-to-end latency increases.

### 4.2 Timings

```
+---------------------+-------------------+-------------+-----------------------+---------------------------+
|                     |                   |             |                       |                           |
|o----max.block.ms----●                   |             |                       |                           |
|                     v                   |             |                       |                           |
|                     o-----linger.ms-----o             |                       |                           |
|                     |                   v             |                       |                           |
|                     |                   o-------------●. . . . . . . . . . . ..                           |
|                     |                   |             |                       v                           |
|                     |                   |             o----retry.backoff.ms---o---request.timeout.ms---●  |
|                     |                   |             ^. . . . . . . . . . . . . . . . . . . . . . . . .  |
|                     | New timeout       |             |                       |                           |
|         .---------------------------------------------------------------------------------------.         |
|         (        delivery.timeout.ms >= linger.ms + retry.backoff.ms + request.timeout.ms       )         |
|         '---------------------------------------------------------------------------------------'         |
|       send()        |     Batching      |    Await    |        Retries        |         Inflight          |
|                     |                   |    send     |                       |                           |
+---------------------+-------------------+-------------+-----------------------+---------------------------+
```

There are two main timeouts:

* `max.block.ms`
    * **How long the producer may block when calling `send()` and when explicitly requesting metadata via
      `partitionsFor()`.**
    * This may block when producer buffer is full or when metadata is not available.
    * Timeout is thrown when this is reached.
* `delivery.timeout.ms`
    * **The `send()` call already returned the `Future` object, the record is ready for sending = it is placed in a
      batch**.
    * This is the time from the record ready for sending until either broker responds (**the acknowledgement arrives**)
      or the client gives up, including time spent on retries.
    * This needs to cover:
        * `linger.ms` - the record is waiting in the batch. `KafkaProducer` will send a batch either when it is full or
          when this time is reached. **By default it will send as soon as there is a sender thread. Setting this to a
          small value > 0 increases latency a little and significally increases throughput - smaller overhead per
          message and compression, if enabled, is much better.**
        * `request.timeout.ms` - each request is waiting for the acknowledgement.
        * Any retries and pauses between them (`retries` and `retry.backoff.ms`).

This means that:

* **The producer handles the retries for you, there is no point in handling retires within your own application logic.
  Focus on handling non-retryable errors.**
* **The producer will keep trying util the `delivery.timeout.ms` is reached (unless you limit or turn off retries).**

## 4.3 Batching

Setting `batch.size` controls the amount of memory in bytes that will be used for each batch. Setting too large value
will not delay in sending messages because there is also `linger.ms` or, if not set, the producer will send even
one-message batches. However, it will use more memory.

### Ordering guarantees

**Apache Kafka preserves the order of messages within one partition.**

