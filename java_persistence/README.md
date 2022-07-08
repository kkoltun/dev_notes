# Java Persistence

> The data lives longer than any application.

See the code repository [here](https://github.com/kkoltun/dev_notes_code_java_persistence).

SQL notes:
* [Join types](./sql/joins.md)

JDBC notes:
* [Basics](./jdbc/basics.md)
* [Statement types](./jdbc/statements.md)

JPA/Hibernate notes:
* [Loose notes on JPA](jpa.md)
* [JPA vs Hibernate](./hibernate/jpa_vs_hibernate.md)
* [Persistence life cycle](./hibernate/persistence_life_cycle.md)
* [Operations on data](./hibernate/operations.md)
* [Identifying detached instances](./hibernate/detached_state.md)
* [Transaction isolation issues](./hibernate/transaction_isolation_issues.md)
* [Transaction isolation levels](./hibernate/transaction_isolation_levels.md)
* [Optimistic concurrency control](./hibernate/optimistic_concurrency_control.md)
* [Pessimistic concurrency control](./hibernate/pessimistic_concurrency_control.md)

Spring:
* [Guide to @Transactional by Marco Behler](https://www.marcobehler.com/guides/spring-transaction-management-unconventional-guide?utm_source=newsletter&utm_medium=sendy)

Problems addressed by the persistence tools:
* **the problem of granularity** - classes in OOP versus used-defined data types in SQL;
* **the problem of subtypes** - moving inheritance from code to database;
* **the problem of identity** - Java instance identity (`a==b`) and instance equality versus (`equals()`) versus identity of a database row;
* **the problems relating to associations** - `object references` versus `foreign key-constrained columns`;
* **the problem of data navigation** - moving along the object network in Java vs minimizing the number of requests to the database, `n+1 selects` problem.

Materials:
* [Repository and Unit of Work Patterns](https://www.programmingwithwolfgang.com/repository-and-unit-of-work-pattern/)
* [A guide to accessing databases in Java by Marco Behler](https://www.marcobehler.com/guides/a-guide-to-accessing-databases-in-java)

Todo:
* Relational model and theory;
* Data normalization;
* CAP theorem;
* Cartesian product;
* n+1 problem;
* Identifier generation strategies in Hibernate.

