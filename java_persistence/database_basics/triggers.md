# Triggers:

## Features

* Monitor database changes, check conditions and initiate actions.
* Dynamic behavior.
* "Event-Condition-Action" - when **event** occurs, check **condition**; if true, do **action**.
* Why use them:
    * Move the logic from the application to the DBMS.
    * Enforce constraints:
        * Not every case can be covered by the constraints.
        * Sometimes you can actually avoid throwing error from violated constraint and actually repair the data (in the **action** phase).
* Trigger levels:
  * Row-level trigger (`for each row` is present) - activated for each modified/deleted/inserted row.
  * Statement-level trigger - activated only once per event.
* Important to think about:
  * Which trigger goes first when they are activated at the same time.
  * Triggers activating other triggers (chaining), self-triggering, cycles, nested invocations.
* Implementations vary significantly, eg. some databases have only row-level triggers.

## Creating triggers

```sql
CREATE TRIGGER name
BEFORE | AFTER | INSTEAD OF events
[ referencing variables ]
[ FOR EACH ROW ]
WHEN (condition)
ACTION
```

* `BEFORE` or `INSTEAD OF` can be quite tricky
* events: `INSERT ON T`, `DELETE ON T`, `UPDATE [ of C1, C2, ... ] ON T`.
* if `FOR EACH ROW` is present, the trigger will be executed for each modified row.
* `[ referencing variables ]` - reference the data that was modified:
  * Keywords:
    * `OLD ROW AS` - modified/deleted tuple, accessible only from the `FOR EACH ROW`.
    * `NEW ROW AS` - modified/inserted tuple, accessible only from the `FOR EACH ROW`.
    * `OLD TABLE AS` - set of the tuples that have been modified/deleted.
    * `NEW TABLE AS` - set of the tuples that have been modified/inserted.
  * Restrictions basing on the operations:
    * Insertion trigger - only `NEW ROW` and `NEW TABLE`.
    * Deletion trigger - only `OLD ROW` and `OLD TABLE`.
    * Update trigger - both `OLD ...` and `NEW ...`
  * Restrictions basing on the trigger level:
    * Row-level trigger - can have access to both `... ROW` and `... TABLE` (depending on the operation).
    * Statement-level trigger - can have access to only `... TABLE`.
* `condition` - like general level assertion; it is an SQL condition on the database.
* `ACTION` - this heavily depends on the database implementation.

### Trigger example

This trigger simulates the referential integrity constraint on the tables `R` and `S`.

`R.A` references `S.B`, cascaded delete, so the referential integrity requires the `R` to be deleted along with the deleted `S` row.

Row-level trigger:

```sql
CREATE TRIGGER Cascade
AFTER DELETE ON S
-- We have access to the OLD ROW, because this is row-level
REFERENCING OLD ROW AS OLDROW
FOR EACH ROW
-- No condition
DELETE FROM R WHERE A = OLDROW.B
```

Statement-level trigger:

```sql
CREATE TRIGGER Cascade
AFTER DELETE ON S
-- All the deleted rows should be here, no access to the OLD ROW
REFERENCING OLD TABLE AS OT
-- No FOR EACH ROW
-- No condition
DELETE FROM R WHERE A IN (SELECT B FROM OT)
```