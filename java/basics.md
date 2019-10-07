# Java Basics

## Objects, variables

* All non-primitive objects must be explicitly allocated and these objects are allocated on the heap.
* Fields of classes and objects that do not have an explicit initializer and elements of arrays are automatically initialized with the default value for their type (false for boolean, 0 for all numerical types, null for all reference types).
* Local variables must be definitely assigned to before they are accessed, or it is a compile error.

## Abstract Class Compared to Interfaces

Similarities:
* cannot be instantiated;
* may contain a mix of methods declared with or without an implementation.

In abstract class:
* you can declare fields that are not static and final;
* you can define public, protected and private concrete methods.

In interface:
* all fields are automatically public, static and final;
* all methods that are declared or defined (as `default`) are public;
* `since Java 9` you can declare private default methods.

**You can extend only one class; you can implement many interfaces.**

When to use abstract class:
* sharing code between two **closely related classes**;
* declaring non-static and non-final fields;
* classes that extend the abstract class have many common methods or fields;
* classes that extend the abstract class require access modifiers other than public (eg. protected, private).

When to use interface:
* **unrelated classes** would implement the interface (eg. `Comparable` and `Cloneable`);
* specifying a behavior but not thinking about who implements it;
* enabling multple inheritance of type.

## Exceptions

### Three kinds of exceptions

#### Checked exception

* exceptional conditions that a well-written application should anticipate and recover from;
* these are subject to the Catch or Specify Requirement;
* these are all exceptions, except for those indicated by `Error`, `RuntimeException` and their subclasses;
* logging an error message without stacktrace is advised.

#### Errors

* exceptional conditions that **external** to the application;
* application usually cannot anticipate or recover from them;
* usually result in printing the stack trace and exiting;
* subclasses of `Error` class;
* logging the stacktrace usually depends on the context.

#### Runtime Exception

* exceptional conditions that are **internal** to the application;
* application cannot anticipate or recover from them;
* usually result of programming bugs - logic errors or improper use of an API;
* not catching these exceptions is usually helpful as it increases the chance the exception will be detected in the early stage of development;
* logging all the details - message and whole stacktrace is advised.

### Catching base and derived classes as expceptions

If both base and derived classes are caught as exceptions, then catch block of derived class must appear before the base class.
Unlike C++, in Java, catching a base class exception before derived is not allowed by the compiler itself.

## Final

### Final class

A final class cannot be subclassed. Many classes in Java are final - `java.lang.System`, `java.lang.String`. This has security and efficiency benefits.

### Final methods

A final method cannot be overriden or hidden by subclasses.
This is usually used to prevent unexpected behavior from a subclass altering a method that may be crucial to the function or consistency of the class.

### Final variables

A final variable can only be initialized once, either via an initializer or an assignment statement. 

If a variable is a reference:
* the variable cannot be re-bound to reference another object;
* the object it references is **still mutable**, if it was originally mutable.

Inside a class:
* a final variable has to be definitely assigned in every constructor of the class in which it is declared;
* a static final variable has to be definitely assigned in a static initializer of the class in which it is declared.

## Static

### Runtime polymorphism

Like in C++, when method is static, runtime polymorphism **does not happen**.
This means this code:
```java
class Base {
    public static void show() {
       System.out.println("Base::show() called");
    }
}
  
class Derived extends Base {
    public static void show() {
       System.out.println("Derived::show() called");
    }
}
  
class Main {
    public static void main(String[] args) {
        Base b = new Derived();
        b.show();
    }
}
```
results in printing `Base::show() called`.

### Static with null

Calling static methods on objects that are `null` **does not** cause `NullPointerException`. This code compiles and runs well:
```java
public class Test {
    public static void main(String args[]) {
        Test obj = null;
        obj.staticMethod();
    }

    public static void staticMethod() {
        System.out.println("Hello world!");
    }
}
```

## equals() and hashCode() methods

Every `java.lang.Object` has two important methods defined:
* `public boolean equals(Object obj)`;
* `public int hashCode(Object obj`).

### equals() method

Java method `equals()` is used to compare equality of two Objects. There are two ways of comparison:
* **Shallow comparison** - this is the default implementation of `java.lang.Object.equals()`. Is simply checks if two Object references refer to the same object (using `==` operator);
* **Deep comparison** - this can be provided as own implementation. The comparison can be done w.r.t. state of the Objects.

Any implementation of `equals()` method has to be:
* **Reflexive** - for any reference value `a`, `a.equals(a)` should return `true`.
* **Symmetric** - for any reference values `a` and `b`, if `a.equals(b)` returns `true`, then `b.equals(a)` should return `true`.
* **Transitive** - for any reference values `a`, `b` and `c`, if `a.equals(b)` and `b.equals(c)` then `a.equals(c)` should return `true`.
* **Consistent** - for any reference values `a` and `b`, multiple invocations of `a.equals(b)` consistently return `true` or consistently return `false`, provided no informatio nused in comparison on the object is modified.

Furthermore, for any non-null reference `a`, `a.equals(null)` should return false.

### hashCode() method

Java method `hashCode()` returns hashcode value as an Integer. **This method must be overriden in every class which overrides equals() method.**

The general contract of `hashCode()` is:
* it must be consistent, although it is not necessary that it returns the same numbers from one execution of the application to another;
* if two objects are equal, according to `equals()` method, then `hashCode()` method must produce the same `Integer` on each of the two objects;
* if two objects are unequal, according to `equals()` method, is is not neccessary `hashCode()` will produce two distincts numbers. However. producing distinct values on each of the two objects is better for improving performance of hashing based collections.

## Weak, soft and phantom references

**Strong reference**:
* For example: `StringBuffer buffer = new StringBuffer();`.
* If an object is reachable via a chain of strong references (**strongly reachable**), it is not eligible for garbage collection.
* A cyclic reference is a case in which an object with strong reference will be garbage collected. 
* **When strong reference is too strong:** for example in the caching mechanism - having only strong references, we would decide what to remove from cache on our own, to enable GC mechanism.

**`ReferenceQueue`**:
* When passed into reference's constructor, the reference will be automatically inserted into the reference queue when the object to which it pointed became garbage.

**`WeakReference`**:
* Reference which isn't strong enough to force object to remain in memory.
* For example: `WeakReference<Widget> weakWidget = new WeakReference<Widget>(widget);`.
* When `WeakReference#get()` starts returning `null`, it means that the object it pointed to has become garbage.

**`SoftReference`**:
* This reference may stick around after the object became **weakly reachable** and before it is collected.
* **Object recurrection**: calling `get()` on an object that is **weakly reachable** but before the garbage collector collects it.
* The object will surely be collected before 

**`Phantom reference`**:
* `PhantomReference#get()` always returns `null` - it can never be resurrected.
* The point of this reference is to know when an object has been collected, by inspecting the `ReferenceQueue` used when creating the reference.
