# Semaphores

Semaphore maintains a set of permits. It allows several threads in the same block of code.

* Each `acquire()` blocks if necessary until a permit is available and then takes it.
* Each `release()` adds a permit, potentially releasing a blocking acquirer.
* A semaphore with one permit acts as a mutual exclusive lock, **but** semaphore has no owner, so one thead could
  `acquire()` and another `release()`.
* Memory consistency: actions in a thread prior to calling "release" methods (e.g. `release()`) **happen-before**
  actions following a successful "acquire" methods (e.g. `acquire()`) in another thread.
* A `Semaphore` can be fair.
* You can request more than one permit `semaphore.acquire(2)` and then `semaphore.release(2)`.
* Same ideas on interruptibility as with `Lock` object.
* Additional options only for semaphores (not possible in `Lock` objects):
    * Reducing the number of permits (cannot increase).
    * Getting a count/a list of the waiting threads.

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

In the example:

1. The first 5 threads each take a permit and they call the API. The count drops to 0.
2. The other 15 block in `acquire()`, because there are no permits left.
3. One of the 5 finishes and calls `release()`. The count goes to 1 and one waiting thread takes in and goes in.
4. The API never sees more than 5 calls at a time.