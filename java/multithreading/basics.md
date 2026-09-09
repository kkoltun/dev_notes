**All shared variables should be accessed in a synchronized or a volatile way.**

### Synchronized block

* `synchronized` on a non-static method - the key is the instance.
* `synchronized` on a static method - the key is the class object.

### Stopping the thread

* **Not** via `stop()` method.
* Via `interrupt()` method. Send a signal to the thread.
* Checked via `isInterrupted()`.
* If thread is blocked or waiting (`wait()`, `notify()`, `join()`), it will throw `InterruptedException`.

### `wait()` and `notify()`

* They are invoked on a given object.
* The thread executing the invocation should hold the key of that object.
* **So: `wait()` and `notify()` cannot be invoked outside a synchronized block.**
* `wait()` released the key and puts the thread in a `WAIT` state.
* `notify()` releases a Thread in `WAIT` state and puts it in `RUNNABLE` state.
* If there are multiple threads, they are released randomly.

### Thread states

* `NEW` - not been run yet.
* `RUNNABLE` - after `start()` call, but scheduler has not given it a time slice. **This also includes the running
  state.**
* `TERMINATED` - completed the work.
* `BLOCKED` - waiting for entrance of synchronized block.
* `WAITING` - parked using `wait()`.
* `TIMED_WAITING` - parked using `sleep(ms)` or `wait(ms)`.

### CPU architecture

* Main memory:
    * Access: order of 100 ns.
    * Size: order of GBs.
* L2 cache:
    * Access: order of 7 ns.
    * Size: order of 256 kB.
* L1 cache:
    * Access: order of 0.5 ns.
    * Size: order of 32 kB.

* **Visibility** - a variable is said visible if the writes made on it are visible. Writes within synchronized block are
  visible.

```
+-------------------------------------------------------------------------+
|                               Main memory                               |
+-------------------------------------------------------------------------+

+-------------------------------------------------------------------------+
|                                   CPU                                   |
| +---------------------------------------------------------------------+ |
| |                                 L3                                  | |
| +---------------------------------------------------------------------+ |
| +---------------+ +---------------+ +---------------+ +---------------+ |
| |      L2       | |      L2       | |      L2       | |      L2       | |
| +---------------+ +---------------+ +---------------+ +---------------+ |
| +---------------+ +---------------+ +---------------+ +---------------+ |
| |      L1       | |      L1       | |      L1       | |      L1       | |
| +---------------+ +---------------+ +---------------+ +---------------+ |
| +---------------+ +---------------+ +---------------+ +---------------+ |
| |    Core 1     | |    Core 2     | |    Core 3     | |    Core 4     | |
| +---------------+ +---------------+ +---------------+ +---------------+ |
+-------------------------------------------------------------------------+
```

### Happens-before link

The **happens-before** link is defined in the Java Memory Model.

The visibility means "a read should return the value set by the **last** write". But what does **last** mean? We need a
timeline here.

Example:

1. T1 writes 1 to `x`.
2. T2 reads `x` and copies it to `r`.

What is the value of `r`:

1. Without **happens-before** link between T1 and T2 operations: `r` is unknown.
2. With **happens-before** link: `r = 1`.

So **happens-before** link establishes a binding between the read operation and **last** write operation.

How to set up a **happens-before** link:

* It exists between all synchronized or volatile write operations and all synchronized or volatile read operations that
  follow.

### False sharing

* The cache memory is organized in lines. Each line holds 64 bytes.
* Each write to a fragment of a line marks the entire line dirty.

Example:

1. Core 1 is only incrementing `a`.
2. Core 2 is only incrementing `b`.
3. The memory is laid out in such way, that both `a` and `b` land in the same line.
4. **Update of `a` marks the entire cache line dirty for the other caches (e.g. Core 2).**
5. After Core 1 updated `a`, Core 2 wants to update `b`, but sees that the cache line from the main memory is marked
   dirty when reads `b`. It needs to check the main memory, **despite the fact that `b` has not been updated**.

### Doubly checked locking

```java
private static Singleton instance;

static Singleton getWithDoublePhaseLocking() {
    if (instance != null) {
        return instance;
    }

    synchronized (Singleton.class) {
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }
}
```

Problem: non synchronized read supposed to return the value set by a synchronized write. **No guarantee that the read
will get the value set by the write.**

We need a **happens-before** link between the read returning the value and the write that sets it.

The `Singleton instance` should be `volatile`. But then we have the same performance issues as in the synchronized case.

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