# JDBC basics

## Introduction

JDBC - Java Database Connectivity - database-independent connectivity between Java and databases.

There are three layers going from abstraction to concrete implementations in JDBC:
* **JDBC API** - used by the application;
* **JDBC Driver manager** - used by JDBC API;
* **vendor-specific JDBC Drivers**.

## Common JDBC components

1. Driver Manager
  * Manages a list of database drivers;
  * Matches connection requests from application with proper database driver using communication sub protocol;
  * First found driver that matches the protocol is used.

2. Driver
  * Handles the communication with the database;
  * The Driver Manager provies useful abstraction of it.

3. Connection
  * The interface with all methods for contacting a database;
  * Provides communication context.

4. Statement
  * Objects created with this interface are used to submit the SQL statements;
  * Some interfaces accept parameters in addition to executing stored procedures.

5. ResultSet
  * Objects holding data retrieved from database after executing Statement queries;
  * In acts as an iterator to allow you to move through its data.

6. SQLException
  * Handles any error that occurs in a database application.

## Steps to create a JDBC application

1. Import required packages - usually `import java.sql.*`.
2. Register JDBC driver - initialize a driver so that you can open a communication channel with the database.
3. Open a connection - use the method `DriverManager.getConnection()` method to create a `Connection` object, which represents a connection with the database.
4. Execute a query - use an object of class `Statement` for building and submitting an SQL statement to the database.
5. Extract data from the result set - use an appropriate method `ResultSet.getXXX()` method to retrieve the data from the result set.
6. Clean up the environment - close all database connections.

## Registering JDBC driver

1. First approach (most common):
  * Use `Class.forName(JDBC_DRIVER)` method;
  * This dynamically loads driver's class file into memory and automatically registers it.
2. Second approach (non-JDK compliant JVM):
  * Create `Driver` object `Driver driver = new oracle.jdbc.driver.OracleDriver();`
  * Register the driver in the `DriverManager` with `DriverManager.registerDriver(driver);`
