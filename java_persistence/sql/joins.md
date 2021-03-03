# SQL JOIN types

![Join types](./images/joins.png)

[*Why wenn diagrams are wrong when explaining JOINS. :)*](https://blog.jooq.org/2016/07/05/say-no-to-venn-diagrams-when-explaining-joins/)

### Tables used in examples

**table_A:**

| A | M |
|---|---|
| 1 | m |
| 2 | n |
| 4 | o |

**table_B:**

| A | N |
|---|---|
| 2 | p |
| 3 | q |
| 5 | r |

## 1. INNER JOIN

**Selects all rows from both participating tables as long as there is a match.**

`SELECT * FROM table_A INNER JOIN table_B ON table_a.A=table_B.A;`

| A | M | A | N |
|---|---|---|---|
| 2 | n | 2 | p |

## 2. LEFT JOIN or LEFT OUTER JOIN

**Selects all rows from the first table and rows from the second table as long as there is a match.**

`SELECT * FROM table_A LEFT JOIN table_B ON table_a.A=table_B.A;`

| A | M | A | N |
|---|---|---|---|
| 2 | n | 2 | p |
| 1 | m | null | null |
| 4 | o | null | null |

## 3. RIGHT JOIN or RIGHT OUTER JOIN

**Selects all rows from the second table and rows from the first table as long as there is a match.**

`SELECT * FROM table_A LEFT JOIN table_B ON table_a.A=table_B.A;`

| A | M | A | N |
|---|---|---|---|
| 2 | n | 2 | p |
| null | null | 3 | p |
| null | null | 5 | q |

## 4. FULL OUTER JOIN

**Combines results of the both left and right outer joins.**

`SELECT * FROM table_A FULL OUTER JOIN table_B ON table_a.A=table_B.A;`

| A | M | A | N |
|---|---|---|---|
| 2 | n | 2 | p |
| 1 | m | null | null |
| 4 | o | null | null |
| null | null | 3 | p |
| null | null | 5 | q |

## 5. NATURAL JOIN

**Selects all rows from both participating tables as long as there are matches in ALL same named and typed columns. The common columns appear only once in the results.**

`SELECT * FROM table_A NATURAL JOIN table_B ON table_a.A=table_B.A;`

| A | M | N |
|---|---|---|
| 2 | n | p |

**Command producing the same results:**

```sql
SELECT table_A.A, table_A.M, table_B.N
FROM table_A, table_B
WHERE table_A.A=table_B.A;
```

### NATURAL JOIN example

**Table `employees`:**

| Column Name | # | Data Type|
|---|---|---|
| employee_id | 1 | int(11) unsigned |
| first_name | 2 | varchar(20) |
| last_name | 3 | varchar(20) |
| manager_id | 4 | int(11) unsigned |
| department_id | 5 | int(11) unsigned |

**Table `departments`:**

| Column Name | # | Data Type|
|---|---|---|
| department_id | 1 | int(11) unsigned |
| department_name | 2 | varchar(30) |
| manager_id | 3 | int(11) unsigned |

**Command:**

```sql
SELECT * FROM employees e
  NATURAL JOIN departments d;
```

**Results:**

1. Joining employees and departments on both `department_id` and `manager_id`.
2. Common columns appear only once.

**Command producing the same results:**

```sql
SELECT e.first_name, e.last_name, e.department_id, e.manager_id, d.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id AND e.manager_id = d.manager_id;
```

## 6. CROSS JOIN

* **Produces a result set which is the number of rows in the first table multiplied by the number of rows in the second table.**
* **The result is a Cartesian product of two tables.**
* **If `WHERE` clause is used with `CROSS JOIN`, it functions like an `INNER JOIN`.**

`SELECT * FROM table_A CROSS JOIN table_B;`

| A | M | A | N |
|---|---|---|---|
| 1 | m | 2 | p |
| 2 | n | 2 | p |
| 4 | o | 2 | p |
| 1 | m | 3 | q |
| 2 | n | 3 | q |
| 4 | o | 3 | q |
| 1 | m | 5 | r |
| 2 | n | 5 | r |
| 4 | o | 5 | r |

**Command producing the same results:**

`SELECT * FROM table_A, table_B;`

## 7. SELF JOIN

* **A table is joined with itself.**
* **It is useful when the table has a `FOREIGN KEY` which references its own `PRIMARY KEY` (eg. `employees` has `manager_id` which references `employee_id`)**

`SELECT * FROM table_A X, table_A Y WHERE X.A=Y.A;`

| A | M | A | M |
|---|---|---|---|
| 1 | m | 1 | m |
| 2 | n | 2 | n |
| 4 | o | 4 | o |

### SELF JOIN example

**Table `employees`:**

| Column Name | # | Data Type|
|---|---|---|
| employee_id | 1 | int(11) unsigned |
| first_name | 2 | varchar(20) |
| last_name | 3 | varchar(20) |
| manager_id | 4 | int(11) unsigned |

**Command:**

```sql
SELECT e.first_name, e.last_name, e.manager_id, m.first_name, m.last_name, m.employee_id
FROM employees e, employees m
WHERE e.manager_id=m.employee_id
```

**Results:**

1. List of employees with respective managers.
2. Employees with `manager_id=NULL` are not listed.
