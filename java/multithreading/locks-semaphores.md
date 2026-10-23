# Locks and semaphores

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

## Semaphores

Semaphore maintains a set of permits.

* Each `acquire()` blocks if necessary until a permit is available and then takes it.
* Each `release()` adds a permit, potentially releasing a blocking acquirer.
* A semaphore with one permit acts as a mutual exclusive lock, **but** semaphore has no owner, so one thead could
  `acquire()` and another `release()`.
* Memory consistency: actions in a thread prior to calling "release" methods (e.g. `release()`) **happen-before**
  actions following a successful "acquire" methods (e.g. `acquire()`) in another thread.

```
// 20 threads call an external API that allows at most 5 calls at a time

private final Semaphore apiSlots = new Semaphore(5);

String callApi(Request request) throws InterruptedException {
    apiSlots.acquire();          // takes one of the 5 permits, or waits
    try {
        return client.send(request);
    } finally {
        apiSlots.release();      // gives the permit back
    }
}
```

About the example:

1. The first 5 threads each take a permit and they call the API. The count drops to 0.
2. The other 15 block in `acquire()`, because there are no permits left.
3. One of the 5 finishes and calls `release()`. The count goes to 1 and one waiting thread takes in and goes in.
4. The API never sees more than 5 calls at a time.