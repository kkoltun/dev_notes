## System Design

### Steps

#### 1. Clarification of requirements

1. Backend only or frontend too?
2. Planned features, extensions of features.
3. Already made decisions vs the decisions to make in the future.

#### 2. Initial scale estimation

1. What scale is expected - number of simultaneous users, number of messages per second etc?
2. How much storage is needed?
3. What network bandwidth usage users are expecting?
4. Stable usage vs spikes.

#### 3. Planning of the interfaces

APIs establish the exact contract expected from the system. This way you can ensure you did not get the requirements wrong. 

1. Ways of communicating: REST API, SOAP, RPC, UI.
2. Security of the API:
   1. Securing user-facing communication.
   2. Securing inter-server communication.

#### 4. Data model definition

1. Define various system entities, how they interact with each other.
2. Choose the database type(s):
   1. Relational
   2. Document (noSQL)
   3. Graph
3. Choose the data types, eg. to store binary data like photos or videos.
4. Decide on the data management - storage, transportation, encryption.

#### 5. High-level design

1. Identify components - load balancer, server, database, file storage etc.
2. Identify the flow - from the client to the end of the system.

#### 6. Detailed design

Remember, that there is no single answer, there are different approaches with pros and cons.

Example questions:
1. We will be storing a massive amount of data. Should we partition our data to distribute it to multiple databases? What issues could we have?
2. We will be storing a lot of binary documents, probably "forever". The older documents (more than 3 months old) will be really infrequently accessed. What can you propose?
3. How much and at which layer should we introduce cache to speed things up?
4. What components need better load balancing?

#### 7. Identify bottlenecks

1. Identify the single points of failure and propose a way to mitigate the risk.
2. Imagine a scenario where a couple of servers are lost. How to avoid loosing user data/access to the service?
3. How should the performance monitoring be handled? What metrics should be used?
4. What if the performance degrades?