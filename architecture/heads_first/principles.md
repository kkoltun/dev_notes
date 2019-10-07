# Design patterns principles form Heads First Book

**Identify aspects of your application that vary and separate them from what stays the same.**

This means:
* taking what varies and "encapsulating" it so it won't affect the rest of the code.

Patterns:
* strategy.

**Program to an interface, not an implementation.**

**Favor composition over inheritance.**

This means:
* a lot more flexibility;
* dynamic change of objects at runtime.

Patterns:
* strategy.

**Strive for loosely coupled designs between objects that interact.**

This means:
* obtaining flexible OO systems, that can handle change because they minimize the interdepencency between objects.

Patterns:
* observer.

**Classes should be open for extension, but closed for modification.**

This means:
* the goal is to allow classes to be easily extended to incorporate new behavior without modifying existing code;
* this usually leads to new levels of abstraction.

Patterns:
* observer;
* decorator.
