# Events and publishing

Notes from Jakub Nabrdalik's talk [*Simplify your architecture: events and publishing*](https://youtu.be/x7qOo8z2BEI) (Confitura 2025, in Polish).

## Decoupling

Coupling and decoupling are not good and bad. They are a trade-off. Things coupled together are easy to understand
together and to change together. Things decoupled are easy to change one at a time, but the whole becomes hard to
understand. The question is always which you need here: to understand and change a business process as one whole, or to
let two parts, often two teams, change without each other.

## Modules

A module is:

* Responsible for a signle process (so it stays small).
* Encapsulates code & data, everything is private including DB tables. None module in other module anyhow touches the
  tables in this module, call Java.
* Has an API and collaborators (public facade).
* Is a vertical slice (layers inside).

## Sending events

**Event** is a statement, usually in past simple form, you can use pretty much every protocol.

| How the event is sent                                                                 | Protocol                                               | Thread / machine                                    |
|---------------------------------------------------------------------------------------|--------------------------------------------------------|-----------------------------------------------------|
| Call the other module's facade in plain Java, passing the event                       | synchronous                                            | same thread                                         |
| An HTTP call (`RestClient`, `WebClient`) that answers 200 and does the work elsewhere | synchronous call, work done elsewhere                  | another machine                                     |
| Publish on an in-memory bus (Spring's `ApplicationEventPublisher`)                    | asynchronous: the sender knows nothing of what follows | **still the same thread**, unless `@Async` is added |
| The in-memory bus with `@Async` on the listener                                       | asynchronous                                           | another thread                                      |
| A persistent log: Kafka, Kinesis, Pulsar, Azure Event Hubs                            | asynchronous                                           | another machine, and the events survive             |

**Event driven can be done without any event bus.**

## In-memory event bus

When to use in-memory event bus, you need a **REASON** because it complicates things.

One of the reasons can be plugin architecture - when another dev you don't know will want to add/modify behavior. If you
are modifying the code within one team, there is no reason to use it.

Problems with **in-memory event bus** start when producer sends an event to a slow consumer, you need:

1. **Drop the events.** No business process allows this: "we took your money, but there was no thread for your
   transfer".
2. **Back-pressure:** tell the producer to slow down. Throttling is a lot of work.
3. **Buffer them in memory.** This is the default everyone uses. An unbounded buffer ends in `OutOfMemoryError`, which
   takes down the whole JVM. A bounded one only moves the question to "what happens when it is full?". A memory buffer
   survives a short spike, nothing more.
4. **Buffer them in a persistent log** (option 5 of the table), described below.

So why not use plugin architecture to connect OUR modules:

* It has its problems, e.g. a slow consumer and we don't want to own these problems.
* We don't get any benefits and over-complicate the code.

## Persistent log

This is a buffer that (for us) has possibly infinite capacity.

**A persistent log (Kafka and the like), in three cases.**

### 1. The work is really done later, and the buffer must not run out

* The log is a file the producer appends to, and the consumer *pulls* from it at its own pace, so back-pressure comes
  for free.
* Disks fill up too, but in weeks, not seconds, so there is time to see it on monitoring and add consumers.
* **This holds even inside one application.**

### 2. Partitioning, to get rid of database locks

You might have some processes that need pessimistic locking to prevent lost updates. When many threads can modify the
same resource (e.g. customer's account), then there can be problems.

A possible solution is: events keyed by user go to one partition, and one partition is handled by one thread, so all of
one user's transfers are processed one after another and nobody changes that user's balance in the meantime.

**However**, during a rebalance one consumer leaves and another joins, and for a moment two threads can process the
same event without Kafka knowing. The locking exceptions become rare, not impossible. Example:

* Consumer A is long processing event 42 and is considered dead (heartbeat stopped because of GC or `poll()` is
  not called within `max.poll.interval.ms` or even a network problem).
* Consumer B takes over the partition and starts from the last committed offset - gets the event 42 again.
* Consumer A is still running and finishes its write to the database when B is processing the event too.

Two problems here.

First is a possible **lost update** when A finally commits changes from re-processed event 42, for example:

1. Event 42 is WITHRAW (100).
2. A starts processing, but goes zombie.
3. B processes it, current balance = 900.
4. B processes next one which is ACCEPT (200), balance = 1100.
5. A commits long processed event 42 and saves the state as-of after withdrawal, balance = 900 again. **Lost update.**

Second is a double withdrawal - the fact that the event 42 can be processed twice. Consumer A might even get the right,
final balance before the withdrawal (1100) but still process it the second time, which **would not be a lost update**.

Possible solutions:

1. Lost update (classic fixes): pessimistic, optimistic locking with optional retries, repeatable read isolation in
   Postgres with optional retries, atomic updates.
2. Duplicated processing of an event - **only a deduplication row helps here**. Only one transaction for event 42 can
   commit. The other fails on the unique key or waits for the first one and then fails. Naturally, insertion of this key
   must be in the same transaction as the balance operation.

Summing up - **the deduplication rows helps in both problems**.

### Talking to another team's applications

* Calling them synchronously means you can flood them and they must throttle you. With a log, you agree on a
  contract once (what is sent, what it means) and then never need to meet: they consume when they can, and their
  production problems are theirs. This is the reason microservices exist.
* ThoughtWorks described them in 2012 as a way to remove synchronisation points between teams, because every such
  point turns into meetings.
* The Reactive Manifesto asks for message-driven communication for the same resilience, an intermediary between the
  parties.

## Event sourcing does not mean publishing the stored events

Event sourcing is a way to *store* data (as the list of events, such as each payment into and out of an account), so it
belongs to the persistence layer. Telling other modules what happened is communication, which belongs to no layer.

If the stored events are streamed to other modules or teams as they are (with Debezium, for example), the database
schema becomes the contract, which can be a problem of its own: refactoring the event store, already hard, now also
breaks another team. So **keep two separate types the stored event and the published event**, even if they start with
exactly the same fields. Using one object for both at first and splitting it later sounds simpler, but "you go on
holiday, the juniors change both at once".

## System design interview

The three reasons for Kafka above are a ready answer to "why a message broker here?" in a design round:

* Deferred work with a durable buffer.
* Ordering per key instead of locks.
* Decoupling of teams.

Inside one service owned by one team, a method call (or a job table) is the simpler answer.

## Choreography vs orchestration

Choreography:

1. Many steps, but nobody knows the entire process.
2. Two teams don't need to know about each other.
3. **When introduced inside one team you get only the cost**. Nobody can see the entire process.

Orchestration:

1. One class/place calls the steps in order.
2. Two teams working on the same part need to synchronize, cause conflicts etc.