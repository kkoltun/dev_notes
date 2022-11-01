## Pessimistic Locking in databases (with references to JPA/Hibernate)

| Database name | Shared lock statement      | Exclusive lock statement            |
|---------------|----------------------------|-------------------------------------|
| MSSQL Server  | `WITH (HOLDLOCK, ROWLOCK)` | `WITH (UPDLOCK, HOLDLOCK, ROWLOCK)` |
| PostgreSQL    | `FOR SHARE`                | `FOR UPDATE`                        |

PostgreSQL is MVCC, so the `FOR SHARE` lock is not blocking others from writing.
It blocks others from taking an explicit lock.

[Check the code here to verify these things yourself.](https://github.com/kkoltun/dev_notes_code_java_persistence/blob/master/src/test/java/com/concurrency/PessimisticLockingExamples.java)

[Check here for more information on the explicit locks in PostgreSQL.](https://www.postgresql.org/docs/current/explicit-locking.html)

**All the information below is specific to PostreSQL. The database behavior can vary depending on the implementation. For example, MySQL does not allow `INSERT INTO` statements in the Predicate, Exclusive Lock case.** 

---

### Shared lock in PostgreSQL

The `LockMode.PESSIMISTIC_READ`:
```java
Employee employee = session.get(Employee.class, 100);

session.buildLockRequest(new LockOptions(LockMode.PESSIMISTIC_READ))
        .lock(employee);
```
translates into:
```sql
SELECT *
FROM employees
WHERE id=100;

SELECT employee_id
FROM employees
WHERE id = 100
FOR SHARE;
```

---

### Exclusive lock in PostgreSQL

**With an exclusive, explicit lock, you are emulating 2PL in MVCC system.**

The `LockMode.PESSIMISTIC_WRITE`
```java
Employee employee = session.get(Employee.class, 100);

session.buildLockRequest(new LockOptions(LockMode.PESSIMISTIC_WRITE))
        .lock(employee);
```
translates into:
```sql
SELECT *
FROM employees
WHERE id=100;

SELECT employee_id
FROM employees
WHERE id = 100
FOR UPDATE;
```

---

### Predicate, exclusive lock in PostreSQL

**Predicate locks are used when you want to lock only the subset of data.**

This code:
```java
session.createQuery("" +
        "SELECT e " +
        "FROM Employee e " +
        "WHERE e.jobId = 'SA_REP'", Employee.class)
        .setLockMode(LockModeType.PESSIMISTIC_WRITE)
        .getResultList();
```
translates into:
```sql
SELECT * 
FROM employees emp
WHERE emp.jobId = 'SA_REP'
FOR UPDATE OF emp
```

#### Predicate, exclusive lock vs `UPDATE`

The `UPDATE` will block until the lock is released.

```sql
UPDATE employees
SET salary = salary * 2
WHERE jobId = 'SA_REP'
```

#### Predicate, exclusive lock vs `DELETE`

The `DELETE` will block until the lock is released.

```sql
DELETE FROM employees
WHERE jobId = 'SA_REP'
```

#### Predicate, exclusive lock vs `INSERT`

**This will not be blocked in PostgreSQL.** It will block in eg. MySQL because this one does a lock also on the gaps `(-INF, data)` and `(data, +INF)`.

```sql
INSERT INTO employees
(id, name, salary, job_id)
VALUES
(200, 'Karol', 1000, 'SA_REP')
```
---

### Setting `NOWAIT` in the lock

The transaction with `NOWAIT` will throw a `PSQLException` if the lock is unavailable.
This is a way to fail fast.

This code:
```java
session.find(Employee.class, 1,
        LockModeType.PESSIMISTIC_WRITE,
        Collections.singletonMap(
                AvailableSettings.JPA_LOCK_TIMEOUT,
                LockOptions.NO_WAIT
        )
);
```
translates into:
```sql
SELECT *
FROM employees emp
where emp.job_id='SA_REP'
FOR UPDATE OF emp NOWAIT
```

---

### Setting `SKIP_LOCKED` query hint

[Check this post by Vlad Mihalcea.](https://vladmihalcea.com/database-job-queue-skip-locked/)

TODO notes, code

---

### PostgreSQL Advisory Locks

[Check this post by Vlad Mihalcea.](https://vladmihalcea.com/how-do-postgresql-advisory-locks-work/)

* This is a way to apply application-level concurrency control.
* The scope can be:
  * Session-based locks - reentrant and non-transactional. They have to be unlocked N times after being locked N times.
  * Transactions-based locks - reentrant and transactional. They are released at transaction commit/rollback.
* The functions accept `int` values, so you have to assign the special operations in the application to the `int` keys.

Example usage:

Locking a specific resource (`Employee#100`) within a context of a specific request. (`POST /employees/100/perk`):
1. When a request is received for a specific employee, issue a lock on the employee ID and the request URI (hashcode).
2. This way different operations can be done on the employee simultaneously, but the requests to the same operations cannot interleave.
3. For example (this is not REST) locking on URL `POST /employee/promote` with request body containing employee ID `100`.

```sql
-- Obtain exclusive session level advisory lock
void pg_advisory_lock(int key1, int key2)

-- Obtain exclusive session level advisory lock if available, returns true or false
boolean pg_try_advisory_lock(int key1, int key2)

-- Obtain shared session level advisory lock
void pg_advisory_lock_shared(int key1, int key2)

-- Obtain shared session level advisory lock if available, returns true or false
boolean pg_try_advisory_lock_shared(int key1, int key2)

-- Release locks
void pg_advisory_unlock(int key1, int key2)
void pg_advisory_unlock_shared(int key1, int key2)
void pg_advisory_unlock_all()

-- Obtain exclusive transaction-level advisory lock
 void pg_advisory_xact_lock(int key1, int key2)

-- Rest of the transaction-level functions are similar to session-level.
```

Check [here](https://www.postgresql.org/docs/9.1/functions-admin.html) for more variants of the functions.