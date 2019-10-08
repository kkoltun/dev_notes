# Java Persistence

> The data lives londer than any application.

JPA/Hibernate notes:
* [Persistence life cycle](./persistence_life_cycle.md)
* [Operations on data](./operations.md)

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

