# Java - exception types

```
               Throwable
               (checked)
                   │
         ┌─────────┴─────────┐
         │                   │
     Exception             Error
     (checked)          (unchecked)
         │                   │
         │             OutOfMemoryError
         │             StackOverflowError
         │
   ┌─────┴──────────────┐
   │                    │
IOException      RuntimeException
(checked)           (unchecked)
                        │
                 NullPointerException
                 IllegalArgumentException
```

## Three kinds of exceptions

### Checked exception

* Exceptional conditions that a well-written application should anticipate and recover from.
* These are subject to the Catch or Specify Requirement.
* These are all exceptions, except for those indicated by `Error`, `RuntimeException` and their subclasses.
* Logging an error message without stacktrace is advised.

### Errors

* Unchecked.
* Exceptional conditions that **external** to the application. Exceptions:
    * StackOverflowError usually comes from a bug (infinite recursion).
    * OutOfMemoryError can come from a memory leak.
    * ExceptionInInitializerError and AssertionError also come from your own code.
* Application usually cannot anticipate or recover from them.
* Usually result in printing the stack trace and exiting.
* Subclasses of the `Error` class.
* Logging the stacktrace usually depends on the context.

### Runtime Exception

* Unchecked.
* Exceptional conditions that are **internal** to the application.
* Application usually cannot anticipate or recover from them. Exceptions:
    * NumberFormatException when parsing user input.
    * OptimisticLockException, which you handle by retrying.
    * Spring's DataAccessException hierarchy.
* Usually result of programming bugs - logic errors or improper use of an API.
* Not catching these exceptions is usually helpful as it increases the chance the exception will be detected in the
  early stage of development.
* Logging all the details - message and whole stacktrace is advised.

## Catching base and derived classes as exceptions

If both base and derived classes are caught as exceptions, then catch block of derived class must appear before the base
class.
Unlike C++, in Java, catching a base class exception before derived is not allowed by the compiler itself.

## `finally`

The `finally` block can be used with alone `try` or `try` with `catch`, this is the code that is ** almost always
ran** - regardless of whether the block excution finished successfully or threw an exception. Exceptions:

* Finally does **not** run after `System.exit()` or a JVM crash or if the thread never leaves the `try`.

Returning from `finally`:

```java
int f() {
    try {
        return 1;
    } finally {
        return 2;
    }
}
```

this returns 2 and swallows the exception.

```java
int g() {
    x = 1;
    try {
        return x;
    } finally {
        x = 2;
    }
}
```

this returns 1, it has already been evaluated.

## try-with-resources

* Works with `autocloseable`.
* The resources are closed in reverse order, before `catch`/`finally` blocks run.
* If `close()` also throws, that exception is attached to the original as a **suppressed** exception instead of hiding
  it.

## Various facts

* Spring `@Transactional` does a rollback only for unchecked exceptions by default. You can change it e.g. using
  `rollbackFor = Exception.class`.
* Exceptions in `ExecutorService.submit()` disappear. They are sorted in the `Future` and only surface when you call
  `get()`, wrapped in `ExecutionException`.