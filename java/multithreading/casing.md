# Compare And Swap (CASing)

## Why

- The problem in concurrent programming is the concurrent access to shared memory.
- So: we can use synchronization for this.
- So: we could also use more efficient tools (synchronization has a cost).

## How

CAS takes three things:

- a location in memory,
- the existing value at that location (expected),
- a new value to replace that existing value.

It is a single atomic assembly instruction:

```
if (current value == expected) {
    replace it with the new value
    return true
} else {
    return false
}
```

## AtomicLong

1. The Java API will try to do the incrementation using the low-level CASing mechanism.
2. CASing will tell if it failed.
3. Try until success.

- So this is the thought behind loosening the synchronization: the code is not always *really* concurrent, and if it is not, then the operation above will succeed quickly in most cases.
- CASing works well when concurrency is not "too" high.
- So: not many threads are trying and trying again.

Implementations:

- `AtomicBoolean`
- `AtomicInteger`, `AtomicLong`
- `AtomicReference`

## Adders and accumulators

- `Atomic*` methods are about "modify and get" or "get and modify".
- Sometimes we don't need the get, so we can use `LongAdder` or `LongAccumulator`.
- Not returning the value allows to distribute the update on different cells when multiple threads are doing it.
- So: then `sum()` (`LongAdder`) or `get()` (`LongAccumulator`) merges the results.
