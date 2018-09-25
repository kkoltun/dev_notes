# Object-Oriented Design Module 2

## Objectives of OOP
* create computer representations of concepts in the problem space;

## CRC Cards
*  Component, Responisibilty, Collaborators;
* prototyping and simulating design;
* far from implementation, enables to focus on the problem;

## Design types
* conceptual design - Component, Responisibilty, Collaborators (CRC) cards method;
* technical design - Unified Modeling Language (UML) method.

## Types of objects
* entity;
* control;
* boundary.

## Qualities to be obtained
* flexibility;
* reusability;
* maintainability.

## Four Design Principles of OOP
* What are the OOP programs?
* How do you create OOP programs?

### Abstraction
> Abstraction is the idea of simplifying a **concept** in the problem domain to its essentials within some **context**. Abstraction allows you to better understand a concept by breaking down into a simplified description that ignores unimportant details.

#### Properties
* used when dealing with complexity;
* abstraction of a concept should make sense for the concept's purpose;
* Rule Of Least Astonishment - the abstraction captures the essential attributes and behavior for a concept with no surprieses and no definitions that fall beyonds its scope.

Abstraction describes:
* attributes;
* behaviors.

#### Abstraction with a class
* class - like a template for its instances. Each instance can have other properties;
* for creating a class using abstraction a **context** is needed;
* attributes and behaviors of a class will vary depending from a **context**.

### Encapsulation
> Encapsulation forms a self-contained object by bundling the data and functions it requires to work, exposes an interface whereby other objects can access and use it, and restricts access to certain inside details.

#### Steps of encapsulation
1. Bundling data and functions in a self-contained object.
1. Expose certain data and functions which can be accessed by other objects.
1. Restrict access.

#### Properties
* should `foo` be encapsulated in `Class A`? = Does `Class A` know about `foo`?
* the `Student` *knows* about their `grades`;
* encapsulation can secure sensitive information;
* encapsulation helps with software changes - the implementation remains hidden (*black box thinking*, *abstraction barrier*).

### Decomposition
> Decomposition is taking a **whole** thing and dividing it up into different **parts**. Or, on the flip side, taking a bunch of separate parts with different functionalities and combining them together to form a whole.

#### Properties
* all about dividing a component into subcomponents;
* fixed or dynamic number of parts (instances of subcomponents);
* part may contain other parts;
* the parts may have closely related or independent lifetimes (fridge and refrigerator vs fridge and food in it).

### Generalization
> generalization of behaviors achieved by methods used in different places;
> generatlization of classes achieved by inheritance;

#### Properties
* reduces redundancy;
* taking a general idea having common characteristics and behaviors of components;
* DRY - Don't Repeat Yourself.

## Abstraction in Java and UML - UML Class Diagram
### UML Class Diagram
* class name, properties and operations;
* directly mapped to code; as opposed to vague **CRC Cards which are far from the implementation, this enables to focus on the problem**.
* CRC resposibilities map Class Diagram to properties/operations

## Encapsulation in Java and UML
* restricting access to properties to getters and setters;
* hiding implementation details from other classes.

## Decomposition in Java and UML

### Methods of Decomposition

#### Association
* loose "some" relationship;
* there is a loose relationship between two objects;
* objects may interact with each other for some time;
* lifetimes of objects are independent;
* symbol - straight line with quantities on each side.

### Aggregation
* weak "has-a" relationship;
* weak relationship - the whole can exist without its parts and vice versa (`Crewmember` can exist without `Plane` aggregting it and vice versa);
* parts can be shared;
* symbol - line with empty diamond and quantities on each side.

### Composition
* striong "has-a" relationship;
* strong relationship - the whole cannot exist without its parts; if it looses its parts it ceases to exist; if whole is destroyed, parts are destroyed too;
* parts are exclusive to the whole;
* symbol - line with filled diamond and quantity on the other side.
