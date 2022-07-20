# Loose notes on relational databases

**Database** = set of named **relations** (or **tables**).

Each relation has a set of named **attributes** (or **columns**).

Each **tuple** (or **row**) has a value for each attribute.

Each attribute has a **type** (or **domain**).

**Schema** = structural description of relations in the database.

**Instance** = actual contents at given point in time.

**Key** = attribute (or set of attributes) whose value is unique in each tuple.

**SQL** is based on the **relational algebra**.

---

SQL query:

```
SELECT A1, A2, ..., AN [3]
FROM R1, R2, ..., RM   [1]
WHERE condition        [2]
```

1. These are the relations, think about them first.
2. Combine filter.
3. What to return.

π (A1, ... AN) σ (condition) (R1 x ... RN)

---

Relational algebra:

* Takes relation as an input and generates relation as output.
* The relation is a set, so there are no duplicates.
* The cross product does not need a specification of the join condition.

SQL:

* It is based on a multi-set, so there are duplicates.
* An easy to pose query might not be easy for the DBMS to do efficiently and vice versa.
* You need to manually set the cross product join condition (eg. `SELECT * FROM Employee, Departament WHERE Employee.dept_id = Departament.dept_id`).

**Compositionality** = queries return relations (you can work further on the results).

The same query written in two ways:

π (ID) σ (GPA > 3.7 ∧ CName = 'Stanford') (Student x Apply)

```
SELECT Student.ID
FROM Student, Apply
WHERE Student.ID = Apply.ID
AND GPA > 3.7 AND CName = 'Stanford'
```

---

Operators:

* `UNION` - in many systems it automatically orders and eliminates duplicates. `UNION ALL` doesn't.
* `INTERSECT`
* `EXCEPT`
* 