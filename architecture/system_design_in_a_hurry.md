# System Design in a Hurry (Hello Interview)

Handwritten notes from [Hello Interview, *System Design in a
Hurry*](https://www.hellointerview.com/learn/system-design/in-a-hurry/introduction): the introduction, the delivery
framework and the core concepts.\

## Introduction

### What the interview is

- An ambiguously defined high-level problem.
- So: break it down into the pieces of infrastructure that you'll need to solve it.
- No single right answer.
- Navigate a complex problem.
- Reason about trade-offs, communicate thinking clearly.
- Quickly work through the basics, leaving time to show off the depth of knowledge in the deep dives.

### What is assessed

Four areas: Problem Navigation, Solution Design, Technical Excellence, Communication and Collaboration.

### Problem Navigation

- Break down the problem into smaller manageable pieces.
- Identify the most important ones.

What can go wrong:

- Not enough exploration of the problem.
- Not enough exploration of the requirements.
- Focus on uninteresting / non-relevant / trivial aspects.
- Getting stuck on one problem and not being able to move forward.
- Failing to deliver a working system.

### Solution Design

- How do you solve each piece of the problem.

What can go wrong:

- Plain lack of knowledge, insight.
- Ignoring scaling or performance considerations.
- Spaghetti design.

### Technical Excellence

- You need to know the best practices, current tech, how to apply them.

What can go wrong:

- Not knowing current tech, using deprecated tech.
- Not knowing how to apply new tech.

### Communication and Collaboration

- Communicate complex concepts, respond to feedback and questions, work together on a problem.

## Delivery Framework

**CRITICAL: First deliver a working system. Then work on non-functional requirements.**

```
                                                                                                       Primary Goal: Satisfy
                                                                                                    Non-functional Requirements
                                                                                  Primary Goal: Satisfy          │
                                                                                 Functional Requirements         │
                                                                                            │                    │
                                                                                            ▼                    ▼
┌(1)────────────┐    ┌(2)────────────┐    ┌(3)────────────┐    ┌(4)┄┄┄┄┄┄┄┄┄┄┄┄┐    ┌(5)────────────┐    ┌(6)────────────┐
│               │    │               │    │               │    ┆               ┆    │               │    │               │
│  Requirements │ ─▶ │ Core Entities │ ─▶ │     API or    │ ╌▶ ┆   Data Flow   ┆ ╌▶ │   High-level  │ ─▶ │   Deep Dives  │
│               │    │               │    │   Interface   │    ┆               ┆    │     Design    │    │               │
│               │    │               │    │               │    ┆               ┆    │               │    │               │
└───────────────┘    └───────────────┘    └───────────────┘    └┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┘    └───────────────┘    └───────────────┘
                                                                                            ▲
                                                                                            │
                                                                                ★ YOU MUST ARRIVE HERE ★
```

Redraw from https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery.

The steps, in order:

1. Requirements (5 min).
2. Core Entities (2 min).
3. API or Interface (5 min).
4. (Optional) Data Flow (5 min).
5. High level design (10-15 min).
6. Deep dives (10 min).

Capacity estimation hangs off the requirements.

### Requirements

Functional requirements:

- A prioritized list of core features.
- Top 3.

Non-functional requirements:

- System qualities that are important to the users.
- Put in context and quantified.
- CAP: consistency vs availability.
- Environment constraints.
- Scalability: peak hours, Black Friday etc.
- Read vs write ratio.
- Latency, especially for reads requiring computation.
- Durability.
- Security.
- Fault tolerance.
- Compliance.

### Core Entities

- The data central to the design.
- The data you send via the API, save in the data model.
- Create a small list, do not aim to cover 100%.

### API or System Interface

Contract between your system and its users.

- REST: HTTP verbs.
    - Default choice.
- GraphQL: lets clients specify exactly what data they want, avoiding over- and underfetching.
    - Many clients with different needs.
- RPC: action-oriented protocol, faster than REST for service-to-service communication.
    - Internal API, performance critical.

### Optional: Data Flow

- High level sequence of actions or processes that the system performs on the inputs to produce outputs.

### High level design

Boxes and arrows to represent the different components of the system and how they interact.

- Do not overthink! Design an architecture that satisfies the API and requirements.
- Stay focused! Do a relatively simple design that meets the core requirements, then layer on complexity to satisfy the
  non-functional requirements.
- When designing this, you will identify needs for adding complexity: note them for later.
- Document only a high level of the data layout.

### Deep dives

Now you have a high level design. Now you focus on:

- Meeting non-functional requirements.
- Addressing edge cases.
- Identifying and addressing issues and bottlenecks.
- Improving the design based on probes from the interviewer.

Then:

- Act proactively.
- Give room to the interviewer to ask questions and probe the design.

## Core Concepts

### CC1 Networking

#### CC1.1 Live updates

- Polling: one way.
- SSE: one way, the client makes the initial HTTP request (stateful).
- WebSockets: bidirectional, but more complex to implement (stateful).
- SSE and WebSockets could be a problem behind the load balancer (stateful).

#### CC1.2 Service to service

- gRPC where performance is critical: binary over HTTP/2, faster than JSON over HTTP.

#### CC1.3 Load balancing

- Level 7 (application level): can route basing on the request content (URL path, headers, cookies, e.g. sticky
  sessions).
    - It is an intermediary: it ends the client's connection on itself, reads each request, opens its own connection to
      a backend, and forwards the request and then the response between the two connections.
- Level 4 (transport layer): TCP level, dumber; it picks a backend once, when the TCP connection opens, and then only
  passes the bytes through without reading them.
    - So: a long-lived connection (WebSockets, SSE) stays on one backend for its whole life, at almost no cost per
      message.
    - Behind L7, a WebSocket costs two open connections per client (client side and backend side) and work on every
      frame, and routing by content gives nothing after the first request.
    - L7 balancers can handle WebSockets too (nginx, AWS ALB), so L4 is the usual fit, not the only one.
- Example: a chat with 200,000 users connected all day goes behind L4; the REST API of the same product (`/api/rooms`,
  `/api/users`) goes behind L7, because there routing by path is the point.

#### CC1.4 Geography

- New York to London is 80 ms base, before you process anything.
- So: use a CDN, regional deployments, data replicated or partitioned by geography.

### CC2 API design

- 4–5 key endpoints.
- Usually REST.
- Think of pagination, or cursor based.
- Think of rate limiting.

### CC3 Data modeling

- Relational DB:
    - Structured data.
    - Consistency.
    - Clear relationships.
- NoSQL DBs:
    - Flexible schemas.
    - Scale horizontally without joins.
- When to choose what, must know:
    - Default: PostgreSQL. It covers more than it seems: JSONB for flexible fields, full-text search up to a point.
    - Data or traffic too big for one PostgreSQL node (writes above all): NoSQL (Cassandra, DynamoDB), which spreads
      the data over many nodes by design.
    - Terabytes of files or text: object storage (S3), with pointers to the objects kept in PostgreSQL.
    - Heavy search over text: a search engine (Elasticsearch), fed from the main database; not a document database.
    - Fast lookups of data that can be lost (cache, sessions, counters, rate limits): Redis, in memory, with a time to
      live per key.
    - Example: an e-commerce shop keeps orders in PostgreSQL, product photos in S3 with their keys in the products
      table, product search in Elasticsearch updated from PostgreSQL, and sessions and the product page cache in Redis.
- When to choose what, advanced:
    - Analytics over a long history (sales by region for 3 years): a columnar warehouse (BigQuery, ClickHouse,
      Redshift); it reads only the columns a query needs, so scanning billions of rows is cheap. PostgreSQL stays for
      the live transactions.
    - Time series (metrics, sensor readings): a time-series database (TimescaleDB, InfluxDB, Prometheus for
      monitoring), built for appending by time and querying time windows.
    - Deep relationships (friends of friends of friends): a graph database (Neo4j); rarely needed, PostgreSQL with
      recursive queries often does it.
    - Geospatial (drivers within 2 km): PostGIS in PostgreSQL, or Redis geo commands for fast-changing positions.
- Design normalized, then denormalize hot paths.
- For NoSQL: design the partition key and the sort key basing on access patterns (fast single partition lookup).
    - Relational: start from the entities and relationships, normalize, answer the queries later with joins and indexes.
    - NoSQL (Cassandra, DynamoDB): no joins, so start from the list of queries and shape one table per query.
    - Partition key = what the query looks up by, so all its rows sit together on one node.
    - Sort key = the order the query wants the rows in.
    - So: two screens needing the same data in two ways = the data written twice, into two tables. Duplication is the
      normal price, paid at write time.
    - Example: a chat. Latest 50 messages of a chat: `messages_by_chat`, partition `chat_id`, sort `sent_at` desc.
      A user's chats by last activity: `chats_by_user`, partition `user_id`, sort `last_message_at` desc. A new message
      is written to both. In PostgreSQL: `messages`, `chats`, `chat_members` and a join.

### CC4 Database indexing

- B-tree indexes: default, support both exact lookups and ranges.
- Hash indexes: better for exact, but do not support ranges.
- Compound index: for queries filtering on two columns, e.g. "events in San Francisco on 25 December" needs an index on
  `(city, date)`.
- Specialized indexes:
    - Full text search.
    - Geospatial search.
- Partial indexes: when you have e.g. 3 years of history but usually browse only the latest rows.
    - So: index only the rows matching a condition, the index stays small.

### CC5 Caching

- Add when the DB is hammered with reads.
- Redis cache hit: 1 ms, compared to DB 20–50 ms.
- Hard part: invalidation.
    - Immediately after write.
    - Short TTL and accept staleness.
    - Both.
- Hard part: refreshing when many requests hit.
    - Locking: only 1 refreshes.
    - Early recomputation.
    - Stagger the TTLs, so entries do not all expire at once.
- Cache-aside: the default pattern (90% of cases).

```
 Read path:

   App ──1. GET key ───────────────▶ Redis
    │  ◀── hit: return the value ─────┘
    │
    │ miss
    ├──2. SELECT ... ───────────────▶ Database
    │  ◀── row ───────────────────────┘
    │
    └──3. SET key row EX ttl ────────▶ Redis, then return the row

 Write path:

   App ──1. UPDATE ... ─────────────▶ Database
    └──2. DEL key ──────────────────▶ Redis   (the next read loads the fresh value)
```

- Where to cache:
    - Redis: the default for application data.
    - CDN: static files (images, videos, JavaScript) at edge locations close to the users.
    - In-process: only small values that rarely change (feature flags, config).
- Redis down entirely: every request hits the DB.
    - So: a small in-process fallback cache, a circuit breaker to shed load, graceful degradation until Redis is back.
- Do not cache everything: only data read often and changed rarely; profile first, then cache the hot paths.

### CC6 Sharding

- Usually to do when hitting storage limits (TBs) or write throughput limits (tens of thousands per sec).
- Most important: the sharding key.
    - Shard-scoped requests: fast.
    - Global: very slow.
- Do not do it too early: at 10k writes per s and 100 GB it is not needed yet.
    - So: bring it up only after showing that one DB plus read replicas is not enough.
- Hash-based sharding: the default; `hash(shard key)` picks the shard, which spreads the data evenly.
- Hot spot: one key gets a huge share of the traffic (e.g. Taylor Swift's concert on one shard) while the others idle.
- Resharding is painful: a new shard means moving a lot of data (see consistent hashing below).
- Cross-shard transactions are near to impossible (distributed transactions, sagas).
    - E.g. one user transfers money to another, on a different shard.
- Range-based sharding: when the key grows monotonically (e.g. customer ID), split by fixed ranges and put only the new
  customers on a new shard; no existing data moves.
    - So: a shard is hot when the load is uneven across ranges; check where the load really sits (e.g. in Woodpecker
      the most active were the customers with a big setup and many campaigns, not the new ones).

### CC7 Consistent hashing

Supports elastic scaling.

- Simple modulo: `hash(key) % N`.
- So: the result changes every time N changes, in a way that almost every key maps to a different server.
- So: a lot of moving data (10 → 11 servers moves 90% of data).
- Arranging servers and keys on a virtual ring.
- So: calculate the hash.
- So: assign the server next on the ring.
- So: much less moving (10 → 11 servers moves 10%).

```
 Hash space 0–99 as a ring; each server sits at the hash of its name; a key goes clockwise to the next server.

                       DB1 (0)
                   .-'''''''''''-.
                 /                 \
                |                   |
      DB4 (75)  |       ring        |  DB2 (25)
                |                   |
                 \                 /
                   '-...........-'
                       DB3 (50)

 key "user-7"  → hash 12 → clockwise → DB2 (25)
 key "user-42" → hash 80 → clockwise, past 99 back to 0 → DB1 (0)

 Add DB5 at 35:
   only the keys hashing to 26–35 move (from DB3 to DB5); every other key stays where it was.
```

### CC8 CAP

You can have only two of the three:

- Consistency (all nodes see the same data).
- Availability (every request gets a response).
- Partition tolerance (the system works even when network connections fail between nodes).

Partitions are unavoidable in distributed systems, so you usually choose between consistency and availability.

- Consistency: if you choose it, when a network partition happens, the nodes refuse to serve requests to avoid returning
  potentially stale data, but when the system is up, it is serving always correct data.
- Availability: every node keeps serving requests even during a partition, but when users get a response, different
  nodes might be returning different data until the partition heals.

Important:

- You don't choose one for the entire system: different parts might have different priorities (e.g. transaction
  management: consistency, vs a reviews system: availability).
- CAP is about system behaviour during network partitions, which are quite rare. In normal operations the real trade-off
  is consistency vs latency.
- PACELC: during a Partition choose Availability or Consistency; Else choose Latency or Consistency.
    - Latency, because the nodes need to coordinate before responding.
- This is mostly about replicating distributed data.
- Usually choose eventual consistency, unless the problem involves money, inventory, booking limited resources.

### CC9 Numbers to know

From the article's table:

| Component      | Key metrics                                                                                      | Scale triggers                                                                                    |
|----------------|--------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------|
| Caching        | ~1 ms latency; 100k+ operations per second; memory-bound (up to 1 TB)                            | Hit rate < 80%; latency > 1 ms; memory usage > 80%; cache churn or thrashing                      |
| Databases      | Up to 50k transactions per second; sub-5 ms read latency (cached); 64 TiB+ storage               | Write throughput > 10k TPS; read latency > 5 ms uncached; geographic distribution needs           |
| App servers    | 100k+ concurrent connections; 8–64 cores at 2–4 GHz; 64–512 GB RAM, up to 2 TB                   | CPU > 70%; response latency > SLA; connections near 100k per instance; memory > 80%               |
| Message queues | Up to 1 million messages per second per broker; sub-5 ms end-to-end latency; up to 50 TB storage | Throughput near 800k messages per second; partition count ~200k per cluster; growing consumer lag |

One well-tuned PostgreSQL instance, rough ballparks (they depend on the hardware and on how heavy each query is):

| What              | Ballpark                                                            |
|-------------------|---------------------------------------------------------------------|
| Simple writes     | thousands to low tens of thousands per second; replicas do not help |
| Simple reads      | tens of thousands per second, more with each read replica           |
| Data              | a few TB is common; tens of TB is possible but painful              |
| Rows in one table | hundreds of millions are fine; billions call for partitioning       |
| Connections       | a few hundred at most; a pooler (PgBouncer) in front                |

- So: "too big for one PostgreSQL" means writes above about 10k–20k per second at peak, or tens of TB. Estimate first
  and compare; often one instance is enough, and saying why is a good answer.
