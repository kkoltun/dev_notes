# REST
## Hypermedia Services
### Hypermedia As the Engine of Application State
`Protocol = a set of conventions governing the treatment and especially the formatting of data in an electronic communications system.`

`Application = computerized behavior that achieves a goal.`

`Protocol = set of legal interactions necessary to realize that behavior. Protocol lays out the interaction rules.`
`Application state = is a snapshot of the entire system at a particular instant.`

* We browse the Web by clicking links or completing and submitting fields. These interlinked pages describe a protocol - a
series of steps we take to achieve a goal.
* The essence of hypermedia - by transiting links between resources, we change the state of an application.
* Hypermedia = everyday part of our online activities; rarely used in computer-to-computer interactions.
* Hypermedia system = characterized by transfer of links in the resource representations exchanged by the participants in the
application protocol.

### Application and resource state

consumer|service
---|---
initial request | resource state representation with links
choose links and make steps | application state changes, links reflect that

Application state changes as a result of:
* the service;
* the customer;
* the exchange of hypermedia-enabled resource representations;
* advertisement and selection of links.

Application state is:
* reflected by links transferred in resource representations;
* transitionable by links advertising legitimate state changes;
* inferred by the consumer based on the state of all resources with which the consumer is currently interacting.

Resource state is a combination of:
* values of information items belonging to the resource;
* links to related resources;
* links that represent a transition to a possible future state of the current resource;
* the results of evaluation any busienss rules that relate the resource to other local resources.

Resource state is partly dependent on the state of other local resources. Importantly, the rules that control the state of a resource are internal to the service that governs the resource. They do not leak into the external representation.

### Domain application protocol
`Domain application protocols specify the legal interactions between a consumer and a set of resources involved in a business process. DAPs sit atop HTTP and narrow HTTP's broad application protocol to support specific business goals.`

Service enforces a protocol - DAP - by advertising legitimate interactions with relevant resources.
Application overall state changes when a consumer follows links embedded in resource representations.
The application state changes that result from a consumer driving a hypermedia system resemble the execution of a business process.
Having a DAP enables user to understand only the semantic or business context in which a link appears. This reduces an application's dependency on static metadata such as URI templates or Web Application Description Language (WADL).

## REST beyond CRUD
[crud is bad for REST](http://www.drdobbs.com/architecture-and-design/crud-is-bad-for-rest/228700407)


## Case studies
### GitHub API starring gists
[description](https://developer.github.com/v3/gists/#star-a-gist)
### SunCloudAPI machine reset button
[description](http://www.tbray.org/ongoing/When/200x/2009/03/20/Rest-Casuistry)
[Fielding comment](https://roy.gbiv.com/untangled/2009/it-is-okay-to-use-post)
### 

## Fielding's dissertation
### Insights on sofware architecture
#### Software architecure vs structure
`At the heart of software architecture is the principle of abstraction: hiding some of the
details of a system through encapsulation in order to better identify and sustain its
properties.`

`Software architecture is defined by a configuration of architectural elements—components, connectors, and data—constrained in their relationships in order to achieve a desired set of architectural properties.`

`Sofware architecture = an abstraction of the run-time behavior of a software system`

`Software structure = a property of the static software source code`

Both modular structure of the source code and having independet software components implemented using parts of the same code have advantages. To focus on the software's run-time characteristics independent of a given component's implementation, the view of the software architecture is spearated from that of the source code.
#### Elements
##### Component
`A component is an abstract unit of software instructions and internal state that provides a transformation of data via its interface.`

A component is defined by its interface and the services it provides to other components, not by its implementation behind the interface. In other words, it is definned by the set of assumptions that other architectural elements can make about the component.
##### Connector
`A connector is an abstract mechanism that mediates communication, coordination, or cooperation among components.`

Connectors enable communication between components by transferring data elements from one interface to another without changing the data. Internally, a connector could consist of a subsystem of components transforming data for transport and  reversing the transformation for delivery. However, the external behavioral abstraction captured by the architecture ignores these details.
##### Data
`A datum is an element of information that is transferred from a component, or received by a component, via a connector.`

It is worth noting that nature of data elements within a network-based application architecture will often determine whether or not a given architectural style is appropriate (eg. mobile code design paradigms). 
#### Configuration
`A configuration is the structure of architectural relationships among components, connectors, and data during a period of system run-time.`

Configuration may be considered as being equivalent to a set of specific constraints on component interaction.
#### Properties
The set of architectural properties of a software architecture aggregates all properties that derive from the selection and arrangement of components, connectors and data within the system.

Properties can be
* functional - those achieved by the system;
* non-functional - for example relative ease of evolution, resuability of components, efficiency, dynamic extensibility.

Properties are induced by the set of constraints within an architecture. Constraints are often motivated by the application of a software engineering principle.
#### Architectural style
`An architectural style is a coordinated set of architectural constraints that restricts the roles/features of architectural elements and the allowed relationships among those elements within any architecture that conforms to that style.`
Styles are a mechanism for categorizing architectures and for defining their common characteristics. 

### Network-based Application Architectures
#### Network-based vs. Distributed
`The primary distinction between network-based architectures and software architectures in general is that communication between components is restricted to message passing, or the equivalent of message passing if a more efficient mechanism can be selected at run-time based on the location of components.`

Distributed system is one that looks to its users like an ordinary centralized system, but runs on multiple, independent CPUs. Network-based system is one that is capable of operation across a network, but not neccessarily in a fashion that is transparent to the user.

#### Architectural properties of key interest
##### Performance
One of the main reasons to focus on styles for network-based applications is because component interactions can be the dominant factor in determining user-perceived performace and network efficiency. Since the architectural style influences the nature of those interactions, selection of an appropriate architectural style can make the difference between success and failuer in the deployment of a network-based application.

Application's overall performance consists of various factors:
* network performance;
* user-perceived performance;
* network efficiency.

As for the network efficiency, it is worth noting that the best application performance is obtained by not using the network. This means that the most efficient architectural styles for network-based application are those that can efficiently minimize use of the network through:
* caching (reuse of prior interactions);
* reducing the frequency of network interactions in relation to user actions (replicated data and disconnected operation);
* removing the need for some interactions by moving the processing of data closer to the source of the data (mobile code).

##### Scalability
Scalability refers to the ability of the architecture to support large numbers of components,
or interactions among components, within an active configuration. Several actions can be taken to improve application's scalability:
* simplifying components;
* distributing services across many components (decentralizing the interactions);
* controlling interactions and configurations as a result of monitoring.

##### Simplicity
Generally, architectural styles induce simplicity by applying the principle of separation of concerns to the allocation of functionality within components.

##### Modifiability
Modifiability can be broken down into:
* evolvability;
* extensibility;
* customizability;
* configurability;
* reusability.

##### Visibility
In the case of network-distributed application, visibility refers to the ability of a component to monitor or mediate the interaction between two other components.

##### Portability

##### Reliability

#### Representational State Transfer (REST)
##### Deriving REST
###### Client-Server
Client-server architectural style's main principle is separation of concerns. By separating the user interface concerns from the data storage concerns, we improve the portability of the user interface across multiple platforms and improve scalability.

Possibly most significant to the Web, is thtat the separation allows the components to evolve independently.

###### Stateless
Communication must be stateless in nature, as in the client-stateless-server (CSS) style. Each request from client to server must contain all of the information neccessary to understand the request, and cannot take advantage of an stored context on the server. **Session state is therefore kept entirely on the client**

This induces:
* visibility - monitoring system does not have to look beyond a single request datum in orded to determine the full nature of the request;
* reliability - it eases the task of recovering from partial failures;
* scalability - not having to store state between requests allows the server component to quickly free resources. It also simplifies implementation because the server doesn't have to manage resource usage across requests.
This choice reflects a design trade-off, it has the following drawbacks:
* it can decrease network performance by increasing the repetitive data sent in a series of requests, since the data cannot be left on the server in a shared context;
* keeping the application state on the client-side reduces the server's control over consistent application behavior - the application becomes dependent on the correct implementation of semantics across multiple client versions.

###### Cache
Cache constraints are added to form client-cache-stateless-server style. This is done to improve network efficiency. The data within a response to a request has to be implicitly or explicitly labeled as cacheable or non-cacheable. The data marked as cacheable enables the client to reuse it for later, equivalent requests.

Adding cache constraints reduces or completely eliminates some interactions, improving efficiency, scalability and user perceived performance. The trade-off is obvious - it can decrease reliability if stale data within the cache differs significantly from the data that would have been obtained had the request been sent directly to the server.

##### REST Architectural Elements
`The Representational State Trasfer (REST) style is an abstraction of the architectural elements within a distributed hypermedia system.`
What does not matter:
* component implementation;
* protocol syntax.
What matters:
* roles of the components;
* constraints upon their interaction with other components;
* components interpretation of significant data elements.

##### Data Elements
A key aspect of REST is the nature and state of an architecture's data elements. There are three options in terms of distributed hypermedia system:
* render the data where it is locate and send a fixed-format image to the recipient;
* encapsulate the data with a rendering engine and send bot to the recipient;
* send the raw data to recipient with metadata that describes the data type.
Each of the options has advantages and disadvantages. **REST provides a hybrid of all three options by focusing on a shared understanding of data types with metadata, but limiting the scope of what is revealed to a standardized interface.** 

Overall rules:
* rest components communicate by transferring a representation of a resource in a format matching one of an evolving set of standard data types, selected dynamically based on the capabilities or desires of the recitpient and the nature of the resource;
* whether the representation is in the same format as the raw source, or is derived from the source, remains hidden behind the interface;
* the benefits of the mobile object style are approximated by sending a representation that consists of instructions in the standard data format of an encapsulated rendering engine (*downloadable feature-engines*).

###### Resources and Resource Identifiers
`Resource is any information that can be named. In other words, it can be any concept that might be the target of an author's hypertext reference.`
Resource `R` is a temporally varying membersip function `Mr(t)` which for time `t` maps to a set of entities, or valuse which are equivalent. The values in the set may be resource *resource representations* and/or *resource identifiers&.

### Books
* C. Ghezzi, M. Jazayeri, and D. Mandrioli. Fundamentals of Software Engineering. Prentice-Hall, 1991.
* C. Alexander. The Timeless Way of Building. Oxford University Press, New York, 1979.
* G. Booch. Object-oriented development. IEEE Transactions on Software Engineering, 12(2), Feb. 1986, pp. 211–221.
* Shaw. Toward higher-level abstractions for software systems. Data & Knowledge Engineering, 5, 1990, pp. 119–128.
* L. Bass, P. Clements, and R. Kazman. Software Architecture in Practice. Addison Wesley, Reading, Mass., 1998.

## Statefull vs stateless
### Statefull and stateless protocols

### Stateless vs caching
[Ion Crowcraft](https://www.cl.cam.ac.uk/~jac22/books/www/book/node39.html)

## Errors in REST

If resource has not been found:
* 400 if there is no mapping to it;
* 404 if there is mapping but it has not been found.

Furthermore:
* according to OWASP API should not reveal any information about the implementation or structure;
* A LOT OF business exceptions should not be really exceptions;
* mapping with FE should be simple;
* information passed to FE should be minimal.

## RPC vs Messaging
### Remote Procedure Calls
#### Definition
A generalization of a regular procedure invocation to a case where caller and receiver do not reside in the same process - and are potentially distributed across separate machines.
#### Goal
The goal is to make remote invocation as similar as possible to regular procedure calls and to hide details of the physical connection.
#### Advantages
The goal potentially allows to turn the distribution of the final system into a deployment-time decision. In other words, it may not matter for the programmet whether the call is local or remote as it syntactically looks the same.
#### Disadvantages
The disadvantages mainly come from the fact that the syntax of regular calls leaves no place for the information that might be usefully used if the system is actually distributed. There are two main security and integrity issues:
* many programming languages provide no security-related tools for managing procedure calls; every call is assumed to be safe;
* in the statically-typed languages, the compiler ensures that the signature and the protocol of the call matches on both sides.
Here, neither of the statements is guaranteed.
### Messaging
#### Definition
Messaging as a communication concept does not attempt to hide the physical aspects of communication. It is still hiding the implementation details, but not to the point of dismissing the notions related to run-time costs of exchanging data.
#### Advantages
* Messaging system can have timeouts that are controlled with arbitrary granularity;
* The progress of physical data transfer can be monitored;
* Messages can have priorities;
* Tagging, meta-information and tracing is possible;
* Security issues can be addressed with the use of digital signatures of data content and access tokens.
### More to read
* https://www.safaribooksonline.com/library/view/java-message-service/0596000685/ch01s04.html
* https://stackoverflow.com/questions/9062475/what-is-the-difference-between-document-style-and-rpc-style-communication
* https://martinfowler.com/articles/consumerDrivenContracts.html
