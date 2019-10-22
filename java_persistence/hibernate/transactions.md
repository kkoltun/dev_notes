# Transactions in Hibernate and JPA

## ACID attributes

Basic attributes of a transaction:
* **Atomicity** - all operations in a transaction execute as an atomic unit.
* **Consistency** - transactions allow multiple users to work concurrently with the same data.
* **Isolation** - a particular transaction should not be visible to other concurrently running transactions.
* **Durability** - transactions should be durable even if the system fails after the transaction has completed successfully.

Business may dictate many rules, so we add one more attribute:
* **Correctness** - the transactions must comply with various business rules. This usually is the responsibility of the application, because many rules cannot be expressed with database constraints.

## Managing transactions

1. If there is only one transactional resource, unit of work involves one system:
  * **Use JDBC API.**
  * **Begin transaction**: use `Connection#setAutoCommit(false)`.
  * **End transaction**: use `Connection#commit()` or `Connectio#rollback()`.

2. If a particular unit of work involves access to more than one transactional resource:
  * **Use JTA API to handle several resources in one system transaction.**
  * **Begin transaction**: use `UserTransaction#begin()`.
  * **End transaction**: use `UserTransaction#commit()`.
  * **Other transaction managers**: use JTA wherever you can and avoid proprietary transaction APIS such as `org.hibernate.Transcation` or `javax.persistence.EntityTransaction`.

## Handling exceptions


