# Design patterns
## Overall rules
#### Encapsulate what varies
#### Favor composition over inheritance
#### Program to interfaces, not implementations
#### Strive for loosely coupled designs of objects that interact
#### Classes should be open for extension but closed for modification
## Patterns one by one
### Strategy
#### Goals:
* define a family of algorythms, encapsulate each one and makes the interchangeable;
* let the algorythm vary independently from clients that use it.
#### Properties:
* the varying and extendable behaviors are encapsulated - they are extending an interface;
* the duck HAS A behavior object, therefore it can be dynamically changed. It is loosely coupled;
* the duck HAS A behavior object, it does not matter what implements it
---
### Observer
#### Goals:
* define one-to-many dependency between Subject and Observers;
* when one Subject changes state, all of its dependents are notified and updated automatically;
* one Subject contains the state and controls it, observers use the state, but this is **pull** interaction;
#### Properties:
* when creating ConcreteObserver, Observer interface is implemented;
* views can depend on different thigs, but Subject is something independent;
* Subject has many Observer objects, but does not know anything about their implementation of the interface;
* Observers register with concrete subject to receive updates.
#### Misc:
* the Java Observer is a **class**, you have to subclass it!
---
### Decorator:
#### Goals:
* attach additional responsibilities to an object **dynamically**;
* provide flexible alternative to subclassing for extending functionality.
#### Properties:
* Decorator has the same supertype as Decorated, but this is only for type matching, not to get behavior;
* Component has what is common everywhere;
* Decorators encapsulate every new thing;
* the way of adding behavior is composing the decorator with component, this way it is acquired **by means of composition**, not **inheritance**.
#### Decorators in Java:
* InputStream is an **abstract component**;
* FileInputStream, ByteArrayInputStream, FilterInputStream are **abstract decorators**;
* BufferedInputStream, LineNumberInputStream are **concrete decorator** of FilterInputStream.
---
### Fluent interface
[Fowler](https://martinfowler.com/bliki/FluentInterface.html)
### Goals:
* make configuration, building an object easier;
### Properiets:
* the key test for fluency is the Domain Specific Language quality. The more the use of the API has that language like flow, the more fluent it is;
* setters that return values. (Violation of CommandQuerySeparation);
* one of the problems of methods in a fluent interface is that they don't make much sense on their own.

## Resources
* [Abstraction, encapsulation and information hiding](https://web.archive.org/web/20071214085409/http://www.itmweb.com/essay550.htm)
* [Heads first design patterns](http://shop.oreilly.com/product/9780596007126.do)
* [Object oriented sofware construction](https://en.wikipedia.org/wiki/Object-Oriented_Software_Construction)
