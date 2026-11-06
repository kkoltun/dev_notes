# Delivery Framework

Handwritten notes from [Hello Interview, *System Design in a Hurry*](https://www.hellointerview.com/learn/system-design/in-a-hurry/introduction). Back to [System design](../system_design.md).


**CRITICAL: First deliver a working system. Then work on non-functional requirements.**

```
                                                                                                       Primary Goal: Satisfy
                                                                                                    Non-functional Requirements
                                                                                  Primary Goal: Satisfy          │
                                                                                 Functional Requirements         │
                                                                                            │                    │
                                                                                            ▼                    ▼
┌(1)────────────┐    ┌(2)────────────┐    ┌(3)────────────┐    ┌(4)┄┄┄┄┄┄┄┄┄┄┄┄┐    ┌(5)────────────┐    ┌(6)────────────┐
│               │    │               │    │               │    ┆               ┆    │               │    │               │
│  Requirements │ ─▶ │ Core Entities │ ─▶ │     API or    │ ╌▶ ┆   Data Flow   ┆ ╌▶ │   High-level  │ ─▶ │   Deep Dives  │
│               │    │               │    │   Interface   │    ┆               ┆    │     Design    │    │               │
│               │    │               │    │               │    ┆               ┆    │               │    │               │
└───────────────┘    └───────────────┘    └───────────────┘    └┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┘    └───────────────┘    └───────────────┘
                                                                                            ▲
                                                                                            │
                                                                                ★ YOU MUST ARRIVE HERE ★
```

Redraw from https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery.

The steps, in order:

1. Requirements (5 min).
2. Core Entities (2 min).
3. API or Interface (5 min).
4. (Optional) Data Flow (5 min).
5. High level design (10-15 min).
6. Deep dives (10 min).

Capacity estimation hangs off the requirements.

## Requirements

Functional requirements:

- A prioritized list of core features.
- Top 3.

Non-functional requirements:

- System qualities that are important to the users.
- Put in context and quantified.
- CAP: consistency vs availability.
- Environment constraints.
- Scalability: peak hours, Black Friday etc.
- Read vs write ratio.
- Latency, especially for reads requiring computation.
- Durability.
- Security.
- Fault tolerance.
- Compliance.

## Core Entities

- The data central to the design.
- The data you send via the API, save in the data model.
- Create a small list, do not aim to cover 100%.

## API or System Interface

Contract between your system and its users.

- REST: HTTP verbs.
    - Default choice.
- GraphQL: lets clients specify exactly what data they want, avoiding over- and underfetching.
    - Many clients with different needs.
- RPC: action-oriented protocol, faster than REST for service-to-service communication.
    - Internal API, performance critical.

## Optional: Data Flow

- High level sequence of actions or processes that the system performs on the inputs to produce outputs.

## High level design

Boxes and arrows to represent the different components of the system and how they interact.

- Do not overthink! Design an architecture that satisfies the API and requirements.
- Stay focused! Do a relatively simple design that meets the core requirements, then layer on complexity to satisfy the
  non-functional requirements.
- When designing this, you will identify needs for adding complexity: note them for later.
- Document only a high level of the data layout.

### Questions to ask yourself

Run them over your own design before the interviewer does.

- What happens if this message arrives twice?
    - So: a retried callback or event must not repeat its effect (a second refund, a second email).
- What if it arrives late, or a scheduled run is late?
- Who is allowed to call this?
    - So: a public callback must prove it comes from the provider (signature, shared secret, or ask its API).
- What does the user see while this part is down?
- For every time on the board: whose zone is it in, and does it repeat?
    - So: a repeating rule is stored as local time plus the zone; a single event as a UTC instant.

## Deep dives

Now you have a high level design. Now you focus on:

- Meeting non-functional requirements.
- Addressing edge cases.
- Identifying and addressing issues and bottlenecks.
- Improving the design based on probes from the interviewer.

Then:

- Act proactively.
- Give room to the interviewer to ask questions and probe the design.
