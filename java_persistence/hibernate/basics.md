# JPA

Problems addressed by the persistence tools:
* **the problem of granularity** - classes in OOP versus used-defined data types in SQL;
* **the problem of subtypes** - moving inheritance from code to database;
* **the problem of identity** - Java instance identity (`a==b`) and instance equality versus (`equals()`) versus identity of a database row;
* **the problems relating to associations** - `object references` versus `foreign key-constrained columns`;
* **the problem of data navigation** - moving along the object network in Java vs minimizing the number of requests to the database, `n+1 selects` problem.

## `Entity`
Entity is:
* a lightweight persistence domain object;
* typically represents a table in a relational database, each entity instance corresponds to a row in that table.

State of an entity is represented by:
* persistent fields;
* persistent properties.

Object/relational mapping annotations are used to map the entites and entity relationships to the relational data in the underlying data store.

Entity class:
* **has to be annotated with `javax.persistence.Entity` annotation**;
* have a public or protected, no-argument constructor;
* must not be declared `final`; the same applies to methods and persistent instance variables;
* must implement `Serializable` interface if an entity instance is passed by value as a detached object;
* may extend/be extended by both entity and non-entity classes;
* must have private, protected or package-private persistent instance variables Clients must access the entity's state through accessor or business methods.

## `EntityManager`
### Container-Managed Entity Managers
Container-managed entity manager means that an `EntityManager` instance's persistence context is automatically propagated by the container to all application components that use the `EntityManager` instance within a single Java Transaction API (JTA) transaction.

Properties:
* getting entity manager via `@PersistenceContext` annotation;
* the persistence context is automatically propagated with the current JTA transaction;
* `EntityManager` references are mapped to the same persistence unit and provide access to the persistence context within that transaction;
* Java EE container manages the lifecycle of container-managed entity managers;
* **directly injected `EntityManager` instances are not thread-safe**.

### Application-Managed Entity Managers
Application-managed entity manager means the lifecycle of `EntityManager` is managed by the appication. The persistence context is not propagated to application components.

Properties:
* getting entity manager via `@PersistenceUnit` and `EntityManagerFactory` class;
* each `EntityManager` creates a new, isolated persistence context;
* the `EntityManager` and its associated persistence context are created and destroyed explicitly by the application;
* this is advisable in case of multithreaded solutions.
* access to the JTA transaction manager has to be gained manually via `@Resource` annotation and `UserTransaction` class;

### Persisting Entity Instances
Being persistent means that entity's data is stored to the database when the transaction associated with the `persist` operation is completed.

New entity instances become managed and persistent either by:
* invoking `persist` method;
* a cascading `persist` operation invoked from related entities that have the `cascade=PERSIST` or `cascade=ALL` elements set in the relationship annotation.

## Transactions

Transaction classes:
* JDBC Transaction - transaction managed through a JDBC Connection.
* CMT Transaction - all work done in the context of a container managed transaction. CMT is not neccessarily container-managed, the point is that the transactions are managed by something other than Hibernate.

XA transaction = global transaction:
* May span multiple resources.
* Talking to multiple resources in a single transaction.
* Websphere, Weblogic or JBoss acting as a TransactionManager.
* Various resources - Oracle Sybase, IBM MQ, JMS, SAP acting as *transaction resources*.
* *Commit* - results are commited across all of the resources.
* *Rollback* - everything is rolled back across all resources.
* Two phase commit protocol is used.