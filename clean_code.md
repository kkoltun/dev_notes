# Clean Code Rules
> Todo: move SOLID to another document
## SOLID

### Single Responsibility Principle
**The class or module should do one thing only.** 

#### Description
* *the class or module should have only one reason to change* by Robert Martin;
* usually `Manager`, `Utility`, `Context` classes are doing too much.

#### Rationale
* software is easier to implement, debug and test;
* any change does not add/remove responsibilites from class;
* classes are easier to understand and explain;
* prevents unexpected side-effects of future changes;
* classes are easier to name clearly.

#### Example
* MVC pattern;
* chain of responsibility pattern.

#### Further reading
* [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns).

### 0pen/Closed Principle
**The code entities should be open for extension, but closed for modification.** 

#### Description
The term originates from *Object Oriented Software Construction* by Bertrand Meyer.

A module is:
* **open** if it is still available for extension. For example it should be possible to add fields to  the data structres it contains. In object oriented programming, adding functionalities is mainly achieved by subclassing;
* **closed** if it is available for use by other modules. This assumes that the module has been given a well defined, stable description.

#### Rationale
* 

#### Example
* an **anti-example** could be `switch` statement that requires change every time you add an option to menu;
* strategy pattern.

#### Further reading
* [Craig Larman, *Protected Variation: The Importance of Being Closed*](http://codecourse.sourceforge.net/materials/The-Importance-of-Being-Closed.pdf);
* [Robert C. Martin, *The Open-Closed Principle, C++ Report*](https://drive.google.com/file/d/0BwhCYaYDn8EgN2M5MTkwM2EtNWFkZC00ZTI3LWFjZTUtNTFhZGZiYmUzODc1/view).

### Liskov Substitution Principle (Sustainability)
**Objects in a program should be replaceable with instances of their subtypes without altering the correctness of that program.**

#### Description
This is a definition of a subtyping relation called (strong) behavioral subtyping introduced by Barbara Liskov in a 1987 conference. It intends to guarantee **semantic interoperability of types in a hierarchy**.

##### Designing by contract
Each method should have *preconditions* and *postconditions* defined.
In the method execution:
* preconditions must hold true in order for it to execute;
* postconditions must hold true after the execution of a method;

When redefining a method (in a derivative):
* preconditions may be replaced by weaker ones;
* postconditions may be replaced by stronger ones.

#### Rationale

#### Anti-examples

##### Strengthening preconditions
1. Base method accepts an int.
2. Derived requires that in to be positive (strenghtened precondition).
3. Code that worked perfectly fine before with a negative ints now is broken.

##### Weakening preconditions
1. Base method guarantees that the member would be positive after being called.
2. Derived changes the behavior to allow negative ints.
3. Code that worked on the object assuming that the post-condition is upheld is broken now.

#### Further reading
* [Presentation by Liskov and Wing](http://reports-archive.adm.cs.cmu.edu/anon/1999/CMU-CS-99-156.ps])
* [Robert C. Martin](https://web.archive.org/web/20151128004108/http://www.objectmentor.com/resources/articles/lsp.pdf)

### Interface Segregation Principle
**Favor many, smaller, client-specific interfaces over one larger, more monolithic interface.**

#### Description
* *clients should not be forced to implement interfaces they do not use* by Robert Martin;
* favor composition over inheritance - separate roles (resposibilities);
* favor decoupling over coupling - do not couple derivative classes with unneeded responsibilities inside a monolith.

#### Rationale
Small iterfaces:
* are easier to utilize;
* are less prone to breaking.

#### Example
* at a larger scale - microservices.

#### Further reading

### Dependency Inversion
**Write code that depends upon abstractions rather upon concrete details.**
**Write to an interface, not implementation.**

#### Description
* *High level modules should not depend upon low level modules. Both should depend upon abstractions* by Robert C. Martin;
* *Abstractions should not depend upon details. Details should depend upon abstractions* by Robert C. Martin.

#### Rationale
* improved reusability and extension (write to an universal API);
* enables Dependency Inversion.

#### Example
* DI in Spring;
* switching database implementations.

#### Further reading
* Design Patterns book.

## Don't Repeat Yourself (DRY)
*Every piece of knowledge must have a single, unambiguous, authoritative representation within a system.*

### Caused by:
* `copy-paste programming`;
* poor understanding of how to apply abstraction.

### Consequences:
* amount of work required to extend and maintain is increased;
* repeating errors.

### Handling:
* duplication in logic should be eliminated via abstraction;
* duplication in process should be eliminated by automation;
* rule of three - if you have identical code in three or more places, it should be abstracted into common place to be reusable and maintainable;
* single source of truth (SSOT)/single point of truth (SPOT) - use relational schemas instead of duplication of data. Every data element is stored exactly once.

### `WET` code:
* waste everyone's time;
* write everything twice.

## Loose coupling
### Law of Demeter (principle of least knowledge)
LoD is a specific case of loose coupling.
It can be summarized in each of the following ways:
* each unit should have only limited knowledge about other units: only units "closely" related to the current unit;
* each unit should only talk to its friends; don't talk to strangers;
* only talk to your immediate friends.

### Further reading
* [The Paperboy, The Wallet and The Law Of Demeter](https://www2.ccs.neu.edu/research/demeter/demeter-method/LawOfDemeter/paper-boy/demeter.pdf)
* [Introducing Demeter and its Laws](http://www.bradapp.com/docs/demeter-intro.html)
* [Tell, Don't Ask](https://pragprog.com/articles/tell-dont-ask)
* [Object-Oriented Programming: An Objective Sense of Style](https://www2.ccs.neu.edu/research/demeter/papers/law-of-demeter/oopsla88-law-of-demeter.pdf)
* [Aspect-oriented Programming With Adaptive Methods](https://www.researchgate.net/publication/220422659/download)

## Single Level of Abstraction Principle(SLAP)
**TODO**

## Further reading
* [Google on writing testable code](http://misko.hevery.com/code-reviewers-guide/);
* [Principles of OOD by Uncle Bob](http://butunclebob.com/ArticleS.UncleBob.PrinciplesOfOod)
* [Refactoring by Fowler - especially *primitive obsession*](https://martinfowler.com/books/refactoring.html);
* [Agile Software Development, Principles, Patterns, and Practices](https://www.amazon.com/Software-Development-Principles-Patterns-Practices/dp/1292025948);
* [Working Effectively With Legacy Code by Feathers](https://www.amazon.com/FEATHERS-WORK-EFFECT-LEG-CODE/dp/0131177052);
* [Clean Code: A Handbook of Agile Software Craftsmanship](https://www.amazon.com/Clean-Code-Handbook-Software-Craftsmanship/dp/0132350882);
* [Object Oriented Software Construction](https://sophia.javeriana.edu.co/~cbustaca/docencia/POO-2016-01/documentos/Object%20Oriented%20Software%20Construction-Meyer.pdf)
* [The Pragmatic Programmer](https://en.wikipedia.org/wiki/The_Pragmatic_Programmer)
* [Code Complete]()
