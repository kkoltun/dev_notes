# Java - exception types

## Three kinds of exceptions

### Checked exception

* Exceptional conditions that a well-written application should anticipate and recover from.
* These are subject to the Catch or Specify Requirement.
* These are all exceptions, except for those indicated by `Error`, `RuntimeException` and their subclasses.
* Logging an error message without stacktrace is advised.

### Errors

* Exceptional conditions that **external** to the application.
* Application usually cannot anticipate or recover from them.
* Usually result in printing the stack trace and exiting.
* Subclasses of the `Error` class.
* Logging the stacktrace usually depends on the context.

### Runtime Exception

* Exceptional conditions that are **internal** to the application.
* Application cannot anticipate or recover from them.
* Usually result of programming bugs - logic errors or improper use of an API.
* Not catching these exceptions is usually helpful as it increases the chance the exception will be detected in the early stage of development.
* Logging all the details - message and whole stacktrace is advised.

## Catching base and derived classes as exceptions

If both base and derived classes are caught as exceptions, then catch block of derived class must appear before the base class.
Unlike C++, in Java, catching a base class exception before derived is not allowed by the compiler itself.

