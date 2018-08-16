# REST
## Hypermedia Services
### Hypermedia As the Engine of Application State
`Protocol = a set of conventions governing the treatment and especially the formatting of data in an electronic communications 
system.`
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
