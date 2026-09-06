## Microservices

Links:
* [Marco Behler](https://www.marcobehler.com/guides/java-microservices-a-practical-guide)
* [Understanding the Differences Between RabbitMQ vs Kafka](https://tanzu.vmware.com/developer/blog/understanding-the-differences-between-rabbitmq-vs-kafka/)
* [CQRS by Martin Fowler](https://martinfowler.com/bliki/CQRS.html)
* [Focusing on events by Martin Fowler](https://martinfowler.com/eaaDev/EventNarrative.html)

### Microservice communication

Asynchronous/synchronous

### HTTP/REST Resilience Patterns

Latency and fault tolerance - Netflix Hystrix
Messaging resilience patterns:
1. JMS implementations like ActiveMQ, trading speed for guarantees - two-phase (XA) commits.
2. RabbitMQ - acknowledgements, confirms, message reliability.
3. 