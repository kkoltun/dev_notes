## Dealing with concurrency in databases

### Questions for this article

1. What are two general approaches to the concurrency?
2. What is the locking mechanism? What are two general categories of locks?
3. Describe an example of a deadlock.
4. What is Two-Phase-Locking mechanism?
5. What is Conservative-Two-Phase-Locking mechanism?
6. What is the "detecting conflicts instead of avoiding them" approach?
7. What is MVCC? Why is it called like this?
8. How does the INSERT work in Postgres? Draw a simple diagram. What is the relationship between x_min and the transaction isolation level?
9. How does the DELETE work in Postgres? Draw a simple diagram. What is the relationship between x_min and the transaction isolation level?
10. How does the UPDATE work in Postgres? Draw a simple diagram. What is the relationship between x_min and the transaction isolation level?

---

### Two general approaches

*This is mostly a followup from the Isolation ACID property.*

Two main ways of dealing with concurrency:
* Avoiding conflicts - you avoid them, by employing a **pessimistic locking** mechanism (e.g. Read/Write locks, Two-Phase locking).
* Detecting conflicts - you allow them, but then you need to detect them using an **optimistic locking** mechanism (e.g. logical clock, MVCC).

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

The [ReadWriteLock](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/locks/ReadWriteLock.html) is an example from the JVM.

---

### Deadlocks

This locking behavior often leads to deadlocks. The database will automatically kill one transaction. The choice is implementation-dependent. Usually it will kill the one that has least cost, the one that has fewer locks (SQL server).

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
* If transaction A has read an object and transaction B wants to write to that object, B must wait until A commits or aborts before it can continue.
* If transaction A has written an object and transaction B wants to read that object, B must wait until A commits or aborts before it can continue.

**So, in general, readers block writers and writers block readers (unlike snapshot isolation).**

There are two phases:
1. **Expanding phase** - locks are acquired and no locks are released.
2. **Shrinking phase** - locks are released and no locks are acquired.
3. Usually you don't know the end of phase 1, so it is determined only when a transaction has completed processing and requested commit/abort.
4. In that phase, all the locks can be released at once.

Drawbacks:
* Transaction throughput and response times of queries are significantly worse under two-phase locking than under weak isolation.
* Database does not limit transaction time, so some transactions might will wait for a lot of time. You have to make sure that you keep all transactions short.
* Unstable latencies, very slow at high percentiles.

Predicate locks:
* In order to prevent phantoms, database has to lock all objects matching some search condition, rather than a single object that does not exist.
* The predicate lock applies event to objects that do not yet exist in the database. This way database prevents all forms of write skew and other race conditions, which makes it serializable.
* For example `SELECT * FROM bookings WHERE room = 123 AND end_time > '2018-01-01' AND start_time < '2018-02-01` would need to lock all objects that match the WHERE clause to prevent phantoms and over-booking as a result.

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

**In other words, to prevent blocking, the database can rebuild previous versions of a database record so an uncommitted change can be hidden away from incoming concurrent readers.**

In PostgreSQL, this means:
* Storing all row versions in the table data structure. Both current rows and their previous versions are stored.
* Additional column `x_min` defines the transaction ID that inserted the record.
* Additional column `x_max` defines the transaction ID that deleted the row.
* The transaction ID = `txid_current()` value (32 bit; not some global timestamp; wraps around!).
* Vacuuming process that cleans up data that is no longer needed.
* If the transaction A does the modification, transaction B will or will not see the modifications (records) depending on the isolation level:
    * In READ_COMMITTED, the current statement timestamp is compared with respective `x` value.
    * In REPEATABLE_READ and SERIALIZABLE, the transaction ID is compared with the `x`.

Operations in PostgreSQL:
* `INSERT`:
  * Transaction A puts a new version of the entity in the database with `x_min = transaction_id` value.
  * Transaction B with `transaction_id > x_min` will read the record.
  * Transaction C with `transaction_id < x_min` behavior depends on the isolation level:
    * READ_COMMITTED: the timestamp of the current statement matters; if `t > x_min` will read the record.
    * REPEATABLE_READ, SERIALIZABLE: `transaction_id > x_min` will read the record.
* `DELETE`:
  * Transaction A puts a `x_max = transaction_id` value into the deleted record. Nothing gets really deleted.
  * Transaction B with `transaction_id > x_max` will not see the deleted record.
  * Transaction C with `transaction_id < x_max`  behavior depends on the isolation level:
      * READ_COMMITTED: the timestamp of the current statement matters; if `t > x_max` will not see the record.
      * REPEATABLE_READ, SERIALIZABLE: `transaction_id > x_max` will not read the record.
* `UPDATE` does just a `DELETE` and an `INSERT`. So the database is storing multiple versions of the record.

Other databases with MVCC mechanisms usually store differences instead of multiple versions of the records.

[Excellent article from Vlad Mihalcea about this with diagrams.](https://vladmihalcea.com/how-does-mvcc-multi-version-concurrency-control-work/)

[Vlad Mihalcea on write Skew using MVCC.](https://vladmihalcea.com/write-skew-2pl-mvcc/)

