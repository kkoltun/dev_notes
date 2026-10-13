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
try {
    lock.lockInterruptibly();
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
try {
    lock.lock();
    // work
} finally {
    lock.unlock();
}
```