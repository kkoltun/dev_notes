# Concurrent collections

## General

- Concurrent interfaces define contracts in concurrent environments.
- So: implementations follow those contracts.
- Some implementations are adapted to low concurrency, some to high.

## Vector and Stack

- Thread safe.
- Old, legacy.
- Very basically implemented (a lot of synchronization).

## CopyOnWriteArrayList and CopyOnWriteArraySet

- No locking for read operations.
- A write creates a new structure.
- The new structure replaces the old one by moving a pointer in a synchronized way.
- Use: many reads and very few writes, e.g. an application config list.

## Queues and stacks

Two types:

- FIFO = queue: `Queue`.
- LIFO = stack: `Deque`, which is both a queue and a stack.

Implementations:

- Every `BlockingQueue` implementation is thread safe.
- `ArrayBlockingQueue` – a thread safe bounded queue built on an array. Uses one `ReentrantLock` for both putting and
  taking, plus two `Condition`s built from it: `notFull` and `notEmpty`.
- `LinkedBlockingQueue` - optionally bounded queue built on linked nodes. There are two separate locks for putting and
  taking, so consumption does not block producing.
- `LinkedBlockingDeque` - optionally bounded deque using same mechanism as `ArrayBlockingQueue` with one lock and
  conditions.
- `PriorityBlockingQueue` - unbounded queue built on a heap.
- `ConcurrentLinkedQueue`/`ConcurrentLinkedDeque` – an unbounded queue/deque using CAS.

Problem:

- There can be multiple producing / consuming threads. The thread needs to know if there is space / anything to consume.
  Calling the `size()` method is not right, because `size()` then put / produce is not atomic.

Full queue handling with a blocking queue:

- Throw.
- Return false, after an optional timeout (`offer()` with a timeout or without).
- Block until a cell becomes available (`put()`).

## Concurrent maps

Implementations:

- `ConcurrentHashMap` – made to handle very high concurrency, millions of keys / values.
- `ConcurrentSkipListMap`.

`ConcurrentMap`:

- Adds atomic operations: `putIfAbsent`, `remove`, `replace`.

## ConcurrentHashMap since Java 8

- One flat array, like in `HashMap`.
- The lock covers only a single bucket.
- Put:
    - A retry loop (CAS).
    - If the bucket is empty, no lock is taken, CAS is used.
    - If CAS failed and the bucket is not empty, or it has never been empty, then synchronize on the bucket's first
      element and add the entry / replace the value.
    - The first thing to do after locking: check if this is still the first entry.
- Reads do not use locks.

Methods (the interesting ones):

- `search()` – parallel search.
- `reduce()` – parallel reduction.
- `forEach()` – parallel forEach.
- `newKeySet()` – returns a `Set` backed by a `ConcurrentHashMap`.

The parallel methods:

- Run on `ForkJoinPool.commonPool()`, like parallel streams; you cannot pass your own pool.
- The first argument, `parallelismThreshold`, is the map size from which the work is split: `Long.MAX_VALUE` = sequential,
  `1` = as parallel as possible.
- So: no blocking work inside them, it stalls the pool shared by the whole JVM (see
  [`stream_parallel.md`](../stream_parallel.md)).

## ConcurrentSkipListMap

### Skip list

- A smart structure based on a sorted linked list with extra layers of shortcut links on top.
- Relies on atomic reference operations, no synchronization.
- Used in the JDK to create maps and sets.
- A `LinkedList` takes O (n) to get to index i.
- So: you create one or more layers of fast access lists; the elements in the list must be sorted.
- So: the average access time is O (log (n)).

```
  1                       5
  |                       |
  1 <-------> 3 <-------> 5 <-------> 7
  |           |           |           |
  1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8
  head                                    tail
```

- When looking for an element, go from the top of the access list to the bottom, the searched list halving on each
  step => O (log (n)).

Summary of the skip list:

- Keys sorted.
- Used to implement a map.
- Ensures fast access to a key.
- Not array based.

### ConcurrentSkipListMap and ConcurrentSkipListSet

Comparing `ConcurrentSkipListMap` to `ConcurrentHashMap`:

- The `ConcurrentHashMap` has a set of operations to be done when putting and the bucket is not empty. These operations
  have to be atomic. You need synchronization.
- With the skip list, you do only one reference change inside the core linked list, which is CAS. Then you fix the
  shortcuts (upper levels) one by one, but they can briefly lag, because they are only shortcuts.

Making it thread safe:

- `ConcurrentSkipListMap` / `ConcurrentSkipListSet` use skip lists.
- References implemented with a CAS mechanism like the one in the `AtomicReference`.
- A thread safe map without synchronization.
- Tailored for concurrency.
