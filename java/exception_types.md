# Java - exception types

## Three kinds of exceptions

### Checked exception

* exceptional conditions that a well-written application should anticipate and recover from;
* these are subject to the Catch or Specify Requirement;
* these are all exceptions, except for those indicated by `Error`, `RuntimeException` and their subclasses;
* logging an error message without stacktrace is advised.

### Errors

* exceptional conditions that **external** to the application;
* application usually cannot anticipate or recover from them;
* usually result in printing the stack trace and exiting;
* subclasses of `Error` class;
* logging the stacktrace usually depends on the context.

### Runtime Exception

* exceptional conditions that are **internal** to the application;
* application cannot anticipate or recover from them;
* usually result of programming bugs - logic errors or improper use of an API;
* not catching these exceptions is usually helpful as it increases the chance the exception will be detected in the early stage of development;
* logging all the details - message and whole stacktrace is advised.

## Catching base and derived classes as expceptions

If both base and derived classes are caught as exceptions, then catch block of derived class must appear before the base class.
Unlike C++, in Java, catching a base class exception before derived is not allowed by the compiler itself.

