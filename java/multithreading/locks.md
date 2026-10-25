# Locks

* Intrinsic locking - using `synchronized`. Problems with it:
    * A thread waiting for a lock cannot time out, be interrupted or give up. If the holder gets stuck indefinitely,
      waiters are stuck forever and usually the only way out is rebooting JVM.
    * It is exclusive only with no shared (read) mode.
    * No fairness options - no FIFO option guaranteeing that the longest-waiting thread gets the lock.
* Explicit locking - using `Lock`.
    * Many more options and methods, check below.

## Lock patterns introduced by the `Lock`

### Interruptible Lock Acquisition

```
Lock lock = new ReentrantLock();
lock.lockInterruptibly();
try {
    // work
} finally {
    lock.unlock();
}
```

### Timed Lock Acquisition

```
Lock lock = new ReentrantLock();
if (lock.tryLock(1, SECONDS)) {
    try {
        // work
    } finally {
        lock.unlock();
    }
} else {
    log.error("Could not do the work - timed out while waiting for lock");
}
```

### Fair Lock Acquisition

```
Lock lock = new ReentrantLock(true); // enables fairness; beware: it is costly
lock.lock();
try {
    // work
} finally {
    lock.unlock();
}
```

## `Condition` objects used with `Lock` objects

A `Condition` object is used to park and awake threads:

The `await()` method:

* The call is blocking.
* The waiting can be interrupted, unless you used `awaitUninterruptibly()`.
* You can set timeout.
* A fair `Lock` generates a fair `Condition`.
* A `Lock` object can have any number of `Condition` objects.

## `ReadWriteLock` pattern

The regular `Lock` is exclusive - no way to get granularity like "writes lock reads and writes; reads lock writes".

The `ReadWriteLock` is an interface that returns `Lock` objects, the `ReentrantReadWriteLock` is the implementation:

* When write lock is held, no one can hold the read lock.
* Any number of threads can hold the read lock.