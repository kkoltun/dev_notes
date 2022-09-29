# Clean Code Rules

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
A design strategy which:
* allows to reduce the inter-dependencies between components of a system;
* reduces the risk of changes in one component that will require changes in other ones;
* improves thinking about the problem in a generic manner;
* improves maintainability.

Tight coupling:
* makes introducing changes harder;
* impair testability;
* increases the probability of "spaghetti code".

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
* do not mix levels of abstraction in a function;

## Miscellaneous Rules
1. Prefer immutable objects:
  * less error prone;
  * more secure;
  * inherently thread safe.
2. Avoid side effects:
  * do not lie about what the function does - eg. [Java Thread.interrupted()](https://docs.oracle.com/javase/7/docs/api/java/lang/Thread.html#interrupted());
  * this is making method unreliable and hard to debug.
3. Prefer stateless objects:
  * easier to make the solution thread-safe;
  * easier to debug.

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
