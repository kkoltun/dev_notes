# (Integrity) Constraints:

* Constraint allowable database states.
* Static behavior.

### Classification

* Non-null
* Key
* Referential integrity (foreign key)
* Attribute-based (constrain a value of the attribute)
* Tuple-based (how the values in the tuple relate to each other)
* General assertion (constrain values across tables and tuples)

### Declaration

  * With original schema - checked after bulk loading.
  * Later - checked on the current state of the database. 

### Enforcement

  * Checked automatically on every "potentially dangerous" modification.
  * Deferred constraint checking - needed when we want to violate constraints for some time, but then leave the database in the right state in the end (checked when transaction is committed).
  * If the query can potentially violate the constraint, but effectively modifies no rows, it will not throw an error (eg. `UPDATE Employee SET first_name = NULL WHERE id = <non_existent_id>`).

### `NULL` value vs `UNIQUE` constraint

Most databases allow multiple NULLs in a column with unique constraint.  From the POSTGRESQL manual:
> **In general, a unique constraint is violated when there is more than one row in the table where the values of all of the columns included in the constraint are equal.**
>
> However, **two null values are not considered equal in this comparison**. That means even in the presence of a unique constraint it is possible to store duplicate rows that contain a null value in at least one of the constrained columns. 

SQL Server 2005 and older, on the other hand, does not allow multiple NULL values.

### Examples

Create the table:

```sql
CREATE TABLE location_rent (
    rent_id INT (11) UNSIGNED NOT NULL,
    location_id INT (11) UNSIGNED UNIQUE,
    owner_name VARCHAR(30) NOT NULL,
    rent_amount DECIMAL(8, 2) NOT NULL CHECK(rent_amount > 0 AND rent_amount < 1000000),
    PRIMARY KEY (rent_id),
    CHECK (owner_name != 'Karol' OR rent_amount > 5000)
);
```

This is allowed despite the `UNIQUE` constraint - `NULL` is not equal to another `NULL` (at least in Mysql and Postgresql):

```sql
INSERT INTO location_rent (rent_id, location_id, owner_name, rent_amount)
VALUES (1, NULL, 'Tom', 2500),
       (2, NULL, 'Amy', 4000);
```

This is disallowed by the table check - when renting from Karol, the `rent_amount` must be bigger than 5000:

```sql
INSERT INTO location_rent (rent_id, location_id, owner_name, rent_amount)
VALUES (1, 1, 'Karol', 1000);
```

This is disallowed by the `rent_amount` check - it must be bigger than zero:

```sql
INSERT INTO location_rent (rent_id, location_id, owner_name, rent_amount)
VALUES (2, 2, 'Mark', -10);
```