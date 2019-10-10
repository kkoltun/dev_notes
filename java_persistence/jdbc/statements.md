# Statement types

## Statement

Features:
* General-purpose access to the database;
* Useful when using static SQL statements;
* It does not accept parameters.

Example:
```java
Statement statement = connection.createStatement(); // try block omitted

String updateSql = "UPDATE employees SET age=30 WHERE id=103";

Boolean return = statement.execute(updateSql); // this one returns only whether the result is ResultSet or other
int rowsAffected = statement.executeUpdate(updateSql); // this one returns number of affected rows

String selectSql = "SELECT employees WHERE id=103";

ResultSet resultSet = statement.executeQuery(selectSql);
```

## PreparedStatement

Features:
* Useful when utilizing SQL many times;
* Accepts parameters (numbered from 1).

Example:
```java
String updateSql = "UPDATE employees SET age=? WHERE id=?";

PreparedStatement preparedStatement = connection.prepareStatement(updateSql); // try block omitted

preparedStatement.setInt(1, 35);  // sets age
preparedStatement.setInt(2, 103); // sets id

Boolean return = preparedStatement.execute();
int rowsAffected = preparedStatement.executeUpdate();

preparedStatement.close();

String selectSql = "SELECT employees WHERE first_name=? AND department_id=?";
preparedStatement = connection.prepareStatement(selectSql);

preparedStatement.setString(1, "Alex"); // sets first name
preparedStatement.setInt(2, 100); // sets departament id

ResultSet resultSet = preparedStatement.executeQuery(selectSql);
```

## CallableStatement

Features:
* Used when accessing database stored procedures;
* Accepts parameters.
