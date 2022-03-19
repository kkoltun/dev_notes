# Transaction Isolation Levels

## ANSI Isolation Levels

### Read uncommitted isolation

**Features:**
* Dirty reads are permitted.
* No lost updates.
* One transaction may not write to a row if another uncommitted transaction has already written to it.
* Any transaction may read any row.

**Possible implementation:**
* Exclusive write locks.

### Read committed isolation

**Features:**
* Unrepeatable reads are permitted.
* No dirty reads.

**Possible implementation:**
* Shared read locks: reading transactions don't block other transactions from accessing a row.
* Exclusive write locks: any uncommitted writing transaction blocks all other transactions from accessing the row.

### Repeatable read isolation

**Features:**
* Phantom reads are permitted.
* No unrepeatable reads.

**Possible implementation:**
* Reading transactions block writing transactions but not other reading transactions.
* Writing transactions block all other transactions.

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

## Choosing an isolation level

**Overview of the topic:**
* Most applications do not need *serializable isolation*, phantom reads are usually not that problematic.
* *Read uncommitted* isolation is extremely dangerous to use, it should be eliminated from the beginning.
* You usually do not need a *repeatable read* in every transaction.

### JPA specification

**JPA specification assumes that *read committed* is the default isolation level. This means there can be *unrepeatable reads*, *phantom reads* and *last commit wins* problems.**

**These two features improve the situation:**
1. The **persistence context cache** ensures that the state of the entity instances loaded in one transaction is isolated from other transactions:
  * Retrieving the same entity instance twice in a unit of work results in a mechanism in which the second lookup will be resolved within the persistence context cache and not hit the database.
  * This is why, the read is repeatable and the client won't see conflicting committed data.
  * There still can be phantom reads, but this is a much less severe problem.

2. Enabling **versioning** of the domain model entities turns the *last commit wins* problem into *first commit wins* mechanism. Hibernate can deal with versioning automatically.
