# Exactly once

Why:

* When you have events with IDs, consumer apps can deduplicate.
* When you make aggregates, it will be harder to spot duplicates inside ("I got sum 9: is this 1 a new event, or have I
  already summed it?").
* So: exactly once = idempotent producer (only with `acks=all`) + transactions.

## Idempotent producer

### Duplicated message

1. The leader receives a record.
2. The record is replicated to the followers.
3. The high-water mark is moved, consumers can read.
4. The broker crashes **before** returning to the producer.
5. The producer, after some time of waiting, will re-send.
6. The new message will get to the new leader = duplicate.

### Inversion of the order because of retrying

1. The producer sends some batches and waits for the responses (`max.in.flight.requests.per.connection > 1`).
2. Batch #1 fails.
3. Batch #2 is acknowledged.
4. Producer retries Batch #1 and this time it is acknowledged.
5. The batches have been reordered.

### The mechanism

* Each message has a producer ID, called PID, and a sequence number.
* PID + sequence + partition + topic = the unique ID of a message.
* Brokers track the five last batches produced to every partition of the broker, per producer ID (sequence numbers are
  checked per batch).
* `max.in.flight.requests.per.connection = 5`; should not be higher.
    * So: the five in-flight requests match the broker's window of five batches.

### How it fixes duplicates (the sequence was already tracked):

* The broker returns an error.
* The producer logs it but **does not** throw.

### How it fixes reorders

Getting a wrong sequence (sequence too high):

* When broker gets `Batch #2` before `Batch #1`, it returns `OutOfOrderSequenceException` error (not thrown by the
  producer).
* Producer logs this error.
* Producer retries the batches in order.

### How it (does not) fix the holes in batches

Again getting a wrong sequence:

* Broker expects `100`.
* Producer sends `121`.
* Broker returns error.
* This time the producer sees that it had given up the batches 100-120 (expired), so no luck - they will never come. It
  does two things:
    * Raises its epoch and restart the sequence from 0. Broker will treat it as a fresh start.
    * Adds that those sends fail in their callbacks, so the application can see it.
* Some records are lost for good.

### Possible scenario: producer restart

1. One producer fails.
2. A new one is spun up somehow, maybe manually, maybe automatically (Kubernetes).
3. The new one **gets a new ID**.
4. If the new one sends the same message, it will be duplicated, because it has a different composite ID.
5. This is also the case if a producer freezes and comes back!

### Possible scenario: broker failure with a new leader elected

1. A broker fails.
2. The controller elects a new leader in the partitions the failed broker was leader of.
3. The producer wrote to broker A, topic T, partition 0.
4. Now the producer writes to broker B.
5. B knows the last 5 batch IDs, because they are updated on replication (so each broker has its own in-memory state).
6. So: when B becomes the leader, it knows the latest sequence numbers (assuming `acks=all`, which is required).

### Possible scenario: broker failure with the old leader comming back

1. The old leader restarts.
2. No in-memory state.
3. OK: it stores the state in a file and then reads it on startup.
    * Snapshot on every segment end and on closing.
    * Recovery from the logs for things that did not go into a snapshot yet.

### Limitations

* This covers retrying inside the producer logic.
* Calling `send()` twice won't be covered.
* So: do not catch producer exceptions and retry yourself.
