# System Design in a Hurry (Hello Interview)

Handwritten notes from [Hello Interview, *System Design in a Hurry*](https://www.hellointerview.com/learn/system-design/in-a-hurry/introduction): the introduction, the delivery framework and the core concepts. Read on 2026-11-02.

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

**Deliver a working system.**

The steps, in order:

1. Requirements (5 min).
2. Core Entities (2 min).
3. API or Interface.
4. Data Flow.
5. High level design.
6. Deep dives.

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
- Stay focused! Do a relatively simple design that meets the core requirements, then layer on complexity to satisfy the non-functional requirements.
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

- Level 7 (application level): can route basing on the request content.
- Level 4 (transport layer): TCP level, dumber; for WebSockets you need level 4 because you are maintaining a TCP connection.

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
- Design normalized, then denormalize hot paths.
- For NoSQL: design the partition key and the sort key basing on access patterns (fast single partition lookup).

### CC4 Database indexing

- B-tree indexes: default, support both exact lookups and ranges.
- Hash indexes: better for exact, but do not support ranges.
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

### CC6 Sharding

- Usually to do when hitting storage limits (TBs) or write throughput limits (tens of thousands per sec).
- Most important: the sharding key.
  - Shard-scoped requests: fast.
  - Global: very slow.
- Do not do it too early: at 10k writes per s and 100 GB it is not needed yet.
- Cross-shard transactions are near to impossible (distributed transactions, sagas).
  - E.g. one user transfers money to another, on a different shard.

### CC7 Consistent hashing

Supports elastic scaling.

- Simple modulo: `hash(key) % N`.
- So: the result changes every time N changes, in a way that almost every key maps to a different server.
- So: a lot of moving data (10 → 11 servers moves 90% of data).
- Arranging servers and keys on a virtual ring.
- So: calculate the hash.
- So: assign the server next on the ring.
- So: much less moving (10 → 11 servers moves 10%).

(Drawn: a ring 0–90 with DB1–DB4 placed on it; each key goes clockwise to the next DB.)

### CC8 CAP

You can have only two of the three:

- Consistency (all nodes see the same data).
- Availability (every request gets a response).
- Partition tolerance (the system works even when network connections fail between nodes).

Partitions are unavoidable in distributed systems, so you usually choose between consistency and availability.

- Consistency: if you choose it, when a network partition happens, the nodes refuse to serve requests to avoid returning potentially stale data, but when the system is up, it is serving always correct data.
- Availability: every node keeps serving requests even during a partition, but when users get a response, different nodes might be returning different data until the partition heals.

Important:

- You don't choose one for the entire system: different parts might have different priorities (e.g. transaction management: consistency, vs a reviews system: availability).
- CAP is about system behaviour during network partitions, which are quite rare. In normal operations the real trade-off is consistency vs latency.
- PACELC: during a Partition choose Availability or Consistency; Else choose Latency or Consistency.
  - Latency, because the nodes need to coordinate before responding.
- This is mostly about replicating distributed data.
- Usually choose eventual consistency, unless the problem involves money, inventory, booking limited resources.

### CC9 Numbers to know

From the article's table:

| Component | Key metrics | Scale triggers |
|-----------|-------------|----------------|
| Caching | ~1 ms latency; 100k+ operations per second; memory-bound (up to 1 TB) | Hit rate < 80%; latency > 1 ms; memory usage > 80%; cache churn or thrashing |
| Databases | Up to 50k transactions per second; sub-5 ms read latency (cached); 64 TiB+ storage | Write throughput > 10k TPS; read latency > 5 ms uncached; geographic distribution needs |
| App servers | 100k+ concurrent connections; 8–64 cores at 2–4 GHz; 64–512 GB RAM, up to 2 TB | CPU > 70%; response latency > SLA; connections near 100k per instance; memory > 80% |
| Message queues | Up to 1 million messages per second per broker; sub-5 ms end-to-end latency; up to 50 TB storage | Throughput near 800k messages per second; partition count ~200k per cluster; growing consumer lag |
