# Transactions in the databases

Transactions are motivated by two independent requirements:
* Concurrent database access.
* Resilience to system failures.

## Concurrent access

### Concurrent access: Attribute-level Inconsistency

Client S1:

```sql
UPDATE College SET enrollment = enrollment + 1000
WHERE cName = 'Stanford'
```

concurrent with client S2:

```sql
UPDATE College SET enrollment = enrollment + 1000
WHERE cName = 'Stanford'
```

Both clients modify the same attribute. Will all rows get modified correctly?

### Concurrent access: Tuple-level Inconsistency

Client S1:

```sql
UPDATE Apply SET major = 'CS' WHERE sID = 123
```

concurrent with client S2:

```sql
UPDATE Apply SET decision = 'Y' WHERE sID = 123
```

Both clients modify the same tuple/row. Will all rows get the modification?

### Concurrent access: Table-level Inconsistency

Client S1:

```sql
UPDATE Apply SET decision = 'Y'
WHERE sID IN (SELECT sID FROM Student WHERE GPA > 3.9)
```

concurrent with client S2:

```sql
UPDATE Student SET GPA = 1.1*GPA WHERE sizeHS > 2500
```

Will these two issued concurrently result in a consistent state of the database?

### Concurrent access: Multi-statement inconsistency

Client S1:

```sql
INSERT INTO Archive 
SELECT * FROM Apply WHERE decision = 'N';
DELETE FROM Apply WHERE decision = 'N';
```

concurrent with client S2:

```sql
SELECT COUNT(*) FROM Apply;
SELECT COUNT(*) FROM Archive;
```

### The goal in concurrent access

Execute sequence of SQL statements so they appear to be running in isolation.

---

## Resilience to System Failures

We could have a bulk load with a lot of data. In the middle of the bulk load, there could be a system failure. We don't want to end up with part of the data loaded.

### The goal in resilience

Guarantee all-or-nothing execution, regardless of the failures.

---

## Transactions

**A transaction is a set of one or more SQL operations treated as a unit.**

* Transactions appear to run in isolation.
* If the system fails, each transaction's changes are reflected either entirely or not at all.

SQL standard:
* Transaction begins automatically on first SQL statement.
* On `commit` transaction ends and new one begins.
* Current transaction ends on session termination.
* `Autocommit` turns each statement into transaction.

Session vs transaction:
* Session may be spanning over multiple transactions.
* Over the same connection multiple (begin transaction - commit) are possible.

### ACID attributes

Basic attributes of a transaction:
* **Atomicity**
* **Consistency**
* **Isolation**
* **Durability**

### Atomicity

This deals with the crash during the transaction. Each transaction is executed "all-or-nothing", it is never left half way done.

The logging mechanism ensures this. There are special mechanisms that, after the system recovers from the crash, undo the partial effects of the transactions.

**Transaction rollback** undoes partial effects of a transaction. This can be either initiated by the system or the client.

### Consistency

Each client, each transaction:
* can assume all constraints hold when the transaction begins;
* must guarantee all constraints hold when the transaction ends (this is usually done by the constraints subsystem).

This, along with serializabiity, guarantees that the constraints always hold.

### Isolation

1. Many users operate on the database; each of them issues a sequence of transactions; each transaction is a sequence of statements.
2. **Serializability** is the implementation of the isolation. This means that the operations within transactions may be interleaved, but execution must be equivalent to some sequential (serial) order of all transactions.
3. So the system might execute all of these operations done by users concurrently, but it has to guarantee that the behavior against the database is equivalent to some sequential order.
4. How is it done? Using protocols involving locking.

This solves the potential issues in *Attribute-level Inconsistency* and *Tuple-level Inconsistency*.
In both examples above, the database can execute two transactions in arbitrary order and this will be OK, as long as they both are fully executed.

In the case of *Table-level Inconsistency* and *Multi-statement inconsistency* the database still can execute the two transactions in arbitrary order and this **will** leave the database in the consistent state.
However, the order of the execution of these two transactions matters from the user standpoint.
So, the database guarantees the serializability when the transactions are issued concurrently, but **does not** ensure the exact order of the execution.
If this is an issue, it has to be coded as part of an application.

Actually, serializability has some overhead (locks) and reduces the concurrency. This is why, databases offer weaker "isolation levels":
* Read Uncommitted
* Read Committed
* Repeatable Read

See [the transaction isolation levels for details](transaction_isolation_levels.md).

### Durability

Each transaction is a sequence of statements.
If the transaction is committed and the system crashes immediately afterwards, all the modifications will still be in the database.

This is ensured using the logging system.

## Other requirements

Business may dictate many rules, so we add one more attribute:
* **Correctness** - the transactions must comply with various business rules. This usually is the responsibility of the application, because many rules cannot be expressed with database constraints.

## Read only transactions

* This helps the system optimize the performance.
* This is independent of the isolation level.

```sql
SET TRANSACTION READ ONLY;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

SELECT AVG(GPA) FROM Student;
SELECT MAX(GPA) FROM Student;
```