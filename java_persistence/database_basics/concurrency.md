## Dealing with concurrency in databases

### Questions for this article

1. What are two general approaches to the concurrency?
2. What is the locking mechanism? What are two general categories of locks?
3. Describe an example of a deadlock.
4. What is Two-Phase-Locking mechanism?
5. What is Conservative-Two-Phase-Locking mechanism?
6. What is the "detecting conflicts instead of avoiding them" approach?
7. What is MVCC? Why is it called like this?
8. What are the additional columns in Postgres MVCC?
9. What are the visibility rules in Postgres MVCC?
10. When are snapshots taken?
11. What happens when INSERT is issued and then: (A) committed, (B) rolled back?
12. What happens when DELETE is issued and then: (A) committed, (B) rolled back?
13. What is the name of the mechanism that is used when you try to update/delete locked rows in Repeatable Read? How
    does it work?

---

### Two general approaches

*This is mostly a followup from the Isolation ACID property.*

Two main ways of dealing with concurrency:

* Avoiding conflicts - you avoid them, by employing a **pessimistic locking** mechanism (e.g. Read/Write locks,
  Two-Phase locking).
* Detecting conflicts - you allow them, but then you need to detect them using an **optimistic locking** mechanism (e.g.
  logical clock, MVCC).

**No matter what you choose, there are always going to be some locks.**

**Amdahl's Law - the more locks you have, the less space for parallelisation.**

---

### Locking in general

Better to lock on the lower level:

1. Database objects are hierarchical in nature.
2. Logical tablespace -> multiple database files -> files are built of data pages -> each page contains rows.
3. Locking on lower level (eg. rows) offer better concurrency.

Two general types of locks:

* Shared (read) lock - prevents a record from being written while allowing concurrent reads.
* Exclusive (write) lock - prevents both read and write operations.

| Compatibility        | Read/shared lock | Write/Exclusive lock |
|----------------------|------------------|----------------------|
| Read/shared lock     | Allow            | Prevent              |
| Write/exclusive lock | Prevent          | Prevent              |

The [ReadWriteLock](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/locks/ReadWriteLock.html) is an
example from the JVM.

---

### Deadlocks

This locking behavior often leads to deadlocks. The database will automatically kill one transaction. The choice is
implementation-dependent. Usually it will kill the one that has least cost, the one that has fewer locks (SQL server).

*Diagram from the Vlad Mihalcea article [here](https://vladmihalcea.com/database-deadlock/).*

![Deadlock example by Vlad Mihalcea](https://vladmihalcea.com/wp-content/uploads/2019/10/DatabaseDeadlock.png)

---

### Two-Phase Locking (2PL)

This is a relatively old approach to the problem:

* Uses shared and exclusive locks.
* Guarantees serializability (prevents even lost updates and write skew).
* The rule is - never acquire a lock after a lock has been released.
* In non-conservative 2PL, there can be deadlocks.

Rules:

* If transaction A has read an object and transaction B wants to write to that object, B must wait until A commits or
  aborts before it can continue.
* If transaction A has written an object and transaction B wants to read that object, B must wait until A commits or
  aborts before it can continue.

**So, in general, readers block writers and writers block readers (unlike snapshot isolation).**

There are two phases:

1. **Expanding phase** - locks are acquired and no locks are released.
2. **Shrinking phase** - locks are released and no locks are acquired.
3. Usually you don't know the end of phase 1, so it is determined only when a transaction has completed processing and
   requested commit/abort.
4. In that phase, all the locks can be released at once.

Drawbacks:

* Transaction throughput and response times of queries are significantly worse under two-phase locking than under weak
  isolation.
* Database does not limit transaction time, so some transactions might will wait for a lot of time. You have to make
  sure that you keep all transactions short.
* Unstable latencies, very slow at high percentiles.

Predicate locks:

* In order to prevent phantoms, database has to lock all objects matching some search condition, rather than a single
  object that does not exist.
* The predicate lock applies event to objects that do not yet exist in the database. This way database prevents all
  forms of write skew and other race conditions, which makes it serializable.
* For example `SELECT * FROM bookings WHERE room = 123 AND end_time > '2018-01-01' AND start_time < '2018-02-01` would
  need to lock all objects that match the WHERE clause to prevent phantoms and over-booking as a result.

Index-range locks:

* To avoid the overhead of predicate locks, databases use index-range locks.
* They lock a wider range of objects, e.g. all bookings with `room = 123` if there is an index for this column.
* So an **approximation** of the search condition is attached to one of the indexes.
* These locks may have a wider range, but have much less overhead than predicate locks.

[Check here for diagrams and more details.](https://vladmihalcea.com/2pl-two-phase-locking/)

---

### Conservative two-phase locking (C2PL)

This is 2PL with a rule that transactions obtain all the locks they need before the transactions begin.

The transaction that already has some locks, will not block waiting for other locks.
No deadlocks!

---

### Another approach - detecting conflicts instead of avoiding them

Excessive locking (avoiding conflicts) leads to:

* Threads getting caught in deadlocks.
* Threads spending a lot of time waiting.

Another approach is:

* Readers should not block writers.
* Writers should not block readers.
* Writers should block other writers.

So:

* Whenever you are reading something, this does not block others from writing it.
* Whenever you are writing something, you are not blocking anyone from reading it until you commit it.

The implementation of these assumptions is MVCC.

---

### Multi-Version Concurrency Control (MVCC)

**To provide the behavior described above, the system must operate on multiple versions of the same record.**

**In other words, the database keeps multiple row versions so an uncommitted change or changes committed after the
snapshot was taken (Repeatable Read) can be hidden away from incoming concurrent readers.**

In PostgreSQL, this means:

* Storing all row versions in the table data structure. Both current rows and their previous versions are stored.
* Additional column `xmin`: the identity (transaction ID) of the inserting transaction for this row version (each update
  of a row creates a new row version for the same logical row).
* Additional column `xmax`: the identity (transaction ID) of the deleting transaction or zero for undeleted row version.
  Remember that UPDATE also deletes a tuple in PostgreSQL.
    * It is possible for this column to be nonzero in a visible row version when: deleting transaction hasn't committed
      yet or an attempted deletion was rolled back.
* The transaction ID = `pg_current_xact_id()` value (32 bit; not some global timestamp; wraps around!).
    * The transaction ID is assigned lazily when it first writes to the database.
* Vacuuming process that cleans up data that is no longer needed.

#### Visibility in PostgreSQL

Every quest runs against a **snapshot** which records the things:

* `xmin` - every xid below this is finished (comitted or aborted).
* `xmax` - every xid at or above ths had not started yet.
* the list of xids that were still **in progress**.

The in-progress list is needed because transactions do not commit in the order they start, for example:

```
1. xid 100 starts
2. xid 101 starts
3. xid 102 starts
4. xid 101 COMMITS
5. xid 103 starts, takes a snapshot: xmin = 100, xmax = 104, in_progess = [100, 102]

xid 103:
* needs to see the changes from xid 101
* must not see the changes from xids 100, 102
```

This also enables the REPEATABLE READ to be repeatable - the list is frozen at snapshot time, so even if 100 and 102
COMMIT seconds later, the 103 will not see their tuples.

When is the snapshot taken?

* `READ_COMMITTED`: a fresh snapshot at the start of every statement — which is exactly why the same query can return
  different rows twice in one transaction.
* `REPEATABLE_READ`, `SERIALIZABLE`: one snapshot, at the start of the first non-transaction-control statement, reused
  for the whole transaction.
* `SERIALIZABLE` uses the same snapshot but additionally tracks read/write dependencies between concurrent transactions
  and aborts one with a serialization failure if the outcome could not have arisen from running them one at a time.

Operations in PostgreSQL:

* `INSERT`:
    * Transaction A puts a new version of the entity in the database with `x_min = A's xid`, `xmax = 0`.
    * Nobody else sees it while A is running. If A rolls back, nobody ever sees it — the tuple stays on disk until
      vacuum removes it.
    * Once A commits, the tuple is visible to any snapshot taken after the commit. So a `READ_COMMITTED` transaction
      that started before A can still see the row from its next statement onwards; a `REPEATABLE_READ` one that took its
      snapshot before A committed will not see it for its whole lifetime.
* `DELETE`:
    * Transaction A writes `xmax` = A's xid into the existing tuple. Nothing is physically removed; vacuum does that
      later, once the tuple is invisible to every possible snapshot.
    * The row stays visible to everyone else while A runs, and stays visible forever if A rolls back - a non-zero `xmax`
      does not mean "deleted".
    * After A commits, the row disappears for snapshots taken after that commit: from the next statement in
      `READ_COMMITTED`, never within an already-started `REPEATABLE_READ` transaction.

How to know if the row was DELETED:

1. The `xmax` is filled when deleting row, but it stays like this even when transaction rolls back.
2. To know if the row has been deleted (before vacuum runs), you need to check the `pg_xact` table. It stores two bits
   per transaction - in progress, committed, aborted.
3. So if the reader finds: aborted -> the deleting never happened, committed -> apply snapshot rules from above.
4. To be true, not every read check the `pg_xact` - this status is resolved once and written back to tuple's
   `t_infomask` - `HEAP_XMAX_COMMITTED` or `HEAP_XMAX_INVALID`. Every later reader sees the flag and skips the lookup.
5. The cache write above is why **SELECT statements can dirty pages and generate write I/O on a table**.

The same applies to the INSERT and UPDATE:

1. The `xmin` is not cleared on ROLLBACK!
2. This is why we need also `HEAP_XMIN_COMITTED` and `HEAP_XMIN_INVALID`.

So a `ROLLBACK` DOES NOT undo anything, it only writes one entry in `pg_xact` and stops. It is `O(1)` rather than
proportional to the work done.

Other databases with MVCC mechanisms usually store differences instead of multiple versions of the records.

----

#### EvalPlanQual (EPQ) and pitfalls related to it

EvalPlanQual (EPQ, Evaluate Plan Qualification) is a mechanism in PostgreSQL that decides what happens when `UPDATE`,
`DELETE`, `SELECT ... FOR UPDATE/SHARE` or `MERGE` in READ COMMITTED runs into a row that another transaction has
concurrently modified and committed after the statement's snapshot was taken.

1. The statement in transaction A scans the table using a snapshot taken when it started.
2. It finds a row matching `WHERE` clause and tries to update it.
3. Transaction B has already updated the row and is still running.
4. The transaction A waits on the row lock.
5. When transaction B finishes:
    1. It was rolled back -> the statement proceeds with the original row version.
    2. It committed a delete -> the statement skips the row.
    3. It committed an update -> EPQ comes into the play.

In REPEATABLE READ/SERIALIZABLE third case would throw an error
`ERROR: could not serialize access due to concurrent update`.

In READ COMMITTED, PostgreSQL:

1. Follows the row's update chain (`t_ctid`) to the latest version and locks it.
2. Re-evaluates `WHERE` along with optional `JOIN` clauses against that version.
3. If the version still qualifies, it applies the update or delete.
4. If there is any JOIN, the exact joined row that produced the candidate will be used.

What is important here:

1. EPQ only rechecks rows that the original scan already found. Rows that did not qualify are not re-checked.
2. The result combines the snapshot's decision about which rows to consider with each target row's current state, taken
   at a different instant for each row, plus snapshot-frozen data for everything else.

---

[Excellent article from Vlad Mihalcea about this with diagrams.](https://vladmihalcea.com/how-does-mvcc-multi-version-concurrency-control-work/)

[Vlad Mihalcea on write Skew using MVCC.](https://vladmihalcea.com/write-skew-2pl-mvcc/)

