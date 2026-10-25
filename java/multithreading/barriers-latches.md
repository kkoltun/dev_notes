# Barriers and latches

## Barriers

- Having several threads waiting for each other.
- Computation is shared among several threads.
- Each thread is given a subtask.
- When all threads are done, a merging operation is run.

Steps:

1. Distribute the computation on several threads.
2. We need to know when all threads have finished their task.
3. We need to launch a post-processing.

```java
CyclicBarrier barrier = new CyclicBarrier(4); // the number of threads that will be launched

barrier.await(); // from inside the task! Blocks until everybody is ready.
```

### The CyclicBarrier class

- Default state: closed.
- Calling `await()` from the task counts how many times it was called; when the count is equal to the defined one, the
  barrier is opened and the execution is continued.
- Then we register a callback task that is invoked when the last party arrives **before** the barrier releases anyone.
- `await()` can accept a timeout.
- There is also a reset: the release and the reset are both in one step. When the last party arrives, it does under its
  lock:
    - runs the barrier action (a callback you can set, in the thread that arrived last),
    - it trips: wakes every waiting thread and at once starts a new round.
- So: a cyclic barrier is "cyclic" because it resets after each opening.

Exceptions:

- Broken barrier: a waiting thread is interrupted or times out; other waiters get `BrokenBarrierException`, so does
  every later `await()`; a broken barrier does not reset.
- `reset()` called by hand: any waiter gets the same exception; it is for recovering the broken barrier.

## Latches

- Similar to a barrier, but once it reaches zero, it never resets.
- Implementation: `CountDownLatch`.
- No way to pass a callback to invoke when the latch reaches zero.

## Differences between barriers and latches

- With a barrier, the task `await()`s for the others to finish.
    - You can do the merging in a callback.
    - You can `await()` before merging in a separate thread, and then do it.
- With a latch, the tasks count it down, while the merging thread awaits on it and will continue when the latch reaches
  zero.
