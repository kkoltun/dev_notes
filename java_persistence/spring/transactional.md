# Spring `@Transactional`

**Remember that @Transactional works on public bean methods when calling autowired bean, not e.g. `this` (CGLIB proxy is
required).**

## Physical vs logical transaction

* Physical transaction = the one opened in the database. There could be different savepoints defined in one transaction.
* Logical transaction = potentiall nested `@Transactional` methods.

One physical transaction can have one or more logical transactions inside.

## Propagation modes

### Application for example logs

Invoice service inserts an invoice in a `@Transactional` method and then calls the balances service which fails.

Method `InvoiceService.add()`:

1. Run the INSERT.
2. Call `BalancesService.updateBalance()`.
3. `updateBalance()` throws a uncaught `RuntimeException`.
4. `add()` catches it and handles.

Both `add()` and `updateBalance()` are valid `@Transactional` methods within `InvoiceService` and `BalancesService`
Spring beans.

### REQUIRED (default)

* If there is a transaction - use it; otherwise - open a new one.
* Calling @Transactional method from another one:
    * Uses the same physical transaction.
* The `@Transactional` `updateBalance()` method call throws unchecked exception:
    * **Spring does not rollback on exit, it only marks the transaction for rollback `status.setRollbackOnly()`.**
    * The `add()` method goes on and the ROLLBACK is issued on its exit, basing on the flag set above.
    * There is a `UnexpectedRollbackException` exception thrown here, but it is thrown only to inform, that the method
      returned normally as if it succeeded, but the data was NOT persisted. It is not a failure to COMMIT an already
      rolled-back transaction, because the transaction is just rolled back basing on the flag set some time ago.

Example logs with the exception:

```
2026-09-21 10:59:20.608 UTC [413] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:59:20.628815604Z 2026-09-21 10:59:20.628 UTC [413] LOG:  statement: BEGIN
2026-09-21T10:59:20.629209175Z 2026-09-21 10:59:20.629 UTC [413] LOG:  execute <unnamed>: INSERT INTO invoices (pdf_url, user_id, amount) VALUES ($1, $2, $3)
2026-09-21T10:59:20.629223759Z 	
2026-09-21T10:59:20.629225820Z 	RETURNING *
2026-09-21T10:59:20.629227588Z 2026-09-21 10:59:20.629 UTC [413] DETAIL:  Parameters: $1 = 'https://dev-cdn.karolkoltun.dev/images/default/sample.pdf', $2 = 'alamakota', $3 = '12'
2026-09-21T10:59:20.640025692Z 2026-09-21 10:59:20.639 UTC [413] LOG:  execute <unnamed>: INSERT INTO balances (user_id, amount) VALUES ($1, $2)
2026-09-21T10:59:20.640057229Z 	ON CONFLICT(user_id) DO UPDATE SET amount = balances.amount + $3
2026-09-21T10:59:20.640060782Z 	
2026-09-21T10:59:20.640063464Z 	RETURNING *
2026-09-21T10:59:20.640066511Z 2026-09-21 10:59:20.639 UTC [413] DETAIL:  Parameters: $1 = 'alamakota', $2 = '12', $3 = '12'
2026-09-21T10:59:20.641657113Z 2026-09-21 10:59:20.641 UTC [413] LOG:  execute S_1: ROLLBACK

-- add() is about to exit; Spring
--     checks the rollback-only flag, sees it's set,
--     does a ROLLBACK instead of COMMIT
--     throws an exception to add()'s caller: UnexpectedRollbackException Transaction rolled back because it has been marked as rollback-only
```

### REQUIRES_NEW

* Always open a new transaction.
* If there a already a transaction open, Spring:
    * **Suspends** the current transaction - it unbinds the current transaction from thread-local
      `TransactionSynchronizationManager` and stashes it in `SuspendedResourcesHolder`. The connection is left open.
    * Asks the `DataSource`/connection pool for another connection and starts a brand new transaction on it.
    * That inner transaction runs to completion independently (different PID). It is e.g. rolled back.
    * **Resumes** the outer transaction - rebinds back to the thread and the code continues on that original connection.

Facts:

* For database, these are two fully separate, independent transactions.
* There is a need for at least 2 connections available in the pool.
* **Suspend** and **resume** are purely Spring/JVM-side bookkeeping terms.

Example logs:

```
-- FIRST TRANSACTION (OUTER)
-- PID = 330
2026-09-21 10:34:08.248 UTC [330] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:34:08.249279731Z 2026-09-21 10:34:08.249 UTC [330] LOG:  statement: BEGIN
2026-09-21T10:34:08.249776065Z 2026-09-21 10:34:08.249 UTC [330] LOG:  execute <unnamed>: INSERT INTO invoices (pdf_url, user_id, amount) VALUES ($1, $2, $3)
2026-09-21T10:34:08.249793206Z     
2026-09-21T10:34:08.249795540Z     RETURNING *
2026-09-21T10:34:08.249797522Z 2026-09-21 10:34:08.249 UTC [330] DETAIL:  Parameters: $1 = 'https://dev-cdn.karolkoltun.dev/images/default/sample.pdf', $2 = 'alamakota', $3 = '12'
-- SECOND TRANSACTION (INNER)
-- FIRST TRANSACTION SUSPENDED
-- PID = 331
2026-09-21T10:34:08.255737448Z 2026-09-21 10:34:08.255 UTC [331] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:34:08.256241395Z 2026-09-21 10:34:08.256 UTC [331] LOG:  statement: BEGIN
2026-09-21T10:34:08.256690959Z 2026-09-21 10:34:08.256 UTC [331] LOG:  execute <unnamed>: INSERT INTO balances (user_id, amount) VALUES ($1, $2)
2026-09-21T10:34:08.256710230Z     ON CONFLICT(user_id) DO UPDATE SET amount = balances.amount + $3
2026-09-21T10:34:08.256711826Z     
2026-09-21T10:34:08.256712948Z     RETURNING *
2026-09-21T10:34:08.256722491Z 2026-09-21 10:34:08.256 UTC [331] DETAIL:  Parameters: $1 = 'alamakota', $2 = '12', $3 = '12'
2026-09-21T10:34:08.257262518Z 2026-09-21 10:34:08.257 UTC [331] LOG:  execute S_1: ROLLBACK
-- SECOND TRANSACTION ROLLS BACK
-- FIRST TRANSACTION IS RESUMED
2026-09-21T10:34:08.257657449Z 2026-09-21 10:34:08.257 UTC [330] LOG:  execute S_1: COMMIT
-- FIRST TRANSACTION COMMITS
```

### NESTED

* If there is no transaction, works just as `REQUIRES_NEW`.
* If there is a transaction:
    * Verify savepoint support, if not supported - throw.
    * Use the existing connection and physical transaction.
    * Create a savepoint in the database.
    * On success - call `connection.releaseSavepoint(savepoint)` which discards the savepoint marker, Postgres keeps the
      changes, nothing is rolled back.
    * On failure - call `connection.rollback(savepoint)` which undoes only the statements issued since creating it. The
      outer transaction is left alive and valid. E.g. the exception might propagate, but it's the caller's decision what
      to do next (continue or trigger a full rollback).

Facts:

* Not all transaction managers support savepoints.
* This is somehow similar to `REQUIRES_NEW`, when the inner logical transaction does a rollback. However, in the
  no-rollback scenario, the inner transaction can still be rolled back by the outer one.

Example logs:

```
2026-09-21 10:41:53.061 UTC [355] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:41:53.076432489Z 2026-09-21 10:41:53.076 UTC [355] LOG:  statement: BEGIN
2026-09-21T10:41:53.076860935Z 2026-09-21 10:41:53.076 UTC [355] LOG:  execute <unnamed>: INSERT INTO invoices (pdf_url, user_id, amount) VALUES ($1, $2, $3)
2026-09-21T10:41:53.076867433Z 	
2026-09-21T10:41:53.076869001Z 	RETURNING *
2026-09-21T10:41:53.076870485Z 2026-09-21 10:41:53.076 UTC [355] DETAIL:  Parameters: $1 = 'https://dev-cdn.karolkoltun.dev/images/default/sample.pdf', $2 = 'alamakota', $3 = '12'
2026-09-21T10:41:53.085777626Z 2026-09-21 10:41:53.085 UTC [355] LOG:  execute <unnamed>: SAVEPOINT "SAVEPOINT_1"
2026-09-21T10:41:53.088013331Z 2026-09-21 10:41:53.087 UTC [355] LOG:  execute <unnamed>: INSERT INTO balances (user_id, amount) VALUES ($1, $2)
2026-09-21T10:41:53.088024871Z 	ON CONFLICT(user_id) DO UPDATE SET amount = balances.amount + $3
2026-09-21T10:41:53.088026552Z 	
2026-09-21T10:41:53.088027940Z 	RETURNING *
2026-09-21T10:41:53.088029420Z 2026-09-21 10:41:53.087 UTC [355] DETAIL:  Parameters: $1 = 'alamakota', $2 = '12', $3 = '12'
2026-09-21T10:41:53.088901942Z 2026-09-21 10:41:53.088 UTC [355] LOG:  execute <unnamed>: ROLLBACK TO SAVEPOINT "SAVEPOINT_1"
2026-09-21T10:41:53.089080161Z 2026-09-21 10:41:53.089 UTC [355] LOG:  execute <unnamed>: RELEASE SAVEPOINT "SAVEPOINT_1"
2026-09-21T10:41:53.090262680Z 2026-09-21 10:41:53.090 UTC [355] LOG:  execute S_1: COMMIT
```

### NOT_SUPPORTED

Run non-transactionally, **suspending** the current transaction if one exists - same suspend/resume machinery as
`REQUIRES_NEW`.

Example logs:

```
2026-09-21 10:54:07.230 UTC [395] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:54:07.231997649Z 2026-09-21 10:54:07.231 UTC [395] LOG:  statement: BEGIN
2026-09-21T10:54:07.232561278Z 2026-09-21 10:54:07.232 UTC [395] LOG:  execute <unnamed>: INSERT INTO invoices (pdf_url, user_id, amount) VALUES ($1, $2, $3)
2026-09-21T10:54:07.232576160Z 	
2026-09-21T10:54:07.232578700Z 	RETURNING *
2026-09-21T10:54:07.232592802Z 2026-09-21 10:54:07.232 UTC [395] DETAIL:  Parameters: $1 = 'https://dev-cdn.karolkoltun.dev/images/default/sample.pdf', $2 = 'alamakota', $3 = '12'
-- NO BEGIN HERE, BUT THERE IS A NEW PID
2026-09-21T10:54:07.238686881Z 2026-09-21 10:54:07.238 UTC [396] LOG:  statement: SET application_name = 'PostgreSQL JDBC Driver'
2026-09-21T10:54:07.239680046Z 2026-09-21 10:54:07.239 UTC [396] LOG:  execute <unnamed>: INSERT INTO balances (user_id, amount) VALUES ($1, $2)
2026-09-21T10:54:07.239695277Z 	ON CONFLICT(user_id) DO UPDATE SET amount = balances.amount + $3
2026-09-21T10:54:07.239697647Z 	
2026-09-21T10:54:07.239699497Z 	RETURNING *
2026-09-21T10:54:07.239701590Z 2026-09-21 10:54:07.239 UTC [396] DETAIL:  Parameters: $1 = 'alamakota', $2 = '12', $3 = '12'
-- NO COMMIT HERE, BUT THE CHANGES ARE IN THE DB - AUTOCOMMIT MODE
-- Postgres just wraps each individual statement in its own implicit transaction, commits it the instant it finishes.
2026-09-21T10:54:07.250693233Z 2026-09-21 10:54:07.250 UTC [395] LOG:  execute S_1: COMMIT
-- If 395 rolled back here, there would be an inconsistency, because 396 is already committed for real and independently.
```

### SUPPORTS

Join the current transaction if one exists, otherwise run non-transactionally.

### MANDATORY

Join the current transaction if one exists; throw `IllegalTransactionStateException` if there is none.

### NEVER

Run non-transactionally; throw `IllegalTransactionStateException` if a transaction does exist.

