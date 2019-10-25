# Java Persistence

> The data lives longer than any application.

SQL notes:
* [Join types](./sql/joins.md)

JDBC notes:
* [Basics](./jdbc/basics.md)
* [Statement types](./jdbc/statements.md)

JPA/Hibernate notes:
1. [Persistence life cycle](./hibernate/persistence_life_cycle.md)
2. [Operations on data](./hibernate/operations.md)
3. [Identifying detached instances](./hibernate/detached_state.md)
4. [Transaction isolation issues](./hibernate/transaction_isolation_issues.md)
5. [Transaction isolation levels](./hibernate/transaction_isolation_levels.md)
6. [Optimistic concurrency control](./hibernate/optimistic_concurrency_control.md)
7. [Pessimistic concurrency control](./hibernate/pessimistic_concurrency_control.md)

Problems addressed by persistence tools:
* **the problem of granularity** - classes in OOP versus used-defined data types in SQL;
* **the problem of subtypes** - moving inheritance from code to database;
* **the problem of identity** - Java instance identity (`a==b`) and instance equality versus (`equals()`) versus identity of a database row;
* **the problems relating to associations** - `object references` versus `foreign key-constrained columns`;
* **the problem of data navigation** - moving along the object network in Java vs minimizing the number of requests to the database, `n+1 selects` problem.

Materials:
* [Repository and Unit of Work Patterns](https://www.programmingwithwolfgang.com/repository-and-unit-of-work-pattern/)
* [A guide to accessing databases in Java](https://www.marcobehler.com/guides/a-guide-to-accessing-databases-in-java)

Todo:
* Relational model and theory;
* Data normalization;
* CAP theorem;
* Carthesian product;
* n+1 problem;
* Can I use UserTransaction with eg. HikariCP;
* Identifier generation strategies in Hibernate.

