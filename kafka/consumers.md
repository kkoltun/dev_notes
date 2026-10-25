# Kafka Consumers

## 1. Consumers

Consumers read the data from a topic identified by a name (**pull model**).

* Consumers can read from one to many partitions.
* Consumers automatically know which broker to read from.
* In case of broker failures, consumers know how to recover.
* Data is read in order from lower to higher offsets **within each partition**. So if consumer reads from many
  partitions, the order is maintained **only within each partition**. There is no ordering guarantee across partitions.
* Consumers use deserializers to transform binary key and value into objects/data.
* Kafka comes with a set of Common Deserializers.
* **The type of data does not change during the topic lifecycle.** You usually create a new topic instead.

## 2. Consumer Groups

All the consumers in an application read data as consumer groups.

* Each consumer within a group reads from one or more distinct partitions. This means that they **do not share
  partitions**.
* If you have more consumers than partitions, some of them will be inactive (this is normal).
* You can have multiple consumer groups on the same topic (eg. multiple services reading from the events topic).
* To create distinct consumer groups, use the consumer property `group.id`.

**The main way we scale data consumption from a Kafka topic is by adding more consumers to a consumer group.** This is
why it is a good idea to create topics with a large number of partitions.

## 3. Consumer Offsets

The consumer offsets are recorded by Kafka to know, how far is each consumer group in each topic.

* When a consumer in a group has processed data received from Kafka, it should be **periodically** commiting the
  offsets. This makes the Kafka broker write to `__consumer_offsets` topic.
* Kafka keeps offsets for each tuple `(topic, partition, consumer group)`.
* If a consumer dies, it is able to read back from where it left off thanks to the comitted consumer offsets.

## 4. Consumer Groups and Partition Rebalance

This is needed when:

1. You add a new consumer to the group and it starts consuming messages from partitions previously consumer by another
   consumer.
2. A consumer shuts down or crashes, it leaves the group and the partitions consumed by it need to be handled by one of
   the remaining consumers.
3. Topic is modified - e.g. new partitions are added.

Rebalance is **moving partition ownership from one consumer to another**.

In the rebalance there is always:

* A leader - the first consumer that joined the group.
* The leader will get all consumers in the group from the `GroupCoordinator`.
* The leader is responsible for assigning partitions (`PartitionAssignor`).
* Ultimately, the leader sends the list of assignment to the `GroupCoordinator`, which sends this information to all the
  consumers.

### 4.1 Eager rebalances

```
       All partitions revoked                              New partitions assigned
                 ^                       | Synchronization barrier          |
                 |                       |                                  v
Consumer A ──[1]─▶ - - - - - - - - - - - | - - - - - - - - - - - - - - - - - [1]──────▶
                     \            ^      |  \                         ^
Consumer B ─[2]─▶ - - \ - - - - -/- - - -| - \ - - - - - - - - - - - /- - - - [2]─────▶
                 \     \        /    ^   |    \    \                /     ^
Consumer C [3]─▶ -\- - -\- - - / - -/- - | - - \ - -\- - - - - - - / - - -/- - - [3]──▶
              \    \     \    /    /   ^ |     \    \    \       /     /     ^
               \    \     \  /    /   /  |      \    \    \     /     /     /
                \    \     \/    /   /   |       \    \    \   /     /     /
                 ▼    ▼     ▼   /   /   /|        ▼    ▼    ▼ /     /     /
  ───────────────────────────────────────┼─────────────────────────────────────────────▶
  Group coordinator (broker side)        |
```

Redraw from https://www.oreilly.com/library/view/kafka-the-definitive/9781491936153/.

Flow:

1. All consumers stop consuming and give up the ownership of all partition (solid horizontal line becomes dashed).
2. `JoinGroup`: All consumers send the `JoinGroup` requests to the `GroupCoordinator` (left part, arrows down).
3. `JoinGroup` response: The coordinator answers **AFTER** every member has asked (left part, arrows up).
    1. The leader gets the full list of members and the topics each reads.
    2. The others get only the information about the leader and the number of this round (the generation).
4. The synchronization barrier - everyone is in, nobody owns anything.
5. `SyncGroup`: All consumers send the `SyncGroup` requests to the `GroupCoordinator` (right part, arrows down).
    1. The leader sends its plan (`A: [1], B: [2], C: [3]`).
    2. The others send enmpty requests.
6. `SyncGroup` response: The consumers get their assignments.
7. Why the planning happens in the consumer - it is configured by consumer's setting `partition.assignment.strategy`.

Consequences: there is a short window of unavailability of the entire consumer group, the length depends on the size of
the consumer group and other configration values.

The result of the rebalance above is the same partition assignment. It still needed to pause. The cooperative rebalance
(mentioned below) would have paused nothing here.

### 4.2 Cooperative (incremental) rebalances

```
                                              Partition 3 revoked                       Partition 3 assigned
                                                           ^  | Synchronization barrier                  |
Consumer A ==[1|3]===================^===================>[1]=|==================^===================^===|=>
                 \                  /\                  /    \|                 /\                  /    |
Consumer B =[2]===\================/=^\================/=^====|================/=^\================/=^===|=>
                   \ \            / /  \ \            / /     |\ \            / /  \ \            / /    v
Consumer C  - - - - \ \ - - - - -/-/-^- \ \ - - - - -/-/-^- - | \ \ - - - - -/-/-^- \ \ - - - - -/-/-^- [3]>
                     \ \ \      / / /    \ \ \      / / /     |  \ \ \      / / /    \ \ \      / / /
                      \ \ \    / / /      \ \ \    / / /      |   \ \ \    / / /      \ \ \    / / /
                       \ \ \  / / /        \ \ \  / / /       |    \ \ \  / / /        \ \ \  / / /
                        v v v/ / /          v v v/ / /        |     v v v/ / /          v v v/ / /
          ----------------------------------------------------+-------------------------------------------->
                   \___________________ ____________________/ |  \___________________ ___________________/
                                      1st rebalance           |                 2nd rebalance
                                             Group coordinator (broker side)
```

Redraw from https://www.oreilly.com/library/view/kafka-the-definitive/9781491936153/.

Flow:

1. The consumers DO NOT give up their parition ownerships.
2. First rebalance (left part):
    1. `JoinGroup`: All consumers send the `JoinGroup` requests to the `GroupCoordinator` (left part, arrows down).
    2. `JoinGroup` response: The coordinator answers **AFTER** every member has asked (left part, arrows up).
        1. The leader gets the full list of members and the topics each reads.
        2. The others get only the information about the leader and the number of this round (the generation).
    3. `SyncGroup`: All consumers send the `SyncGroup` requests to the `GroupCoordinator` (right part, arrows down).
        1. The leader sends its plan (`A: [1], B: [2], C: []`).
        2. The others send empty requests.
    4. `SyncGroup` response: The consumers get their assignments.
3. Second rebalance (right part):
    1. `JoinGroup`: A says it owns 1, B says it owns 2, C owns none.
    2. `JoinGroup` response: the leader sees that partition 3 belongs to no consumer.
    3. `SyncGroup`: the leader's plan `A: [1], B: [2], C: [3]` goes to the coordinator.
    4. `SyncGroup` response: A owns 1, B owns 2, C owns 3.

Facts:

* This type of rebalance involves reassigning only a small subset of the partitions from one consumer to another.
* This approach allows other consumers to continue processing records from all partitions that are not being reassigned.
* This takes two or more phases.

The difference here is:

* In **eager**: the consumers wait for the `JoinGroup` response with no assignments.
* In **cooperative**: the consumers wait while reading their partitions.

## 5. Heartbeat

* The consumers maintain membership in a consumer group and ownership of the partitions by sending `Heartbeat` requests
  to a Kafka broker.
* The requests are done by a background thread of the consumer.
* If the consumer stops sending heartbeats for long enough, the session will timeout and the group coordinator will
  consider it dead and trigger a rebalance.
* If the consumer crashes, it will take the group coordinator a few seconds without heartbeats to decide it is dead and
  trigger the rebalance.

## 6. Static group membership

When consumer leaves a consumer group, the paritions that were assigned to it are revoked. When it rejoins, it is
assigned a new member ID and a new set of partitions through the rebalance protocol.

It works this way **unless** you set `group.instance.id`, this makes the consumer a **static** member of the group.

1. When it first joins a consumer group, it is assigned a set of partitions as usual.
2. When it shuts down, it does not automatically leave the group - it remains a member of if until its session times
   out.
    1. If the session times out:
        1. The coordinator removes it from the group and starts a rebalance. Its partitions go to the remaining
           consumers.
        2. When it rejoins, it joins the group as a new member, this involves a rebalance, where it may get different
           partitions (depending on the produced plan).
    2. If the session does not time out, when it rejoins, it is recognized with its static identity and is reassigned
       the same partitions it previous held without triggering a rebalance.

**The `group.instance.id` has to be unique within a consumer group.**

Possible use-case - consumers with expensive caches (local state built from their partitions). For example:

1. Partitioning by customer.
2. Each consumer keeps a cache of customer balances and it takes a lot to create one. The caches do not overlap.
3. It is better to wait longer until the consumer rejoins than to rebuild the cache somewhere else.

Smaller use-cases:

1. Rolling deploys - restarting 10 consumers would trigger 20 rebalances with eager rebalance (10 leaving, 10 joining).
2. Fewer duplicates - no handover of the partition.

Drawback - while the static member is away, but it's session has not timed out yet, nobody reads its partitions.

Important configuration value - `session.timeout.ms`:

1. Long enough to cover a restart.
2. Short enough that a consumer that is reall dead doesn't leave its paritions unread for too long.

## 7. Reading data to keep alive

Apart from heartbeat, which is done in the background, **the consumers must keep polling Kafka or they will be
considered dead and the partitions they are consuming will be handed to another consumer in the group**.

This is controlled with `max.poll.interval.ms`.

This is very important because:

1. The consumer can be stuck doing some long processing.
2. The heartbeats flow the entire time, but after `interval.ms` the consumer leaves the group and its partitions go to
   others.
3. When it finally commits, the commit is rejected because it no longer owns those paritions. The new owner then
   processes the same records again, which is a duplicate.

Possible fixes:

1. Faster processing.
2. Bigger `max.poll.interval.ms` value.
3. Polling for less records at once.

## 8. Calling `poll()`

The first `poll()` call with a new consumer:

* Finds the `GroupCoordinator`.
* Joins the consumer group.
* Receives the partition assignment.
* If a rebalance is triggered, it will be hanlded inside the poll as well.

The `poll(Duration)` adheres to the timeout restriction and, at the same time, it has different jobs, e.g. getting
metadata from Kafka. So if it times out before getting the data, it just return.

## 9. Config values by problem

### 9.1 When a consumer is considered alive

* `max.poll.interval.ms` - time during which the consumer can go without polling before it is considered dead.
* `session.timeout.ms` and `heartbeat.interval.ms` - described above, heartbeat interval must be lower than session
  timeout and is usually one-third of the timeout value.

### 9.2 Timeouts

* `default.api.timeout.ms` - timeout taht will apply to (almost) all API calls. In the `poll()` method, you are required
  to set an explicit timeout.
* `request.timeout.ms` - max timeout the consumer will wait for a response from the broker.

### 9.3 Offset reset

The `auto.offset.reset` controls the behavior when:

* Consumer starts reading a partition which it doesn't have a comitted offset (kept in a topic in Kafka).
* Committed offset the consumer has is invalid.

Values:

* `latest` - the consumer will start reading from the newest record.
* `earliest` - the consumer read all the adat in the partition, starting from the very beginning.
* `none` - exception is thrown when attempting to consume from an invalid offset.

### 9.4 Partition assignment

The `partition.assignment.strategy` controls how partitions are assigned to consumers in a consumer group.

Values:

* `Range` - assigns to each consumer a consecutive subset of partitions from each topic it subscribes to. This can end
  up with one consumer having more partitions than the other (the number of consumers does not divide the number of
  partitions of each topic neatly).
* `RoundRobin` - takes all the partitions from all subscribed topics and assigns them to consumers sequentially, one by
  one. This will end up with all consumers having the same number of partitions or with partition difference equal to
  one.
* `Sticky` - two goals:
    * Have an assignment that is as balanced as possible.
    * In case of a rebalance, leave as many assignments as possible in place.
* `Cooperative Sticky` - the assignment is same as above, but supports cooperative rebalances in which consumer can
  continue consuming from the partitions that are not reassigned.

### 9.5 How much to process

The `max.poll.records` controls the max number of redords that a single call to `poll()` will return. This is needs to
suit the `max.poll.interval.ms` value.

### 9.6 Latency vs throughput

The `fetch.min.bytes` (default 1 byte):

* Controls the minimum amount of data that the consumer wants to receive from the broker when fetching records.
* If a broker received a request for records from a consumer but the new records amount to fewer bytes, it will wait.
* This reduces the load on both the consumer and the broker.

The `fetch.max.wait.ms` (default 500 ms):

* Controls the wait caused by the `fetch.min.bytes` setting.
* So this is some extra latency in case there is not enough data flowing to the Kafka topic to satisfy the minimum
  amount of data.

So setting `fetch.min.bytes = 1MB` and `fetch.max.wait.ms = 100ms`: when Kafka receives a fetch request from the
consumer and will respond with data either when it has 1 MB of data or after 100 ms, whichever happens first.

So this is balancing latency vs throughput:

1. *Many small fetches* - each record comes as soon as it is available, so **low latency**. But you pay a fixed cost
   every few records, so more requests lead to more broker CPU, more network traffic and **less total throughput**.
2. *Few big fetches* - the fixed cost mentioned above is spread over many more records, so **high throughput**. However,
   there could be significant pauses waiting in the broker until the batch fills or time passes, so **latency is
   higher**.

### 9.7 Not choosing the leader

The consumer fetches data from the partition leader by default.

This can be changed with consumer setting `client.rack` and broker
`replica.selector.class=org.apache.kafka.common.replica.RackAwareReplicaSelector`.

## 10. Loading data in two phases

After we got to know the basic settings, we can get deeper into the process of loading data. There are two stages:

1. **Fetch (broker -> consumer buffer)**. The consumer sends fetch requests to the brokers that lead its partitions. The
   broker answers with record data, that consumer keeps in its local, in-memory buffer. These settings matter here:
    * `fetch.min.bytes` - the least data broker collects before it responds.
    * `fetch.max.wait.ms` - max wait for the minimum before broker answers with whatever it has (could be empty).
    * `fetch.max.bytes` and `max.partition.fetch.bytes` - cap the size of one response, in total and per partition.
2. *Hand-out (consumer buffer -> the poll () loop)**. The `poll()` method first looks at the buffer. If the buffer has
   any records, it will return them capped by `max.poll.records` and the rest stays in the buffer for the next `poll()`.
   Only when the buffer is empty, the `poll()` will fetch and wait for results or timeout. The client will also fetch in
   the background while the code processes polled batch.

## 11. Commits and offsets

**Kafka does not track acknowledgements from the consumers the way many JMS queues do. Instead it lets consumers to use
Kafka to track their position (offset) in each partition.**

**Offset commit**:

* The action of updating the current position in the partition.
* Kafka does not commit records individually, consumers commit the `last processed message + 1` they've successfully
  processed from a partition and implicitly assume that every message before the last was also successfully processed.
* Consumer sends a message to Kafka, which updates a special `__consumer_offsets` topic with the committed offsets
  per topic, consumer group and partition.
* When the consumers are healthy, nobody uses this data. A running consumer does not ask Kafka where to continue. It
  keeps its own position in memory and fetches "everything after offset X".
* The committed offset is read only when a partition gets a **new owner**:
    * After a crash.
    * On a rebalance.
    * On a restart.

What is important, by default committing an offset automatically or without specifying the exact value means committing
the offset after the last offset that was returned by `poll()`.

A few things can go wrong here:

* If the committed offset is smaller than the offset of the last message the client processed, the messages between the
  comitted and processed will be processed twice.
* Naturally, if it is larger, the messages will be lost.

Re-processing:

```
                                      Event we are processing right now
              These events will be reprocessed      |
          in case of rebalance, causing duplicates  |
                __________________/\________________|__
               /                                    v  \
+----+----+----+----+----+----+----+----+----+----+----+----+- -
| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |::::
+----+----+----+----+----+----+----+----+----+----+----+----+- -
            ^                      \___________  ___________/
            |                                  \/
            |                           Events returned
  Last committed offset                   by last poll
```

Redraw from https://www.oreilly.com/library/view/kafka-the-definitive/9781491936153/.

Lost messages:

```
           Event we are processing right now
                           |      Events returned
                           |        by last poll
                     ______|___________/\___________________
                    /      v                                \
+----+----+----+----+----+----+----+----+----+----+----+----+- -
| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |::::
+----+----+----+----+----+----+----+----+----+----+----+----+- -
                              \______________  __________^__/
                                             \/          |
                              These events will be lost  |
                                in case of rebalance     |
                                                         |
                                               Last committed offset
```

### 10.1 Automatic Commit

* Consumer commits the lates offset every `auto.commit.interval.ms`, 5 seconds by default.
* Whenever you poll, the consumer checks if it is time to commit, and if it is, it will commit the offsets it returned
  in the last poll.
* So if the interval is five seconds and after three seconds from the last commit the consumer crashed, a rebalance will
  happen and the new consumers will start consuming the partitions from the last committed offset - the one that is
  three seconds old.
* It is safe only when the records from the last `poll()` are processed before the next `poll()`. If they are handed to
  another thread and the loop polls again staight away, unprocessed records get committed, and a crash loses them.

### 10.2 Commit Current Offset Synchronosly

* First set `enable.auto.commit=false`.
* The most simple method is `commitSync()`, whic returns once the offset is committed or throw and exception. It retries
  until it succeeds or encounters non-retryable error.
* This commits the latest offset returned by `poll()` so if you are in the middle of processing, you risk missing the
  messages that were committed but not processed.

### 10.3 Commit Current Offset Asynchronously

* First set `enable.auto.commit=false`.
* Use `commitAsync()`. This method does not retry. Retrying the commits can be error-prone, because we could be trying
  to commit offset 2000 while at the same time there was another batch and successfully committed offset 3000!

### 10.3 Combining Synchronous and Asynchronous Commits

* You can e.g. use `commitAsync()` in the poll loop and use `commitSync()` only when shutting down.

### 10.4 Commit Specified Offset

* None of the methods above let you specify what offset you commit.
* If you are processing a big batch, you might want to commit the offset mid-processing, so a rebalance in the middle
  does not start from the beginning of the batch.
* Both methods take `Map<TopicPartition, OffsetAndMetadata>`, so you commit exactly the offsets you choose, e.g. every
  1000 records.
* **Make sure you commit the last processed offset + 1.**

## 11. Consuming Records with Speciﬁc Offsets

You use `poll()` when you want to consume messages from the last committed offset in each partition and proceed in
processing all messages in sequence.

However sometimes you want to start reading at different offset:

* `seekToBeginning(Collection<TopicPartition> tp)` and `seekToEnd(Collection<TopicPartition> tp)` are the methods to
  use.
* Warning: these methods are lazy. They only mark the partitions as `go to the end`. The actual offset is looked up at
  the next `poll()` or `position()` call.
* You can also get the offsets that were current at specific timestamps using `consumer.offsetsForTimes()`.

## 12. Exiting

1. Consumer is running `poll()`.
2. Another thread needs to call `consumer.wakeup()`. This is the only consumer method safe to call from a different
   thread.
3. Calling `wakeup()` causes the `poll()` to exit with `WakeupException` or if `consumer.wakeup()` was called not when
   the thread was waiting on the poll, the exception will be thrown on the next iteration when `poll()` is called.
4. If you have set `enable.auto.commit=false`, do a `commitSync()`.
5. Then call `consumer.close()`. This commits offsets if autocommits are enabled and then sends the group coordinator a
   message that the consumer is leaving the group.

## 13. Rebalance Listeners

This is a `ConsumerRebalanceListener` passed to `subscribe()`. It lets your code act when partitions move.

Three methods:

* `onPartitionsRevoked()`: called before your partitions are taken away. Commit what you've processed here, with
  `commitSync()` and the specified offsets from 10.4, so the new owner doesn't re-read it.
* `onPartitionsAssigned()`: called after new partitions arrive. Load any state for them here, or seek to an offset you
  keep somewhere yourself.
* `onPartitionsLost()`: called only in exceptional cases, when the partitions already belong to someone else, for
  example after the session timed out. Don't commit here, because those partitions aren't yours anymore.