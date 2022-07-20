# Transactions in Hibernate and JPA

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


