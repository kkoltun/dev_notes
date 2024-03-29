## Transactions in the databases

### Questions for this article

1. What are two main motivations for transactions? 
2. What are 4 types of concurrent access inconsistencies?
3. What is a database transaction, what are the properties of it?
4. What is the difference between a session and a transaction?
5. Why are transactions so important in the multi-object context (3 reasons)?
6. What is Atomicity? Show it on a diagram? What are two possible cases where atomicity plays an important role?
7. What is Consistency?
8. What is Isolation? What is the ideal state? Why is it not achievable?
9. Give an example of a problem with isolation.
10. What is durability?
11. What other requirements could be present in the real-world database usage?

---

### Introduction

Transactions are motivated by two independent requirements:
* Prevent inconsistencies in the concurrent database access.
* Provide resilience to system failures.

---

### Concurrent access inconsistency types

#### Concurrent access: Attribute-level Inconsistency

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

#### Concurrent access: Tuple-level Inconsistency

Client S1:

```sql
UPDATE Apply SET major = 'CS' WHERE sID = 123
```

concurrent with client S2:

```sql
UPDATE Apply SET decision = 'Y' WHERE sID = 123
```

Both clients modify the same tuple/row. Will all rows get the modification?

#### Concurrent access: Table-level Inconsistency

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

#### Concurrent access: Multi-statement inconsistency

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

#### The goal in concurrent access

Execute sequence of SQL statements so they appear to be running in isolation.

---

### Resilience to System Failures

We could have a bulk load with a lot of data. In the middle of the bulk load, there could be a system failure. We don't want to end up with part of the data loaded.

#### The goal in resilience

Guarantee all-or-nothing execution, regardless of the failures.

---

### Transactions

**A transaction is a set of one or more SQL operations treated as a unit.**

**In a relational database, everything that you execute is done in the context of the database transaction (even in the auto-commit) mode.**

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

Basic attributes of a transaction:
* **A**tomicity
* **C**onsistency
* **I**solation
* **D**urability

Transactions are particularly important in the multi-object context:
* Single row in one table often has a foreign key reference to a row in another table.
Multi-object transactions allow you to ensue that these references remain valid.
* When denormalized information needs to be updated, you need to update several places/documents/tables in one go.
Transactions prevent denormalized data from going out of sync.
* In databases with secondary indexes, the indexes also need to be updated every time you change a value.

---

### Atomicity

**Grouping multiple operations in an all-or-nothing unit of work, which can succeed only if all individual operations succeed.**

The operations might fail because of various reasons - breaking constraints, system crash.

![Atomicity](images/atomicity.svg)

**Transaction rollback** undoes partial effects of a transaction. This can be either initiated by the system or the client.

Two mechanisms play important role here:
* Undo log - in case a transaction needs to be rolled back.
* Redo log - in case of a crash with some transactions not written to the disk yet.

> Note that atomicity in the context of ACID is different than atomicity in multi-threaded programming.
> If one thread executes an atomic operation, that means there is no way that another thread could see half-finished result of operation.
> In the context of ACID, atomicity is *not* about concurrency. This is covered under the letter **I** for **isolation**.

---

### Consistency

**A modifying transaction can be seen as a state transformation, moving the database from one valid state to another.**

Each client, each transaction:
* can assume all constraints hold when the transaction begins;
* must guarantee all constraints hold when the transaction ends (this is usually done by the constraints subsystem).

This, along with serializabiity, guarantees that the constraints always hold.

**This is different than Consistency in the CAP theorem. That one is about linearizability (every read following a write should always read the latest state).**

---

### Durability

**All committed transaction changes become permanent.**

Each transaction is a sequence of statements.
If the transaction is committed and the system crashes immediately afterwards, all the modifications will still be in the database.

This is ensured using the logging system (usually a redo log or *Write-Ahead Log* in Postgres).

---

### Isolation

**This means interleaving concurrent transaction statements so that the outcome is equivalent to a serial execution.**

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

---

### Implementation of isolation - serializability

See [here](https://vladmihalcea.com/serializability/) for details and diagrams.

See [example race condition test code](https://github.com/kkoltun/dev_notes_code_java_persistence/blob/master/src/test/java/com/bank/ACIDRaceConditionTest.java).

---

### Other requirement - correctness

Business may dictate many rules, so we add one more attribute - **correctness**. The transactions must comply with various business rules. This usually is the responsibility of the application, because many rules cannot be expressed with database constraints.

---

### Read only transactions

* This helps the system optimize the performance.
* This is independent of the isolation level.

```sql
SET TRANSACTION READ ONLY;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

SELECT AVG(GPA) FROM Student;
SELECT MAX(GPA) FROM Student;
```

---

### Additional materials

See [Designing Data Intensive Applications -> Chapter 7: Transactions -> The Meaning of ACID](https://www.oreilly.com/library/view/designing-data-intensive-applications/9781491903063/).
