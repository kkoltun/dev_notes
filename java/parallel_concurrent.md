# Parallel and concurrent computing in Java

### List of the topics

1. Parallel vs concurrent.
2. Synchronized blocks.
3. Reentrant locks.
4. Happens-before link.
5. Volatile.
6. False sharing.
7. Singleton pattern:
   1. Naive approach - why it is incorrect in the multithreaded realm.
   2. Synchronized approach - why it is non-optimal?
   3. Double-check locking - why it is buggy:
      1. Check [article here](https://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html).
      2. Stack overflow [answer here](https://stackoverflow.com/a/3580658) and [Bloch's comment in the "Best Practices for Lazy Initialization" paragraph here](https://www.oracle.com/technical-resources/articles/javase/bloch-effective-08-qa.html).
   4. Correct approaches:
      1. Enum used for example in the `NaturalOrderComparator` class.
8. Potential pitfalls check Java Puzzlers item 77.

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