# JPA
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
* a acscading `persist` operation invoked from related entities that have the `cascade=PERSIST` or `cascade=ALL` elementts set in the relationship annotation.
