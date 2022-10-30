## Session and Transaction in Hibernate

[Based on this documentation page](https://docs.jboss.org/hibernate/core/3.3/reference/en/html/transactions.html) and [this archived page](https://developer.jboss.org/docs/DOC-13951#).

### Questions for this article

1. What is the SessionFactory?
2. What is the Session?
3. What is the Unit of Work? Is it different than a physical database transaction? What is the scope of it?
4. What is the session-per-operation pattern?
5. What is the session-per-request pattern? Draw a diagram for this pattern.
6. What are *long coversations*, why do we need them?
7. What is the naive impl. of *long conversations*?
8. How *long conversations* can implemented safely in general? What Hibernate features help here?
9. What are two patterns for implementing *long conversations*? Draw a diagram for these two patterns.
10. What are common antipatterns and possible issues with `Session` objects (3 examples)? 

---

### Objects

`SessionFactory`:

* Expensive-to-create.
* Threadsafe.
* Intended to be shared by all application threads.
* Usually created only once from a `Configuration` instance.

`Session`:

* Inexpensive.
* Non-threadsafe.
* Should be used once and then discarded for eg. a single request.

---

### Unit of Work

[Check here for a detailed description from Martin Fowler.](https://martinfowler.com/eaaCatalog/unitOfWork.html)

* Martin Fowler describes it as " [maintaining] a list of objects affected by a business transaction and coordinates the writing out of changes and the resolution of concurrency problems".
* This a transactions (in an abstract notion), but fulfilling it might often span multiple physical database transactions.
* Usually also called a "business transaction".

---

### Session-per-operation antipattern

* Opening and closing a `Session` for every simple database call in a single thread.
* Doing the same for database transactions.
* **Database calls in an application are made using a planned sequence and grouped into atomic units of work.**
* Doing these operations in auto-commit mode (every single SQL gets comitted) is useless.
* **Hibernate disables or expects the application server to disable the auto-commit mode immediately.**

---

### Session-per-request pattern

![Session-per-request diagram](https://developer.jboss.org/servlet/JiveServlet/showImage/102-13951-3-22002/session_request.png)

* Opening and closing a `Session` for every request that came from the client to the server.
* All database operations are executed in this unit of work.
* On completion and once the response for the client has been prepared, the session is flushed and closed.
* One single database transaction; starts when session is opened; committed when session is closed; one-to-one relationship.

---

### Long conversations

* The session-per-request not always works. Sometimes there are series of interactions with the users interleaved by database accesses.
* Scenario:
	1. User accesses the screen. The data has been loaded using a particular `Session` and database transaction.
	2. User is free to modify the screen.
	3. After 5 minutes, user clicks "Save".
	4. User expects their modiifcations to be made persistent.
	5. **User expects that they were the only people editing this information.**
	6. **User expects that no conflicting modification has occurred.**

#### Naive implementation of long conversations (antipattern)

* Keep the `Session` and the transaction open during user think time.
* Keep the locks held in the database to prevent concurrent modification and to guarantee isolation and atomicity.
* **Lock contention would not allow the application to scale with the number of concurrent users.**

#### Better implementation - key points

* Use several database transactions to implement the conversation.
* Application is partially resposible of maintaining isolation of business processes.
* **Atomictiy = only one of the transactions actually stores the updated data; the rest are only reading the data.**

Use of the Hibernate features to acheive this:
1. **Automatic versioning** - automatic optimistic concurrency control. The concurrent modifications are checked at the end of the conversation.
2. **Detached objects** - objects can be detached and then reattached to persist modifications. [**session-per-request-with-detached-objects pattern**] -
3. **Extended (or Long) Session** - the `Session` can be disconnected from the underlying JDBC connection after the database transaction has been comitted. Then, it can be reconnected when new client request comes.

#### Session-per-request-with-detached-objects pattern

![Session-per-request-with-detached-objects diagram](https://developer.jboss.org/servlet/JiveServlet/showImage/102-13951-3-22003/session_detachedobjects.png)

* Use **automatic versioning** and **detached objects**.
* Steps:
  1. Load all instances in the beginning.
  2. Detach them during user think time.
  3. Reattach them when they are finally saved.
  4. Persist the modifcations using reattached instances. Automatic versioning cares about the isolation of the concurrent modifications.

#### Session-per-conversation-pattern

![Session-per-request-with-detached-objects diagram](https://developer.jboss.org/servlet/JiveServlet/showImage/102-13951-3-22004/session_conversation.png)

* Use **automatic versioning** and **detached objects**.
* Steps:
  1. Disconnect the Hibernate `Session` from the JDBC connection after the database transaction has been comitted.
  2. Reconnect when a new client request comes.
  3. When persisting entities, you don't have to reattach them (as in session-per-request-with-detached-objects).
  4. Automatic versioning again takes care of isolation.
  5. **The `Session` will not be allowed to be flushed automatically, but explicitly.**

#### Other antipatterns

These ones are usually antipatterns: session-per-user-session, session-per-application. Potential problems:
* The `Session` is not thread-safe. Things that work concurrently (HTTP requests, beans, workers) will cause race conditions if you share `Session` objects. If you keep the `Session` in the `HttpSession`, the user could theoretically click fast enough to cause two threads share the same `Session` object.
* An exception thrown by Hibernate means you have to rollback the database transaction and close the `Session` immediately. If you bind it to the application, you have to stop the application.
* The `Session` is the first-level cache. It caches every object that is in a persistent state. If you keep it open for a long time and load too much data, it will grow endlessly and finally throw `OutOfMemoryException`.

See [here](https://docs.jboss.org/hibernate/core/3.3/reference/en/html/transactions.html#transactions-basics-issues) for details and possible solutions.

---

### Database transaction demarcation

**No communication with the database can occur outside of a database transaction (even if you are using auto-commit mode).**

Two types of environments:
* Non-managed environment - the application developer has to manually set transaction boundaries (begin, commit or rollback the transactions).
* Managed environment - usually provides container-manager transactions; the transaction assembly is defined declaratively (deployment descriptors, session beans etc.).

Quick facts:
* The call to `Transaction::commit()` automatically triggers the synchronization, so you don't have to call `Session::flush()` explicitly. This is controlled by `FlushMode` property for the session.
* The call to `Session::close()` mainly releases the JDBC connections.
* There are different idioms (check [here](https://docs.jboss.org/hibernate/core/3.3/reference/en/html/transactions.html#transactions-demarcation) to see code):
	* Non-managed environment idiom.
	* Non-managed environment idiom with getCurrentSession()
	* BMT idiom
	* BTM idiom with getCurrentSession()
	* CMT idiom

See idioms for each type on this page.

---

### Optimistic and pessimistic concurrency control

See other notes for details.
