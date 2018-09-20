# Java Basics

## Abstract Class Compared to Interfaces
Similarities:
* they cannot be instantiated;
* they may contain a mix of methods declared with or without an implementation.

In abstract class:
* you can declare fields that are not static and final;
* you can define public, protected and private concrete methods.

In interface:
* all fields are automatically public, static and final;
* all methods that are declared or defined (as `default`) are public.

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

## 
