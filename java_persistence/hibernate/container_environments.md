## EntityManager in the container environments

*Some parts here are copied/rewritten from [here](https://docs.jboss.org/hibernate/entitymanager/3.5/reference/en/html/architecture.html).*

Examples:
* EJB3
* CDI (Java Context and Dependency Injection)

External links:
* [Types of Entity Managers: Application-managed EntityManager](https://www.javacodegeeks.com/2013/03/types-of-entity-managers-application-managed-entitymanager.html).
* [Container vs Application Managed EntityManager](https://www.byteslounge.com/tutorials/container-vs-application-managed-entitymanager)

### Container-managed entity manager

Container-managed entity manager means that an `EntityManager` instance's persistence context is automatically propagated by the container to all application components that use the `EntityManager` instance within a single Java Transaction API (JTA) transaction.

Properties:

* Getting entity manager via `@PersistenceContext` annotation.
* The persistence context is automatically propagated with the current JTA transaction.
* `EntityManager` references are mapped to the same persistence unit and provide access to the persistence context within that transaction.
* This way, the application components do not have to pass the reference to the `EntityManager` instance to each other in order to make changes within a single transaction.
* Java EE container manages the lifecycle of container-managed entity managers.
* The `EntityManager` instances are not thread-safe, so injecting them directly will work correctly only in a thread-safe environment.

### Application-Managed Entity Managers

Application-managed entity manager means the lifecycle of `EntityManager` is managed by the appication. The persistence context is not propagated to application components.

Properties:

* Getting the entity manager via the `@PersistenceUnit` and the `EntityManagerFactory` class.
* Each `EntityManager` creates a new, isolated persistence context.
* The `EntityManager` and its associated persistence context are created and destroyed explicitly by the application.
* The transaction demarcation is added manually.
* This is useful when dealing with multithreading. While the `EntityManager` instances are not thread-safe, so they cannot be directly injected then. The `EntityManagerFactory` instances are thread-safe.
* The access to the JTA transaction manager has to be gained manually via `@Resource` annotation and `UserTransaction` class which has the `begin()`, `commit()` and `rollback()` methods.

More information [here](https://docs.oracle.com/cd/E19798-01/821-1841/bnbra/index.html).

Example:

```java
class ApplicationManagedEntityManagerExample {
    // First, get the factory.
    @PersistenceContext
    EntityManagerFactory emf;

    // This will be the entity manager created by the factory.
    EntityManager em;

    // Manually gain access to the JTA transaction manager.
    @Resource
    UserTransaction utx;

    void example() {
        em = emf.createEntityManager();

        try {
            utx.begin();

            em.persist(someEntity);
            em.merge(anotherEntity);
            em.remove(thirdEntity);

            utx.commit();
        } catch (Exception e) {
            utx.rollback();
        }
    }
}
```

### Persistence Context scope

Two approaches:
1. Binding the persistence context to the transaction boundaries:
2. Keeping the persistence context available across several transactions.

#### Transaction-bound persistence context

* This is a more common approach. 
* This is only doable when JTA transactions are used. 
* The persistence context is associated with the JTA transaction life cycle. 
* Starting/opening context: When an entity manager is invoked, the persistence context is also opened, if there is no persistence context associated with the current JTA transaction. Otherwise, the associated persistence context is used.
* Closing context: the context ends then the JTA transaction completes.

So here, during the JTA transaction, an application will be able to work on managed entities of the same persistence context. In other words, you don't have to pass the entity manager's persistence context across your managed beans (CDI) or EJBs method calls, but simply use dependency injection or lookup whenever you need an entity manager.

#### Extended persistence context

You can also use an extended persistence context.
This can be combined with stateful session beans, if you use a container-managed entity manager: the persistence context is created when an entity manager is retrieved from dependency injection or JNDI lookup, and is kept until the container closes it after the completion of the Remove stateful session bean method.
This is a perfect mechanism for implementing a "long" unit of work pattern.
For example, if you have to deal with multiple user interaction cycles as a single unit of work (e.g. a wizard dialog that has to be fully completed), you usually model this as a unit of work from the point of view of the application user, and implement it using an extended persistence context.

Example [here](https://www.adam-bien.com/roller/abien/entry/building_perfect_anti_facades_almost).

### Persistence context propagation

Persistence context propagation occurs for container-managed entity managers.

In a transaction-scoped container managed entity manager (common case in a Java EE environment), the JTA transaction propagation is the same as the persistence context resource propagation. In other words, container-managed transaction-scoped entity managers retrieved within a given JTA transaction all share the same persistence context. In Hibernate terms, this means all managers share the same session.

Important: persistence context are never shared between different JTA transactions or between entity manager that do not came from the same entity manager factory. There are some noteworthy exceptions for context propagation when using extended persistence contexts:

* If a stateless session bean, message-driven bean, or stateful session bean with a transaction-scoped persistence context calls a stateful session bean with an extended persistence context in the same JTA transaction, an IllegalStateException is thrown. 
* If a stateful session bean with an extended persistence context calls as stateless session bean or a stateful session bean with a transaction-scoped persistence context in the same JTA transaction, the persistence context is propagated. 
* If a stateful session bean with an extended persistence context calls a stateless or stateful session bean in a different JTA transaction context, the persistence context is not propagated. 
* If a stateful session bean with an extended persistence context instantiates another stateful session bean with an extended persistence context, the extended persistence context is inherited by the second stateful session bean. If the second stateful session bean is called with a different transaction context than the first, an IllegalStateException is thrown. 
* If a stateful session bean with an extended persistence context calls a stateful session bean with a different extended persistence context in the same transaction, an IllegalStateException is thrown.