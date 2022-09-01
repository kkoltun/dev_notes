## Persistence Life Cycle

### Basic terms

#### Persistence lifecycle

These are the states an entity goes through during its life. 

#### Unit of work

This is a set of (possibly) state-changing operations considered one (usually atomic) group.

#### Persistence service

A service that provides persistence context.

#### Persistence context

Overall it can be treated as a service that remembers all the modifications and state changes made to the data in a particular unit of work.

### Entity Lifecycle

![Entity lifecycle](./images/entity_lifecycle.svg)

#### Transient state

* Instance created with `new` and garbage-collected when it is no longer needed.
* No rollback mechanisms.
* Transition from transient to persistent means becoming managed.
* From transient to persistent: calling `EntityManager#persist` or creating a reference of an already-persistent instance with enabled cascading state for that mapped association.

#### Persistent state

* Instance has a representation in the database.
* Instance is stored in the database or will be stored when unit of work completes.
* Instance with database identity.
* Instance's database identifier is set to primary key value of the database representation.
* Instance always associated with a persistence context.

#### Transitions to the persistent state

* Creating instance and calling `EntityManager#persist`.
* Creating a reference to the object from another persistent instance that is already managed.
* Retrieving from the database by executing a query, identifier lookup.
* Navigating the object graph starting from another persistent instance.

#### Removed state

* The provider will delete the entity instance from the database at the end of a unit of work.
* Result of calling `EntityManager#remove()` or deleting reference from a mapped collection with `orphan removal` turned on.

#### Detached state

* State entered when after getting the persistent instance, the unit of work is ended, the persistence context is closed and the application still has a *handle* - reference to the loaded instance.
* The instance can be discarded and garbage-collected. 
* The instance can be worked on and then made persistent by calling `merge()`.

### Persistence context

* `EntityManager` has a persistence context.**
* Persistence context is created by calling `EntityManagerFactory#createEntityManager()`.
* Persistence context is closed by calling `EntityManager#close()`.
* There is one `EntityManagerFactory` per persistence unit.
* The scope of the persistence context demarcates the unit of work.

#### Automatic dirty checking:

* Detecting which persistent entity instances have been modified by the application.
* When unit of work completes, usually the state held in memory is propagated to database.

#### Persistence context as a `first-level cache`:

* All the entitiy instances handled in a particular unit of work are remembered.
* If lookup by identifier is requested, Hibernate will first check if the entity instance is present in the persistence context.

#### Persistence context cache ensures:

* The persistence context is not vulnerable to stack overflows caused by circular references in an object graph.
* There can never be conflicting representations of the same database row at the end of a unit of work.
* Changes made in a particular persistence context are immediately visible to all other code executed inside that unit of work and its persistence context.
* Only one instance represents a particular database row within one persistence context (other idea is process-scoped identity).

### Creating `EntityManager`

When `EntityManagerFactory#createEntityManager()` is called:

* The `EntityManager` looks for an ongoing transaction on the same thread and *joins* the transaction by listening to transaction events.
* If there is no transaction going, it enters a special *unsynchronized* mode. In this mode, JPA will not automatically flush the persistence context.
* If you want the `EntityManager` to join the transaction, create it in the same thread as the transaction.
