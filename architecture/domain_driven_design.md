# Domain Driven Design

## Two types of complexity

* **Essential** - inherent to the problem.
* **Accidental** - dependent on the solution; this is a result of the activity.

DDD focuses on the essential complexity.

## The model

* The model is the reason why we are developing the project, it is the heart of the system.
* Modeling it is the biggest advantage in the project.
* The model gathers the knowledge of the system rules and the behavior of the system.
* The model is prepared for extension and adding details.
* **The model reflects the dynamics more than the static structure.**
* **There is only one model. It is common for analytics, programmers, designers etc.**
* **Therefore, the model can reside only in a layer that is technology-agnostic.**

Ubiquitous Language:

* The Domain Expert and the Development Team must understand it.
* The methods of expressing it can be local to the team (UML, Excel, Miro,...).

### The layers

Layers in DDD:

1. Presentation
2. Logic layer
    1. Application logic
    2. Business logic
3. Data access

Business logic layer:

* 100% focused on the model.
* Totally technology-agnostic.
* Testable.
* Uses Ubiquitous Language directly.

Application logic layer:

* Usually thin.
* Responsible for security, transaction-management.
* Orchestrates domain objects - **puts them into right order to fulfill use cases**.

### Building blocks

Building blocks come from Responsibility Driven Design by Rebecca Wirfs-Brock:

* Define Roles for objects.
* Each Role has a set of responsibilities.
* Each class plays a certain Role.

Building Blocks define a set of Roles that can be played by objects within the Model.

**Make explicit what is implicit**:

* The core concepts and complexity of the Domain Model have to be explicit.
* All core expressions from Ubiquitous Language should be in the Domain Model.

#### 1 | Entity

* These are ordinary Entities known from ORMs with added business logic.
* There should be only **business logic essential for this entity** inside, not more.

#### 2 | Aggregate

* Entity graphs.
* One entity is the Aggregate Root.
* Aggregate itself is a Unit Of Work:
  1. Load it from the Repository or create new using a Factory.
  2. Perform business operations.
  3. Persist in the Repository.
* Does not have getters/setters unless they have a business reason.
* 

### Loose notes

1. Oczywiście dobrą  praktyką jest stworzenie własnej adnotacji `@ApplicationService`, która będzie nieść ze sobą szereg standardowych adnotacji, ukrywając szczegóły poszczególnych adnotacji technicznych.
2. 
