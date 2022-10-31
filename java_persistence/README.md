# Java Persistence

> The data lives longer than any application.

See the code repository [here](https://github.com/kkoltun/dev_notes_code_java_persistence)

## Notes

Database basics:

1. [Basics](database_basics/basics.md)
2. [Joins + (exercises)](database_basics/joins.md)
3. [Transactions](database_basics/transactions.md)
4. [Dealing with concurrency in databases](database_basics/concurrency.md)
5. [Transaction isolation issues](database_basics/transaction_isolation_issues.md)
6. [Transaction isolation levels](database_basics/transaction_isolation_levels.md)
7. [Constraints](database_basics/constraints.md)
8. [Referential integrity constraints](database_basics/referential_integrity_constraints.md)
9. [Triggers](database_basics/triggers.md)

JDBC notes:
1. [Basics](./jdbc/basics.md)
2. [Statement types](./jdbc/statements.md)

General, quick JPA/Hibernate notes:
1. [Basics](hibernate/basics.md)
2. [EntityManager in the container environments](hibernate/container_environments.md)
3. [JPA and Hibernate](./hibernate/jpa_and_hibernate.md)

Concurrency control in JPA/Hibernate:
1. [Transactions in Hibernate - short overview](./hibernate/transactions_overview.md)
2. [Transactions and sessions in Hibernate - more details](./hibernate/transactions_details.md)
3. [Optimistic concurrency control](./hibernate/optimistic_concurrency_control.md)
4. [Pessimistic concurrency control](./hibernate/pessimistic_concurrency_control.md)

Entity states, operations:
1. [Operations on data](./hibernate/operations.md)
2. [The identity of detached state instances](./hibernate/detached_state.md)
3. [Persistence lifecycle](./hibernate/persistence_lifecycle.md)
4. [Unit tests of these mechanisms in a separate project](https://github.com/kkoltun/dev_notes_code_java_persistence)

Code and different tests:
1. [Entity states and persistence mechanisms](https://github.com/kkoltun/dev_notes_code_java_persistence/tree/master/src/test/java/com/hr/jpa)
2. [Race condition example (money transfer case)](https://github.com/kkoltun/dev_notes_code_java_persistence/blob/master/src/test/java/com/bank/ACIDRaceConditionTest.java)

Spring:
* [Guide to @Transactional by Marco Behler](https://www.marcobehler.com/guides/spring-transaction-management-unconventional-guide?utm_source=newsletter&utm_medium=sendy)

## Additional materials

Database courses:
* [Udemy](https://www.udemy.com/course/sqldatabases/?LSNPUBID=JVFxdTr9V80&ranEAID=JVFxdTr9V80&ranMID=39197&ranSiteID=JVFxdTr9V80-KHRhqAzlL6sA0ZbEL2.LQQ)
* [Pluralsight](https://www.pluralsight.com/courses/relational-database-design?aid=7010a000002BWqGAAW&promo=&utm_source=non_branded&utm_medium=digital_paid_search_google&utm_campaign=EMEA_Dynamic&utm_content=&gclid=Cj0KCQjw8amWBhCYARIsADqZJoWfIHbujoqTvoCraoT6Z-erIhC9JOHlYHUN6kuydgNzDaeiX-_ondsaAsKtEALw_wcB)
* [EDX](https://learning.edx.org/course/course-v1:StanfordOnline+SOE.YDB-SQL0001+2T2020/block-v1:StanfordOnline+SOE.YDB-SQL0001+2T2020+type@sequential+block@ee78af0439c642bf8a50ec250504a9c8/block-v1:StanfordOnline+SOE.YDB-SQL0001+2T2020+type@vertical+block@d6b8a5f169f34a7ea09e966b7eb16460)
* [Indexing](https://use-the-index-luke.com/)

Database books:
* [Database Internals book](https://www.amazon.pl/Database-Internals-deep-dive-distributed-systems/dp/1492040347/ref=asc_df_1492040347/?tag=plshogostdde-21&linkCode=df0&hvadid=504549506293&hvpos=&hvnetw=g&hvrand=13540985542486224997&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1011347&hvtargid=pla-680768627681&psc=1)
* [Data-intesive applications](https://www.amazon.pl/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321/ref=asc_df_1449373321/?tag=plshogostdde-21&linkCode=df0&hvadid=504448955493&hvpos=&hvnetw=g&hvrand=13540985542486224997&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1011347&hvtargid=pla-432535594773&psc=1)

Database text courses:
* [Geeks for geeks](https://www.geeksforgeeks.org/dbms/?ref=lbp)

Misc topics:
* [Repository and Unit of Work Patterns](https://www.programmingwithwolfgang.com/repository-and-unit-of-work-pattern/)
* [A guide to accessing databases in Java by Marco Behler](https://www.marcobehler.com/guides/a-guide-to-accessing-databases-in-java)
* [Hibernate architecture]([here](https://docs.jboss.org/hibernate/entitymanager/3.5/reference/en/html/architecture.html)

## To cover

* Relational model and theory;
* Data normalization;
* CAP theorem;
* n+1 problem;
* Identifier generation strategies in Hibernate.

