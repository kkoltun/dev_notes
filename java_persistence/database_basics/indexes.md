## Indexes

* Primary mechanism to get improved performance on a database.
* Persistent data structure, stored in database.
* They speed up querying for data: instead of scanning the entire table, we go to the exact rows. 
* Some systems automatically build indexes on the `PRIMARY KEY` attributes. Sometimes on `UNIQUE` attributes too.

### Underlying data structures

Balanced trees (B trees, B+ trees):

* These can be used for all sorts of comparisons in the queries: `A = Val`; `A < Val`; `Val1 <= A <= V2`.
* Logarithmic time operations.
* Oracle DB implementation - B-tree index contains an entry for each value in the index key along with a disk address of the row where the value is stored.

Hash tables:

* These can be used only for `A = Val` queries:
* Constant time operations.

### Downsides of indexes

1. They take extra space (probably marginal in most cases).
2. Index creation takes time and space (fairly time-consuming operation).
3. Index maintenance - when values in the table change, the indexes have to be modified to reflect those changes (this can be really costly when table is modified frequently).

### Benefits

The benefits depend on:

1. Size of the table (and possibly layout).
2. Data distributions.
3. Query vs update load.