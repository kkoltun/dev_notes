# Strategy Pattern

![strategy](./image/strategy.svg)

**Definition**: the strategy patterns defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

**Advantages**:
* new behavior can be added without modifying any of the existing ones and without touching any of the client classes;
* the client class delegates its behavior to the behavior class by having an object with right interface;
* no implementation details leak to the client class, it owns interface;
* the behavior (also called *algorithm*) can be changed dynamically;

Rules used mostly: *favor composition over inheritance* and *encapsulate what varies*.
