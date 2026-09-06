## Database scaling

Additional links:
* [Source article](https://www.freecodecamp.org/news/understanding-database-scaling-patterns/)
* [Quora discussion](https://www.quora.com/Whats-the-difference-between-sharding-DB-tables-and-partitioning-them)
* [Instagram sharding ideas a couple of years ago](https://instagram-engineering.com/sharding-ids-at-instagram-1cf5a71e5a5c)

Scenario:
1. You have an application where you serve the data to the users.
2. This is a single-instance application with a single database machine.
3. Things start to get worse:
   1. API latency increases.
   2. Some transactions deadlock or starve.
   3. The application is taking more time to respond.*

### First step - query optimization and Connection Pool implementation

#### Denormalization in highly used tables.

The database is probably heavily normalized, so you introduce some reduntant columns - especially for those columns which appear frequently in `WHERE` or `JOIN ON` clause in queries.
The result is that the queries become smaller and the application layer is adding the results up.

#### Tweaking around database connections

Use database connection pools, cache database connections etc. Even multiple application threads can use the same database connection.

### Second step - vertical scaling or Scale Up

*The first step made things faster, but there is more and more data in the database.
It is constantly running out of memory, processor usage is very high all the time.*

You add some more RAM and disk space to the database server.
This is an example of vertical scaling or scaling up the system.

Steps to do this (instead of moving all the data at once):
1. Allocate a bigger machine.
2. Set the new machine as `replica` to the existing machine (`primary`).
3. The replication will happen naturally over time.
4. Once the replication is done, promote the new machine to `primary` and take the older machine offline.

### Third step - replication with or CQRS

*One big machine is not able to handle all `read/write` requests. In most of the cases, any companies needs transactional capability on `write`, but not on `read` operations.*

You separate the `read` & `write` operations, while accepting that a little bit of inconsistent or delayed `read` operations are OK for the business.

Steps:
1. Launch two more big machines & set them up as `replica` to the current machine.
2. Database replication will take case of distributing data from `primary` to `replica` machines.
3. All read queries (`Q` in CQRS) are navigated to one of the `replica` instances.
4. All write queries (`C` in CQRS) are navigated to the `primary` instance.

### Fourth step - multi-primary replication

*The data replication takes too long. The delay between the write step (eg. posting a payment) and the read step (eg. seeing the actual result) is too long.*

1. You start distributing the `write` operations too. In the `multi-primary` configuration, all the machines can work as both `primary` and `replica`. They create a circle of replicas: `A -> B -> C -> D -> A`, meaning `B` can replicate data from `A`, `C` - from `B` etc.
2. You can write data to any node. While reading the data, you can broadcast the query to all nodes, whoever replies return that.
3. All nodes have the same database schema, set of tables, index etc.
4. All nodes use the same set of IDs, so collisions need to be prevented (`UUID`, `GUID`).

Downsides:
1. The `read` operations can suffer - they involve broadcasting query and getting the correct result.

### Fifth step - partitioning

Moving the data to another database schema basing on the functionality.
Different database can host data categorized by different functionality.
The, the backend layer aggregates the results.

### Sixth step - horizontal scaling (sharding)

Sharding is a special type of partitioning, where data is spread across multiple computers.
There is a `sharding key` that refers to a machine.
Each machine can have their own replicas etc.

Downsides of sharding:
1. The queries get much more complex.
2. Range queries could span different shards.
3. Joins become difficult or maybe impossible. How can you join tables from another database on another machine?

Handling with the downsides - having two sets of data - one for complex queries, one for simple queries (sharded).
Google Datastore does not support joins or more complex queries. At the same time it is sharded and replicated.
