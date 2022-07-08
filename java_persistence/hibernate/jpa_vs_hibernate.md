JPA vs Hibernate

JPA:
* Java Persistence API, initially released in May 2006
* It is a specification, not implementation.
* It is a set of rules and guidelines to set interfaces for implementing object-relational mapping (ORM).

Hibernate:
* Framework initially released in May 2007.
* It is an implementation of JPA guidelines.

JPA | Hibernate
--- | ---
`javax.persistence` package | `org.hibernate` package
As an object-oriented query language, it uses Java Persistence Query Language (JPQL) to execute database operations. | As an object-oriented query language, it uses Hibernate Query Language (HQL) to execute database operations.
Use `EntityManager` to interact with the mapped entity classes. | Use `Session` to interact with the mapped entity classes.

JPQL is heavily-inspired-by subset of HQL. A JPQL query is always a valid HQL query, the reverse is not true however.
