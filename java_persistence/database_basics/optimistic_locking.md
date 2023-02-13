## Optimistic Locking in databases (with references to JPA/Hibernate)

Separate topics, to investigate later:
1. [How to increment the parent entity version whenever a child entity gets modified with JPA and Hibernate](https://vladmihalcea.com/how-to-increment-the-parent-entity-version-whenever-a-child-entity-gets-modified-with-jpa-and-hibernate/)

---

### Introduction

Approaches:
* Pessimistic locking - it works, but not when you expect a lot of concurrent load, as noted before.
* Optimistic locking provided by the database - PostgreSQL provides optimistic locking, as it is a MVCC database.
* Optimistic locking provided by a framework, like Hibernate.

**Optimistic locking is all about having a separate column which somehow stores the snapshot (version) of the entity when you loaded it.**

For the optimistic locking in Postgres, check notes about it being a MVCC database.

In a JPA application, versioning has to be enabled to enable *first commit wins* mechanism.

TODO tests to be implemented:
* Excluding properties from versioning.
* `OptimisticLockType.Dirty`.
* Forcing a version increment.

### Implementing the Long Conversations

Using the optimistic locking in Hibernate (versioning mechanism) is **the only way** to implement Long Conversations, where session spans multiple database transactions.

Otherwise, if you open/close transactions during the business transactions, you will get Lost Update issues even if the Transaction Isolation Level is `SERIALIZABLE`.

Check the section about the Long Conversations [here](../hibernate/transactions_details.md) for more details.

Check the code testing and explaining Long Conversations [here](https://github.com/kkoltun/dev_notes_code_java_persistence/blob/9917586a7c2809dca6acd0127701dfbc3dccce0d/src/main/java/dev/karolkoltun/persistence/concurrency/optimistic/locking/HibernateOptimisticLockingLongConversationTests.java).

### Enabling versioning

The usual way to enable versioning is the `@Version` annotation.
In this case:

* If an `int`, `Integer`, `short` etc. field is annotated, a simple counter is created. Hibernate wraps and starts from zero again if the version number reaches the limit of the data type.
* If a date field is annotated, a timestamp is created. It is slightly less safe, because two transactions could both load and update the same `Item` in the same millisecond. Furthermore, retrieving the current time from JVM isn't necessary safe in a clustered environment.

Alternative to version numbers and timestamps is an annotation `@OptimisticLocking(type = OptimisticLockType.ALL)` used with `@DynamicUpdate` on a whole entity class.
In this case:
1. Hibernate will execute a dynamically created `UPDATE` with `WHERE` clause explicitly set last known entity property values to flush a modifications.
2. If any concurrent transaction has modified any of these values or even deleted the row, the statement returns zero updated rows. In this case Hibernate will throw an exception at flush time.
3. To make Hibernate look only for modification conflicts use `OptimisticLockType.DIRTY`.

#### Versioning features

What modifications trigger the increment of the entity's version:

* The version is incremented whenever an entity instance is dirty. This includes any single-valued (`String`, `int`) properties and embedded ones (`Address`).
* This does not include `@OneToMany` and `@ManyToMany` association collections that have been made read-only with `mappedBy`. Any changes done to these collections will not increment the version of the owning entity instance.
* Changes made to properties annotated with `OptimisticLock(excluded = true)` will not increase entity version.

Making particular reads repeatable:

* Use JPA `Query` interface with method `Query#setLockMode()`.
* This will make Hibernate check each loaded item at flush time. If the version of any item has already changed or row no longer exists, an `OptimisticLockException` is thrown.

Forcing a version increment:

* Sometimes even loading should increment the entity version. In this case use `LockModeType.OPTIMISTIC_FORCE_INCREMENT` in `EntityManager#find()` method arguments.
* This is useful when the client inserts or modifies data and wants the version of some root instance of an aggregate to be incremented (eg. while inserting a new maximal `Bid`, force an increment of the root `Item` entity version.
* Note that if the exemplary `Bid#item` entity association would be changed from `@ManyToOne` to `@ElementCollection` of `Item#bids`, adding a `Bid` to the collection would increment the `Item` version. It is a matter of parent/child ambiguity.
