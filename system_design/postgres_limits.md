## When one PostgreSQL is no longer enough

The order of fixes (query tuning, scale up, replicas, partitioning, sharding) is
in [database scaling](../java_persistence/database_basics/database_scaling.md). This note is about recognising that the
limit is near.

The number of rows alone rarely decides it. A table of a few hundred million rows works well as long as the queries use
good indexes and the hot index pages stay in RAM. Watch the behaviour instead; each signal points to its own fix.

### Signals

| Signal                                | What you see                                                           | Fixes                                                                                                                               |
|---------------------------------------|------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| The working set no longer fits in RAM | The hot rows and index pages are read from disk; latency spikes.       | Partial indexes covering only the queried rows (e.g. only open orders), partitioning by time and dropping old partitions, more RAM. |
| Reads saturate the CPU                | One machine cannot serve that many queries.                            | Read replicas, a cache in front.                                                                                                    |
| Writes saturate the primary           | Every write goes to one node (its WAL and disk); replicas do not help. | Batching writes, a bigger machine, only then sharding.                                                                              |
| Maintenance stops keeping up          | Vacuum, index rebuilds, backups and restores take hours.               | Partitioning by time; old partitions detached, archived and dropped.                                                                |

### Ballparks for one well-tuned instance

Orders of magnitude for comparing against an estimate, not hard limits.

| What                  | Ballpark                                                  | Note                                                                    |
|-----------------------|-----------------------------------------------------------|-------------------------------------------------------------------------|
| Data on one instance  | a few TB common; tens of TB possible but painful          | Backups, restores and new replicas get slow long before any hard limit. |
| Rows in one table     | hundreds of millions fine; billions call for partitioning | What matters is whether the hot index pages fit in RAM.                 |
| Simple reads (by key) | tens of thousands per second                              | Each read replica adds roughly as much again.                           |
| Simple writes         | thousands to low tens of thousands per second             | One primary takes all of them.                                          |
| Connections           | a few hundred at most                                     | Each one is a server process; a pooler (PgBouncer) sits in front.       |

### Partitioning one table by time

Not the same as *Fifth step - partitioning*
in [database scaling](../java_persistence/database_basics/database_scaling.md), which splits data by function into
separate databases. Here **one table inside one instance** is split, e.g. by month:

```
orders (partitioned by created_at)
├── orders_2025_11   ← detached, archived (e.g. files in S3), dropped
├── ...
└── orders_2026_11   ← all hot writes and reads land here
```

* Vacuum and index rebuilds work on one partition, not on billions of rows.
* Old data leaves in one cheap step: detach, archive, drop. No row-by-row `DELETE`, no vacuum afterwards.
* Partitioning alone does not shrink the instance; the size goes down only once old partitions are moved out.
* If all the data must stay online and queryable, it is a bigger machine, then sharding.

### In an interview

Estimate first, then compare with the ballparks. Saying why one database is enough is a good answer in itself.
