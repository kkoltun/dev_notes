# Transaction Isolation Levels

* Isolation levels are set for the transaction. There could be two, concurrent transactions with different isolation levels.
* The isolation levels are mostly about the **reads**. They specify what actually can be read.

## ANSI Isolation Levels

### Read uncommitted isolation

Features:
* Dirty reads are permitted.
* No lost updates.
* One transaction may not write to a row if another uncommitted transaction has already written to it.
* Any transaction may read any row.

Possible implementation:
* Exclusive write locks.

#### Example

Transaction 1:

```sql
UPDATE College SET enrollment = 2 * enrollment
WHERE cName = 'Stanford'
```

After the statement is executed, but before the transaction is committed, the data is called **dirty**.

Transaction 2, executed concurrently:

```sql
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
SELECT AVG(enrollment) FROM College
```

The statement might read the uncommitted, increased enrollment in - this is the **Dirty Read**.
The increased enrollment could never get committed to the database (eg. system failure).

Furthermore, the statement could also get inconsistent results - calculate average on only partially updated data.
This means that part of the College rows already have the doubled enrollment and part of them have the original value.

**This is not equivalent to any serial order**, T2 could be executed in any moment of T1. It is neither `T1, T2`, nor `T2, T1`.

### Read committed isolation

Features:
* Unrepeatable reads are permitted.
* No dirty reads.

Possible implementation:
* Shared read locks: reading transactions don't block other transactions from accessing a row.
* Exclusive write locks: any uncommitted writing transaction blocks all other transactions from accessing the row.

#### Example

Transaction 1:

```sql
UPDATE Student SET GPA = 1.1*GPA WHERE sizeHS > 2500;
```

Transaction 2, executed concurrently:

```sql
SET TRANSACTION LEVEL READ COMITTED;
SELECT AVG(GPA) FROM Student;
SELECT MAX(GPA) FROM Student;
```

The `AVG` function might get the old GPA values, while the `MAX` operation could get the new GPA values. The read is unrepeatable.

**This is not equivalent to any serial order**. It is neither `T1, T2` order, nor `T2, T1` order. T1 could be executed between the T2 statements.

### Repeatable read isolation

Features:
* Phantom reads are permitted.
* No dirty reads.
* No unrepeatable reads.

Possible implementation:
* Reading transactions block writing transactions but not other reading transactions.
* Writing transactions block all other transactions.

#### Example 1 - repeatable read

Transaction 1:

```sql
UPDATE Student SET GPA = 1.1*GPA;
UPDATE Student SET sizeHS = 1500 WHERE sID = 123;
```

Transaction 2, executed concurrently:

```sql
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT AVG(GPA) FROM Student;
SELECT AVG(sizeHS) FROM Student;
```

The first `SELECT` could be executed before both `UPDATE` statements, while the second `SELECT` - after.
This does not mean a dirty read, this is not unrepeatable read, because we do not read the same field two times.

**We still don't have the global serializability.**
The first statement of T2 could go before T1, the second statement of T2 could go after T1.
So this is neither `T1, T2` nor `T2, T1`.

#### Example 2 - phantom tuples 

Transaction 1:

```sql
INSERT INTO Student [100 new tuples];
```

Transaction 2, executed concurrently:

```sql
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT AVG(GPA) FROM Student;
SELECT MAX(GPA) FROM Student;
```

**Repeatable read** allows the two statements to be executed before and after the insertion of the tuples (rows).
The new tuples that appeared between the `SELECT` statements are called **phantom tuples**.
So the `AVG` operation might be calculated on a different set of data than `MAX`.
The rationale behind this is that the tuples that we read in `AVG` statement, still have the same value when we are reading in the `MAX` statement.

This behavior does not happen when deleting rows, however.

### Serializable isolation

**Features:**
* Emulates serial execution - as if transactions were executed one after another, rather than concurrently.

### Summary

Table from [Patterns of Enterprise Application Architecture by Martin Fowler](https://www.amazon.com/Patterns-Enterprise-Application-Architecture-Martin/dp/0321127420):

| Isolation Level  | Dirty Read | Unrepeatable Read | Phantom Read |
|---|---|---|---|
| Read Uncommitted | Yes | Yes | Yes |
| Read Committed | No | Yes | Yes |
| Repeatable Read | No | No | Yes |
| Serializable | No | No | No |