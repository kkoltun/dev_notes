# Hexagonal architecture

Handwritten notes from Cockburn's *Hexagonal Architecture*, 2026-10-28, with Woodpecker (WP) as the example.

### WP as a hexagon (drawn as an octagon)

The ports, each with its adapters and the actors outside:

- **management**: REST API (other app, user), MCP (LLM), GUI (user, admin)
- **scheduling**: scheduler, triggered by a clock
- **prospects**: Pipedrive adapter, to Pipedrive
- **inbox**: inbox adapter, to the users' outbound inboxes
- **notifications**: mailbox (to the users' management inboxes), GUI (to the GUI user)
- **db**: Postgres (to the database), in-memory
- **outbound**: LinkedIn adapter (to LinkedIn), mailbox adapters (to the users' outbound mailboxes)
- This should have 10 edges for inbox to be on the right.

### In tests

- You drive the app via the left sides.
- You replace the right sides with mocks.
- It's not where the data flows, it is more who initiates the conversation.

### Ports and adapters

- Port: a purpose-defined conversation the app exposes (left) or needs (right). Not a technology.
- Adapter: translates between one specific technology and a port. Some adapters are stand-ins and have no external actor (a mock database).
- A single port could have several adapters.
- A hexagon might be an octagon etc.
- Hexagons are **not** deployment units. They can be modules inside one monolith with enforced boundaries.
- Not everything deserves to be a hexagon. A thin context with little logic can be just an adapter on the core.
- Rules need to be complex enough to protect and test in isolation.

### Source code dependencies

Drawn: the core in the middle, the driving side on the left and the driven side on the right; on both sides the source code dependency arrow points at the core.

- Source code dependencies point INWARD on both sides.
- The difference between the sides is the runtime control flow:
  - LEFT: the adapter calls the core and depends on the API the core offers (THE PORT).
    - Control: INWARD
    - Dependency: INWARD
  - RIGHT: the core calls the adapter at runtime, but the adapter depends on the interface the core defines (THE PORT).
    - Control: OUTWARD
    - Dependency: INWARD

### In the WP context

- The core is the campaign logic: when, to whom, what. In DDD this would be the core domain.
- The core knows its interfaces (THE PORTS). Something at startup (wiring or a DI container) plugs the concrete adapters in (interfaces, implementations on the right).

### Usually in code

- The right side port is almost always an explicit interface, because the adapters need to implement it.
- The left side port is often just the public methods. An explicit interface is useful if you want to test an adapter with a fake core.

### When looking at an app

- Count ports, not adapters. The left side often looks busy but still has few ports.
- Queues:
  - A message queue the app consumes from is a driving adapter on the left.
  - When the app publishes to the queue, this lands on the right.
- Inbox polling vs Kafka consuming (polling too!): each one lands on a different side:
  - Inbox polling has some heavy logic: don't poll after the campaign is sent, don't poll after an error, etc. The scheduling rules are the business logic here, so the scheduling belongs to the core and the app initiates the conversation with the external world through adapters.
  - So: the clock triggers it from the left, but the core makes the decision what to do next.
  - Kafka polling is logic hidden from the core, so for the business it is just like "events are flowing to me and driving me". The loop lives in the adapter.

### Core points

- Technology, linked to purpose.
- Technology is substitutable.
- The app outputs data to the UI and the user decides whether this should be saved. This might be in the core, but you can as well extract all of this to presentation control: for the core it is just output.
- The adapter in hexagonal is the usage of the Design Patterns Adapter: "convert the interface of a class into another interface clients expect".
