# Key Technologies

Handwritten notes from [Hello Interview, *System Design in a
Hurry*](https://www.hellointerview.com/learn/system-design/in-a-hurry/key-technologies). Back
to [System design](../system_design.md).

## KT1 Core database

- Important: NoSQL and SQL databases overlap in many areas, so don't delve into details by comparing them. Most can do
  both relationships and handle documents etc.
- Instead focus on choosing one and justifying the choice, e.g. Postgres ACID properties.

### KT1.1 Relational databases

- You usually choose it.
- You get joins, transactions and indexes.

### KT1.2 Non-relational databases

Types:

- key-value (Redis, DynamoDB)
- document (MongoDB, Couchbase, Firestore (GCP))
- column-family (wide-column) (Cassandra, Bigtable (GCP))
- graph (Neo4j)

Facts:

- Flexible data models (relational databases can also do that with JSON columns).
- Scalability: horizontal (relational databases can do sharding).
- Big data and real-time web apps (10ks of writes a second).

Why NoSQL is recommended for many writes a second:

- Cassandra:
    - Spreads writes across many machines on its own, each row has a partition key and this decides which store to
      choose. With a relational database you either have one that takes all writes or do sharding which is manual work.
    - A write is cheap, it is only a write to an in-memory table and to the log on the disk. Then the in-memory table is
      written out to sorted data files on disk, then the log can be dropped. The write is cheap because it's only append
      at the end of a file plus an insert in memory. No joins, no transactions. There is still a compaction process
      doing cleanup in the background.
    - Drawbacks: you design tables from the queries. Having 100ks of IoT sensors sending a reading in each second and
      reading this as "readings of X device between 10:00 and 11:00", you partition per device sorted by time. This is
      well spread, BUT any other query will be expensive.
- Redis:
    - The data is in the memory, it never waits for the disk. Readind RAM takes about 100 ns, reading SSD - 100
      microseconds. Writing to disk in background.
    - One thread runs all the commands, one after another. No locks, no thread switching. Each command is atomic for
      free.
    - Operations are simple - most work on one key, in constant or logarithmic time.
    - An event loop serves all connections - most of the request's time is spent waiting on the network, not working, so
      the event loop makes sure the thread only spends time on the working part. This works because each piece of work
      is really short, e.g. one request spend 0,5ms travelling, but creating the answer in redis takes 1-5 microseconds.
      So instead of 10,000 threads handling connections and doing work (mostly asleep) one thread in the event loop only
      checks which connections are ready to handle (all data to read is there) and then and processes them. It is never
      idle while there is work. Good analogy - waiter serving 20 tables; he would not be able to do that if he waited in
      each table until guests finish eating.
    - Drawbacks:
        - One core per instance. To have more cores, you need to run a Redis cluster which splits the keys across
          instances.
        - One slow command blocks everyone. For example operation on a huge collection or scal of all keys.

## KT2 Blob storage

- Large unstructured blobs of data (images, videos, other files).
- Amazon S3, Google Cloud Storage.
- Store data in there and a pointer in the main database (usually relational).
- Diagram: the user calls the server, the server writes to the core database (id, owner, name, URL), the URL points to
  S3, and the user downloads the file through a CDN that reads from S3.

Client wants to upload:

1. Order a presigned URL from the server.
2. The server returns it and saves it in the database.
3. The user uploads to that URL.
4. Blob storage notifies the server that the upload finished.

Facts:

1. Very durable, scalable: Amazon covers it.
2. Much lower cost than database storage.
3. Secure: encryption in transit and at rest.
4. Upload/download directly for the client using presigned URLs.

## KT3 Search optimized database

- Use when required to provide full-text search AND the primary database is not enough.
- Alternatives first: GIN indexes in Postgres, which support full-text search.

Techniques:

1. Inverted indexes: data structures mapping from words to the documents that contain them.
2. Tokenization: breaking a text into individual words. Then you can build the inverted index.
3. Stemming: reducing to the root form (running, runs → run).
4. Fuzzy search: usually edit distance calculation allows finding results that are not the exact matches.
5. Scaling: add more nodes and shard data across them.

## KT4 API Gateway

Responsibilities:

- Routes requests to the right services.
- Sometimes also:
    - handles authentication,
    - handles rate limiting,
    - handles logging.

Examples:

- AWS API Gateway
- Kong
- nginx or Apache web server

## KT5 Load balancer

- High traffic.
    - So: distribute among multiple machines (horizontal scaling).
- L4 vs L7 load balancer: check the [Core Concepts notes](./core_concepts.md), *CC1.3 Load balancing*.
- Beware: when having in-memory caches per key (e.g. per firm or per user ID), think about routing each key to the same
  instance with an L7 load balancer (hash-based routing on the key; sticky sessions are the per-user case). Otherwise
  the cache will be re-created in each instance the request goes to.

Examples:

- AWS Elastic Load Balancer
- NGINX
- HAProxy

## KT6 Queues

- Buffer for bursty traffic: queues can be used to manage surges in requests. A queue buffers them, allowing the system
  to process at a manageable rate.
- Distribute work across a system: the tasks can be put in a queue, and then worker nodes can pull and execute them.
- (Nabrdalik: "use partitioning to reduce lock contention") Use Kafka topics to execute multiple tasks in parallel, but
  at the same time sequentially for a single entity, e.g. multiple steps after creating an account, with the
  partitioning key account id. See [Events and publishing](../../architecture/events_and_publishing.md).
- Durable buffer.
- Consumer pulls at its own pace (backpressure).

### Message ordering

- Kafka: guaranteed order within a partition (with some exceptions during rebalances).
- SQS standard: no order, a message can arrive twice.
- SQS FIFO: the message group ID is like the key in Kafka.
- RabbitMQ: one consumer in one queue is ordered. Split work into several queues by key.
- Google Pub/Sub: order only within an ordering key, which has to be switched on for a subscription.

### Scaling and backpressure

- Scaling with partitions: queues can be partitioned across multiple servers.
- Backpressure: produce slower, or even reject accepting messages, when consumption is not catching up.

### Where queues don't fit

- Especially where the load can be handled directly and the answer is needed within milliseconds, e.g. reading a page
  or checking a price.

## KT7 Streams / event sourcing

### Event sourcing

- Technique where changes in application state are stored as a sequence of events. These events can be replayed to
  reconstruct the app's state at any point in time.
    - Detailed audit trail.
    - Reverse or replay transactions.
- Keeping events allows real-time processing, auditing, rolling back changes, reconstructing state (e.g. at a bank).

### Streams

- Use case: large amounts of data in real time. With a stream processing system you can process them in real time to
  update analytics.
- Support multiple consumers reading the same stream. This is usually the publish-subscribe pattern.

### Why Kafka might not be a good choice for event sourcing

- No reading by entity: you want all events for a single account, but they sit there on a partition with thousands of
  other events. An event store (EventStoreDB) or even a Postgres table with the right indexes returns this directly.
- No check when appending: cannot do "add event if version is 42". EventStoreDB has this, Postgres naturally too
  (optimistic concurrency).
- Retention: Kafka's primary purpose is not keeping data forever. The two policies, compact or delete, are more natural
  to it.

### Snapshots

- A long history of events makes loading an entity slow.
    - So: save a snapshot from time to time; the current state is the last snapshot + the events since it.
- Snapshots make loading fast; they do not replace keeping the events.

## KT8 Distributed locks

- You can do locking in a traditional database, but these locks are not suited for long-term locking.
- You still can use rows in a relational database and some atomic, super fast locking query like `UPDATE ...`.
- BUT:
    - This will work until there are more than in the order of 10k such writes a second.
        - So: past this, either partition or use Redis, which keeps data in memory.
    - Having a table that is updated thousands of times a second creates a lot of dead tuples, so tune autovacuum.
    - The updated columns should not be indexed; then it is a HOT update, staying on the same page and not touching the
      index.
- However, using Postgres here has advantages:
    - locking and modification in one transaction.
- Alternatives to Postgres: a distributed key-value store like Redis. Updates and even scripts in Redis can be executed
  atomically.
- Don't forget about setting the lock expiry time!

## KT9 Distributed cache

Use cases:

- Save aggregated metrics: computation is expensive, so store them in a distributed cache (reduction of latency at the
  cost of consistency: the cache is refreshed e.g. hourly).
- Reduce database queries.
- Speed up long queries.

Consider:

- Eviction policy:
    - Least recently used (LRU).
    - First in, first out.
    - Least frequently used (LFU): a new element enters with a low count, so it cannot replace elements with e.g. at
      least 10 accesses and is evicted first.
        - So: you need to count misses too (accesses to elements not in the cache). Caffeine (TinyLFU) and Redis
          support it.
- Cache invalidation.
- Cache write:
    - Write-through: save to the database and the cache in one process. Consistency, but slower.
    - Write-around: save to the database only; save in the cache when reading.
    - Write-back: save to the cache, then to the store asynchronously.
    - Cache-aside: check the cache; if missing, load from the database and write to the cache.
        - A write saves in the database and removes from the cache.

### How to store the data, Redis for example

- Redis itself is a key-value store.
- The value can have different types:
    - String: often serialized JSON.
        - Storing a lock.
        - Storing a user profile.
    - HashMap: fields of one object.
        - This is better than storing JSON, because you can issue editing of one value in the map. No need to read the
          entire value; Redis will manage the collection.
    - List: ordered list, fast on both ends.
    - Set: unique members, no order.
    - Sorted set: unique members ordered by score.
    - Geo: points with coordinates.
    - HyperLogLog: approximate count of unique items.
