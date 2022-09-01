## Transactions in Hibernate and JPA

### Managing transactions

1. If there is only one transactional resource, unit of work involves one system:
  * **Use JDBC API.**
  * **Begin transaction**: use `Connection#setAutoCommit(false)`.
  * **End transaction**: use `Connection#commit()` or `Connectio#rollback()`.

2. If a particular unit of work involves access to more than one transactional resource:
  * **Use JTA API to handle several resources in one system transaction.**
  * **Begin transaction**: use `UserTransaction#begin()`.
  * **End transaction**: use `UserTransaction#commit()`.
  * **Other transaction managers**: use JTA wherever you can and avoid proprietary transaction APIS such as `org.hibernate.Transcation` or `javax.persistence.EntityTransaction`.

### Choosing an isolation level

**Overview of the topic:**
* Most applications do not need *serializable isolation*, phantom reads are usually not that problematic.
* *Read uncommitted* isolation is extremely dangerous to use, it should be eliminated from the beginning.
* You usually do not need a *repeatable read* in every transaction.

### Transaction classes:

* JDBC Transaction - transaction managed through a JDBC Connection.
* CMT Transaction - all work done in the context of a container managed transaction. CMT is not neccessarily container-managed, the point is that the transactions are managed by something other than Hibernate.

### XA transactions

* Global transactions.
* May span multiple resources.
* Talking to multiple resources in a single transaction.
* Websphere, Weblogic or JBoss acting as a TransactionManager.
* Various resources - Oracle Sybase, IBM MQ, JMS, SAP acting as *transaction resources*.
* *Commit* - results are commited across all of the resources.
* *Rollback* - everything is rolled back across all resources.
* Two phase commit protocol is used.

### Transaction-isolation level vs JPA specification

**JPA specification assumes that *read committed* is the default isolation level. This means there can be *unrepeatable reads*, *phantom reads* and *last commit wins* problems.**

**These two features improve the situation:**
1. The **persistence context cache** ensures that the state of the entity instances loaded in one transaction is isolated from other transactions:
* Retrieving the same entity instance twice in a unit of work results in a mechanism in which the second lookup will be resolved within the persistence context cache and not hit the database.
* This is why, the read is repeatable and the client won't see conflicting committed data.
* There still can be phantom reads, but this is a much less severe problem.

2. Enabling **versioning** of the domain model entities turns the *last commit wins* problem into *first commit wins* mechanism. Hibernate can deal with versioning automatically.