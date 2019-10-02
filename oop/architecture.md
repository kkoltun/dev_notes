# Software Architecture
## Why is it important?

Applications lacking a formal architecture are generally:
* tightly coupled;
* brittle;
* difficult to change;
* without a clear vision or direction.

Furthermore, architecture addresses the following questions:
* is the application scalable;
* what are its performance characteristics;
* how easily does it respond to change;
* what are the deployment characteristics;
* how responsive is it.

Without architecture, to determine architectural characteristics of the application one has to fully understand the inner-workings of every component and module in the system.

## Architectural Patterns

Architectural patterns help define the basic characteristics and behavior of an application. Each of the patterns has its characteristics, strengths and weaknesses. Knowing these features is vital in choosing one that meets your business needs and goals.

### Layered Architecture

Characteristics:
* most common architecture pattern;
* other called as n-tier architecture pattern;
* standard for most Java EE applications.

Description:
* components are organised into horizontal layers;
* each layer performs a specific role within the application (e.g., presentation logic, business logic);

Most layered applications have four layers:
* presentation - handling all user interface and browser communication;
* business - executing specific business rules associated with the request;
* persistence;
* database.

In some cases business and persistence are combined into a single business layer.

**Each layer in the architecture forms an abstraction around the wokr that needs to be done to satisfy a particular business request.** This way, each layer does not need to know anything about processing that is specific for another one.

For example business layers is responsible for:
* accessing data from the persistence layer;
* performing business logic against the data;
* passing data up the presentation layer.
On the contrary, thanks to the layering, the business layer doesn't need to be concerned about how to format customer data for display on a screen.

