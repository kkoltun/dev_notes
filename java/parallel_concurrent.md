# Parallel and concurrent computing in Java

### List of the topics

1. Thread lifecycle.
2. The thread as a set of tasks.
3. Parallel vs concurrent.
4. Synchronized blocks.
5. Reentrant locks.
6. Happens-before link.
7. Volatile.
8. False sharing.
9. Usage of wait() and notify() methods; implementing Consumer/Producer.
10. Singleton pattern:
    1. Naive approach - why it is incorrect in the multithreaded realm.
    2. Synchronized approach - why it is non-optimal?
    3. Double-check locking - why it is buggy:
       1. Check [article here](https://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html).
       2. Stack overflow [answer here](https://stackoverflow.com/a/3580658) and [Bloch's comment in the "Best Practices for Lazy Initialization" paragraph here](https://www.oracle.com/technical-resources/articles/javase/bloch-effective-08-qa.html).
    4. Correct approaches:
       1. Enum used for example in the `NaturalOrderComparator` class.
11. Potential pitfalls check Java Puzzlers item 77.
12. Class `Runnable` vs `Callable`.
13. Using `Future` objects.
14. ExecutorServices:
    1. Executor Pattern - why is it better than using just `new Thead(runnable).start()`.
    2. CachedExecutorService
    3. ScheduledExecutorService, difference between scheduleAtFixedRate and scheduleAtFixedDelay.
    4. Shutting down - difference between shutdown(), shutdownNow(), awaitTermination().
15. Synchronization:
    1. Intrinsic locking using synchronized and volatile (language primitives).
    2. Explicit locking with Lock
       1. What is guaranteed by the Lock mechanism?
       2. What is the difference between this way and intrinsic locking?
       3. Interruptible lock patten and usage.
       4. Timed lock acquisition pattern and usage.
       5. Fair lock acquisition pattern and usage.
    3. Condition mechanism
       1. Using Condition objects.
       2. Difference between wait()/notify() and Condition.
    4. Read-write locks - have exclusive writes, but parallel reads.
16. Semaphores; fairness; acquiring more permits; reducing the number of permits; increasing (possible?); checking the semaphore state.
17. Thread-local
18. CASing - Compare And Swap
    1. Is it always essential to use synchronization?
    2. How CASing works - what are the parameters and what is done
    3. What are the usages?
    4. Atomic variables
    5. Adders and accumulators
19. Concurrent collections:
    1. What it means for an interface to be concurrent? This is only a contract.
    2. Implementations can fulfill the contract, but at the same time be prepared to different levels of concurrency (10 vs 10k threads).
    3. Vector and Stack, why not use them
    4. Copy On Write structure, how it works, implementations, when to use them
    5. Queue, BlockingQueue, Deque, BlockingDeque structures:
       1. Modification methods add(), offer(), offer() with a timeout, put()
       2. Methods poll() and peek(); remove() and element(); take()
    6. ConcurrentMap implementations:
       1. ConcurrentHashMap - atomic operations - remove, replace and putIfAbsent
       2. Skip lists mechanism
       3. ConcurrentSkipList and ConcurrentSkipSet, advantages, how they work

### Writing good concurrent code

1. Check for race conditions:
   1. What is happening to the fields (not variables/parameters).
   2. If two threads are reading or writing a given field, you have a race condition.
2. Check for the happens-before link - if you want things to be correct on the analysed field, it needs to have a happens-before link between the read operations and write operations.
   1. Are read/write volatile?
   2. Are they synchronized?
   3. If not, there is probably a bug.
3. Choose synchronized or volatile.
   1. Do you need atomicity on that piece of code? If so, use synchronized, the code will not be interruped by other threads.
   2. Do you need only visibility? If so, use volatile.
4. Look out for false-sharing, use rather synchronized on a `private final static Object lock` rather than class instance.
   Other library can unlock the synchronized lock if it is available from outside. For example call `wait()` inside your synchronized block will unlock it for other threads. See Java Puzzlers item 77.