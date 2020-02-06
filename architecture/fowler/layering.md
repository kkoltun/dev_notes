# Layering

## Overall information

**Layering is one of the most common techniques that software designers use to break apart a complicated software system.**

Opaque layers:
* Higher layer uses lower layer.
* Usually each layer hides its lower layers from the layers above.

Benefits:
* One can understand a single layer as a coherent whole without knowing much about the other layers.
* Layers can be substituted with alternative implementations of the same basic services.
* Dependencies between layers are minimized.
* Once a layers is built, there can be many higher-level services built on it.
* Layers can be standardized (`TCP` and `IP` are standards defininig how the layers should operate).

Downsides:
* Not all things can be encapsulated well. In a layered enterprise application, adding a new field to UI requires changes in the database and everywhere between.
* Extra layers can harm performance. Data is usually transformed from one representation to another from layer to layer.
* Deciding what layers to have and what the responsibilities each layer should have is hard.

## Three Principal Layers

### Overview

**Presentation**:
* Handles interaction between the user and the software.
* Displays information to the user.
* Handles user requests - mouse clicks, keyboard hits, HTTP requests, command-line invocations.
* Interprets requests into actions upon the domain.

**Data source**:
* Communicates with other systems taht carry out tasks on behalf of the application.
* Examples: transaction monitors, messaging systems, etc.
* Usually biggest piece of data source logic is a database.

**Domain logic**:
* Calculating based on inputs and stored data.
* Validation of any data that comes from the presentation.

There are two approaches:
1. (More pure, less often) Domain logic completely hides the data source from the presentation.
2. (Less pure, more often) Presentation layer accesses the data source directly and lets the domain logic manipulate it before presenting.

**Main rules:**
* Domain and data source should never depend on the presentation.
* Layers communicate from top to bottom. This way the layer is dependent only on the interface of the layer directly below it.

Checking what belongs to domain logic:
* Try to change presentation layer from a rich, Web UI to a command-line interface in a web application.
* Think of deciding what to highlight in an UI - decision should come from business logic.

### Where to run layers

**Data source**:
* This is usually a database run on an a server.
* A powerful client might duplicate the server functionality, then synchronization is an issue.

**Presentation layer**:
* Rich client - running layer on the client-side.
* Web interface - running on the server.
* Moving from server-side to client-side - harder maintenance, better responsiveness.

**Domain logic**:
* Usually run on server-side.
* If the logic is moved to client-side, it is wise to move all the logic (especially having a rich client).
