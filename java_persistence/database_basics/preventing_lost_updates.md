## How are Lost Updates prevented

### Atomic write operations

```sql
UPDATE counters
SET value = value + 1
WHERE key = 'some';
```

* Forces the *read-modify-write cycles* to happen sequentially.
* This is somehow an example of pessimistic concurrency control.
* Most databases support them, they remove need to implement *read-modify-write cycles* in application code.
* Not all writes can be easily expresses in terms of atomic operations, but when they are - use them.

### Explicit locking

```sql
SELECT *
FROM counters
WHERE key = 'some'
FOR UPDATE;
```

* Again, this forces the *read-modify-write cycles* to happen sequentially
* This is an exact example of pessimistic concurrency control.
* If the database's built-in atomic operations don't provide the necessary functionality, then the application can explicitly lock the objects that are going to be updated.

### Automatically detecting lost updates

* Instead of forcing things to happen sequentially, let them run in parallel. If the transaction managed detects a lost update, abort the transaction.
* This is an example of optimistic concurrency control.
* This is used in PostgreSQL's repeatable read, Oracle's serializable and SQL Server's snapshot isolation levels.

### Compare-and-set

```sql
UPDATE document
SET content = 'content with my new section!'
WHERE id = 1234
  AND content = 'content';
```

* Allow an update to happen only if the value has not been changed since last read.
* **This may not be sae on every database implementation.**

### Conflict resolution and replication

* Locks and compare-and-set do not apply in the context of leaderless or multi-leader replication scenarios.
  In general, these methods assume that there is a single, up-to-date copy of the data.
* Replicated databases usually allow concurrent writes to create several conflicting versions of a value called **siblings.**
  Then, application code or special data structures are used to resolve and merge these versions after the fact.

### Last write wins

* **This is actually an anti-example.**
* It achieves eventual convergence, but at the cost of durability: if there were several concurrent writes to the same key,
  even if they were all reported as successful to the client, only one of the writes will survive and the others will be silently discarded.
* Moreover, as a result of wrong timestamps handling, LWW may even drop writes that were not concurrent.
