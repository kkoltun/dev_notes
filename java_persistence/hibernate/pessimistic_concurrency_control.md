# Pessimistic Concurrency Control

`#todo` Tests to be implemented:
* Both pessimistic variants of `LockModeType`.
* Simulate a deadlock.

**In case of pessimistic concurrency control, when the database lock can't be obtained, exception is thrown. This is a crucial difference between this approach and optimistic one, where exception is thrown at the commit time, not at the query time.**

To obtain pessimistic locking in `EntityManager#createQuery` method, two `LockModeType` variants can be used:
* `LockModeType.PESSIMISTIC_READ` to guarantee repeatable reads.
* `LockModeType.PESSIMISTIC_WRITE` to guarantee repeatable reads, serialize data access and no phantom reads.
* If the specified lock cannot be obtained within a specified timeout, the query throws an exception.

**It is up to JPA provider to implement those requirements:**
* `H2`:
  * There is only one type of exclusive lock, so only `SELECT * FROM ITEM ... FOR UPDATE` is chosen.
* `PostgreSQL`:
  * The `PESSIMISTIC_READ` mode appends shared read lock `FOR SHARE` to the SQL QUERY.
  * The `PESSIMISTIC_WRITE` uses an exclusive write lock with `FOR UPDATE`.
* `MySQL`:
  * The `PESSIMISTIC_READ` is translated into `LOCK IN SHARE MODE`.
  * The `PESSIMISTIC_WRITE` is translated into `FOR UPDATE`.

The timeouts can be configured with:
* A hint `javax.persistence.lock.timeout`.
* Globally for a whole database.

Exceptions thrown:
* `javax.persistence.LockTimeoutException` - non-fatal exception.
* `javax.persistence.PessimisticLockException` - the transaction must be rolled back and the unit of work ends.
* The exact exception thrown depends on the SQL dialect. H2 does not support per-statement lock timeouts, so `PessimisticLockException` is always thrown.

Other features:
* `PESSIMISTIC_READ` and `PESSIMISTIC_WRITE` can be used without versioning, because they translate to SQL statements with database-level locks.
* Lock modes `READ` and `WRITE` are deprecated and should not be used.
