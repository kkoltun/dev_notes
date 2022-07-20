# Referential integrity constraints

**No "dangling pointers" are allowed.**

Referential integrity from `R.A` to `S.B`:
* Each value in column `A` table `R` must appear in column `B` table `S`.
* A is called "foreign key".
* B is usually required to be the primary key for table S or at least be unique.
* Potentially violating modifications:
    * Insert into R
    * Delete from S
    * Update R.A
    * Update S.B

## Special actions

There are some actions which can be differently handled by the database, depending on the configuration of the constraint.

### Delete from S

The deleting from referenced table can be differently configured and handled:

* `Restrict`: default option, if deletion is done on the referenced table and the constraint becomes violated, throw an error and disallow the deletion.
* `Set NULL`: take the referencing rows and set the attributes to `NULL` automaticall (`R.A` gets set `NULL`).
* `Cascade`: take the referencing rows and remove them (remove `R` row).

**Cascade can go multiple steps down!**

### Update S.B

The updating can also be differently configured and handled:

* `Restrict`
* `Set NULL`
* `Cascade`: when referenced value is updated, update also the referencing values (`S.B` gets updated to `X`, update also all referencing `R.A` values to `X`).

### Conflicting constraints

We could try to set conflicting constraints - `cName` set to `NOT NULL` and then the `FOREIGN KEY` set to `ON DELETE SET NULL`:

```sql
CREATE TABLE Apply
(
    sID      INT UNSIGNED,
    cName    VARCHAR(255) NOT NULL,
    major    VARCHAR(255),
    decision VARCHAR(255),
    CONSTRAINT FOREIGN KEY (sID) REFERENCES Student (sID),
    CONSTRAINT FOREIGN KEY (cName) REFERENCES College (cName) ON DELETE SET NULL
);
```

MySQL does not allow this.

### Referential integrity in the same database

This is possible:

```sql
CREATE TABLE T
(
    A INT,
    B INT,
    C INT,
    PRIMARY KEY (A, B),
    FOREIGN KEY (B, C) REFERENCES T (A, B) ON DELETE CASCADE
);
```