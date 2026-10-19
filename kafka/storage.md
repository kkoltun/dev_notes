# Storage

**The administrator configures the a retention period for each topic. Kafka does not wait until all consumer groups read
the topic.**

* A single partition is split into segments. By default a segment is either 1 GB or one week of data, whichever smaller.
* Whichever segment the Kafka is writting to is called **active segment**.
* The active segment is never deleted. You cannot delete a segment before it is closed. If you choose to keep one day of
  logs, but each segment contains five days, then you are storing five days of data as a result.
* A closed segment is deleted only when its **newest** message is older than the retention period, so its oldest
  messages can stay well past the retention time. With a retention of one day, a segment holding messages from Monday
  to Wednesday is deleted only on Thursday, when its last message from Wednesday becomes one day old; the Monday
  messages have lived three days.
* Kafka broker will keep an open file handle to every segment in every partition, even inactive segment. This could
  be a lot of file handles opened at the same time.

## Messages and batches

Each segment is a single file containing offsets and messages:

* Messages are in exactly the same format as they were produced and as they will be sent to consumers.
    * This is optimal, because the broker can send the message to the network socket straight from the file (zero-copy),
      with no decompressing or re-encoding.
    * Batches also stay compressed all the way from producer to disk to consumer.
* Messages consist of:
    * System headers.
    * User payload:
        * Optional key.
        * Value.
        * Optional collection of headers.
* Messages are always sent in batches, even if there is only one message. This is why Kafka performs better with even a
  small amount of delay `linger.ms` that increases the chance of getting more messages in one batch.
* There is a separate batch per partition, so one produce request could contain multiple batches.
* This means that:
    * Producers that write to fewer partitions will be more efficient.
    * Compression is recommended.
    * Larger batches mean better compression.
* Message batch consist of multiple headers. There is much more information stored in batch system headers than in the
  message system headers.

## Upgrading message formats

Kafka supports upgrading message formats in the way that brokers upgraded before all the clients are upgraded:

* New brokers will understand old formats from producers.
* New brokers will know to send old formats to old brokers.
* **When new producer sends a message to the new broker and an old consumer tries to read it, the broker will need to
  convert it. This consumes CPU and memory, so watch the metrics and upgrade clients ASAP.**

## Indexes

To allow starting reading from any offset and timestamp Kafka keeps at least two indexes:

* Index for each partition mapping offsets to segment files and positions in them.
* Similar index for timestamps.

## Deleting and compaction

By default, Kafka stores messages for a set amount of time and purge messages older than the retention period. However
you might need something else:

* Storing data per customer: store one newest entity per customer, regardless of how old it is.
* Storing application state and allowing recoveries: store latest state before crash, not all changes that happened when
  running.

Two retention policies:

* **Delete** - deletes events older than retention time.
* **Compact** - stores the most recent value for each key in the topic (requires messages to have keys).

You can choose the policy using `cleanup.policy` and values `delete` and `compact`:

* `compact` - keeps the latest message for every key forever.
* `delete` - removes only basing on the age.
* `compact,delete` - keeps the latest message for every key **within the retention period**. A message older than the
  retention period will be removed even if it is the latest value for a specific key.

What is important:

* Compaction guarantees no changes in offsets and order. A consumer that reads the partition after compaction gets a
  latest value for each key.
* The active segment is never compacted or deleted.

## Deleting a message

Sometimes you must remove a latest message for a specific key - e.g. user left the platform and we need to remove their
data:

* Send a message with the specified key and `value = null`.
* Cleaner thread will first do a normal compaction and retain only the message with a null value.
* The message is called **tombstone** and is kept for a configured amount of time. Consumers can see it.
* After a certain amount of time, the cleaner thread will remove the tombstone, so give the consumers enough time to
  react to it (e.g. clear the user's database data).

There is also another way of removing messages - using Kafka Admin Client `deleteRecords` method:

* This deletes all messages before a specified offset.
* The method of deleting is setting low-water mark (record of first offset of a partition) to a specified offset.
* This prevents the consumers from records below the new low-water mark.
