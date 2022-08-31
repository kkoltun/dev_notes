## JPA basics

### Problems addressed by the persistence tools

* **the problem of granularity** - classes in OOP versus used-defined data types in SQL;
* **the problem of subtypes** - moving inheritance from code to database;
* **the problem of identity** - Java instance identity (`a==b`) and instance equality versus (`equals()`) versus identity of a database row;
* **the problems relating to associations** - `object references` versus `foreign key-constrained columns`;
* **the problem of data navigation** - moving along the object network in Java vs minimizing the number of requests to the database, `n+1 selects` problem.

[Definitions below copied from here.](https://docs.jboss.org/hibernate/entitymanager/3.5/reference/en/html/architecture.html)

### EntityManagerFactory

An entity manager factory provides entity manager instances, all instances are configured to connect to the same database, to use the same default settings as defined by the particular implementation, etc. You can prepare several entity manager factories to access several data stores. This interface is similar to the SessionFactory in native Hibernate. 

### EntityManager

The EntityManager API is used to access a database in a particular unit of work. It is used to create and remove persistent entity instances, to find entities by their primary key identity, and to query over all entities. This interface is similar to the Session in Hibernate.

### Persistence context

A persistence context is a set of entity instances in which for any persistent entity identity there is a unique entity instance. Within the persistence context, the entity instances and their lifecycle is managed by a particular entity manager. The scope of this context can either be the transaction, or an extended unit of work.

### Persistence unit

The set of entity types that can be managed by a given entity manager is defined by a persistence unit. A persistence unit defines the set of all classes that are related or grouped by the application, and which must be collocated in their mapping to a single data store.

### Container-managed entity manager

An Entity Manager whose lifecycle is managed by the application.

### Application-managed entity manager

An Entity Manager whose lifecycle is managed by the container.

### JTA entity manager

Entity manager involved in a JTA transaction

### Resource-local entity manager

Entity manager using a resource transaction (not a JTA transaction).


### Entity

* A lightweight persistence domain object.
* Typically represents a table in a relational database, each entity instance corresponds to a row in that table.

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

### Persisting Entity Instances

Being persistent means that entity's data is stored to the database when the transaction associated with the `persist` operation is completed.

New entity instances become managed and persistent either by:
* invoking `persist` method;
* a cascading `persist` operation invoked from related entities that have the `cascade=PERSIST` or `cascade=ALL` elements set in the relationship annotation.
