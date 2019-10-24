# ANSI Isolation Levels

## Read uncommitted isolation

**Features:**
* Dirty reads are permitted.
* No lost updates.
* One transaction may not write to a row if another uncommited transaction has already written to it.
* Any transaction may read any row.

**Possible implementation:**
* Exclusive write locks.


