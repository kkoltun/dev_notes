# Relational design

Desing "anomalies":
* Redundancy - capture the same information many times.
* Update anomaly - you can update facts differently in different places, leaving the database in an inconsistent state.
* Deletion anomaly - removing only part of the data.

## Design by decomposition

* Start by creating "mega" relations that contain all the data.
* **Decompose** into smaller, better relations with same info.
* We can do decomposition automatically - we define the "mega" relations, properties and system decomposes it. The final relations satisfy **normal form**.

Properites and Normal Forms:
* Functional dependencies => Boyce-Codd Normal Form
* Functional dependencies + Multivalued dependencies => Fourth Normal Form 
* Fourth Normal Form is more strict than Boyce-Codd Normal Form (BCNF).

## Functional Dependencies and BCNF example

Example table of student applications:

```sql
Apply(studentId, studentName, universityName)
```

* There is redundancy, Update and Delete Anomalies.
* We are storing `studentId - studentName` pairs once for each university.

There is a Functional Dependency from `studentId` to `studentName` (`studentId => studentName`):
* Each `studentId` always has the same `studentName`. However, this does not work the other way round, same `studentName` could have different `studentId` values. This is why, the dependency has a direction.
* We should store the `studentName` for each `studentId` only once.

Boyce-Codd Normal Form:
* If `A => B` then `A` is a key.

Result:
* Decompose: `Student(studentId, studentName)` and `Apply(studentId, universityName)`.

## Multivalued Dependencies and 4NF

Example table of student applications:

```sql
Apply(studentId, universityName, highSchoolName)
```

* There is redundancy, Update and Delete Anomalies.
* Multiplicative effect - if a student is in U universities and studied in H high schools, there are U*H tuples.
* There are no functional dependencies, so this is not addressed by BCNF.

There is a multivalued dependency from `studentId` to `universityName` (`studentId =>> universityName`, double arrow here):
* Given `studentId` has every combination of `universityName` with `highSchoolName`.
* We should store each `universityName` and each `highSchoolName` with an `studentId` only once.

Fourth Normal Form:
* If `A =>> B` then `A` is a key.

Result:
* Decompose: `Apply(studentId, universityName)` and `HighSchool(studentId, highSchoolName)`.