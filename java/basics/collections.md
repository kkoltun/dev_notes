# Java Collections

Facts:

* **Main interface**: `java.util.Collection` is the root interface of Collections Framework.
* **Subinterfaces of `java.util.Collection`**:
    * `Deque<E>`.
    * `List<E>`.
    * `Set<E>`.
    * `SortedSet<E> extends Set<E>`.
    * `NavigableSet<E> extends SortedSet<E>`.
* **The `Map` interface does not inherit from `Collection` interface.**
* **Implementation Classes**: `ArrayList`, `LinkedList`, `HashMap`, `TreeMap`, `HashSet`, `TreeSet`.
* **Thread-safe collections**: `java.util.concurrent` with `CopyOnWriteArrayList`, `ConcurrentHashMap`,
  `CopyOnWriteArraySet`.
* **Algorithms**: interfaces `Comparator<E>`, `Iterator<E>`...

Why do we need collections:

* Reduce development effort.
* Increase quality.
* Provide reusability and interoperability.
* Reduce effort to learn a new API.

## Interfaces

**`Set`**:

* No order guarantees in general (`LinkedHashSet` keeps insertion order, `SortedSet`/`TreeSet` are sorted.
* Cannot contain duplicate elements.
* Does not allow random-access.

**`List`**:

* Ordered collection.
* Can contain duplicate elements.
* All lists provide random-access:
    * Those marked `RandomAccess` provide fast access, like `ArrayList`.
    * For `LinkedList` it is O (n).

**`Queue`**:

* Usually FIFO manner.
* Uses provided comparator or elements` natural ordering.
* The head element is the element that would be removed by a call to `Queue#remove()` or `Queue#poll()` call.
* New elements are inserted to the tail.

**`Dequeue`**:

* A "double-ended-queue".

**`Map`**:

* Maps keys to values.
* Cannot contain duplicate keys.

**`NavigableSet` and `NavigableMap`**:

* A SortedSet and SortedMap extended with navigation methods reporting the closest matches for given search targets.
* Has methods `lower`, `floor`, `ceiling` and `higher` returning elements basing on the comparison.

## Classes

**`HashSet`**:

* `HashSet<E>` is backed by a `HashMap<E, Object>` - the value inserted is a dummy, static `Object()`.
* [OpenJDK implementation for Java 8.](https://github.com/openjdk-mirror/jdk/blob/jdk8u/jdk8u/master/src/share/classes/java/util/HashSet.java)
* You can provide the initial capacity and load factor while creating a `HashSet`. Load factor is a measure of how full
  the underlying map is allowed to get, before increasing capacity automatically.

**`TreeSet`**:

* This is an implementation of `NavigableSet` based on a `TreeMap`.
* You can use natural ordering of elements or provide a `Comparator`.

**`ArrayList`**:

* Resizable-array implementation of the `List` interface.
* Most operations run in (roughly speaking) linear time.

**`LinkedList`**:

* Doubly-linked list implementation of `List` and `Deque` interfaces.
* Operations that index into the list will traverse the list from the end which is closer to the specified index
  (see [here](https://github.com/openjdk-mirror/jdk/blob/adea42765ae4e7117c3f0e2d618d5e6aed44ced2/src/share/classes/java/util/LinkedList.java#L566)).

**`TreeMap`**:

* A Red-Black tree based `NavigableMap` implementation.

## Wrappers and other implementations

There are different kinds of wrappers/views/implementations:

* **Synchronized wrappers** - collections with automatic synchronization (thread-safety).
    * Iterating over them still needs a lock on the collection (`synchronized(list) { ... }`).
* **Read-only views** - used for example to provide clients with a reference to which they have read-only access while
  you have a reference to the backing collection.
* **Thread-safe collections** - collections that allow to be modified while iterating.
    * Plain, non-concurrent collections have fail-fast iterators that throw `ConcurrentModificationException`.
    * `java.util.concurrent` collections don't throw it:
        * `ConcurrentHashMap` has weakly consistent iterators (see below for description).
        * `CopyOnWrite*` collections iterate over a snapshot.

## HashMap

Facts:

* HashMap stores key-value pairs. Internally it stores a table of buckets. For each key-value pair, the index in the
  table is computed using `key.hashCode()` with some additional operation.
    * Before Java 1.4 % remainder was used - slow, but good distribution.
    * From Java 1.4 & bitmask is used - faster, but can result in bad distribution. The operation is `(h ^ h >>> 16)`
      and then index is computed using `(n -1) & hash`.
* Generally a bucket is kind of a linked list. However, if you have many clashes, the getting will have O (n)
  complexity, which is bad. This is why, when a bucket contains at least 8 entries AND the table is at least 64 slots,it
  transforms the bucket into a red-black tree (`HashMap.TreeNode extends LinkedHashMap.Entry`) Then O (n) becomes O (log
  (n)) if the keys are `Comparable`. Otherwise (big bucket, small table) it just resizes 2x table. This mechanism has
  been introduced in Java 1.8.
* Resizing - the resize is O (n) and happens all at once. This can be a latency spike. When you create a new
  `HashMap(100)`, you set the capacity and it is finally rounded to the power of two, so you get 128. However, the
  resize is done using also a load factor which is by default 0.75. So a resize will be one at 96 entries. If you want
  to hold **exactly** N elements, do capacity > N/0.75.
* Iteration is O (capacity + size), not only O (size).
* A key whose `hashCode` depends on a mutable state, mutated after insertion, becomes unreachable - it's in the wrong
  bucket, and `containsKey` returns false while the entry still occupies space. **Prefer immutable keys.**

## Iterators and their consistency

There are different kinds of iterators.

Fail-fast:

* Used by: `ArrayList`, `HashMap`, `TreeMap`, ...
* Changes during the loop: throws `ConcurrentModificationException` (best effort, not guaranteed).
    * This is based on `int modCount` that every collection has. Structural changes (add, remove, clear, resize)
      increment it. The iterator saves a copy when it's created and then compares when `next()` is called, not when
      `hasNext()`.
    * Many modifying operations **do not** change `modCount`: `list.set(i, x)`, `hashMap.put(existingKey, newValue)`.
    * This is no mean of controlling iteration in concurrent environment, this is only means of catching possible bugs.
    * Even with single thread you could get wrong results when modifying a collection while iterating over it without an
      exception - remove second to last element makes the next iteration use `hasNext()` and return false (without
      checking `modCount` - it is checked in `next()`).
* Cost: cheap.
* `Iterator.remove()` supported.

Weakly consistent:

* Used by: `ConcurrentHashMap`, `ConcurrentSkipListMap/Set`, `ConcurrentLinkedQueue`, `LinkedBlockingQueue`...
* Changes during the loop: allowed, may or may not be visible.
* Cost: cheap, no copying.
* `Iterator.remove()` usually supported.
* This means:
    * Does not throw the `ConcurrentModificationException` but at the same time does not promise a frozen view.
    * Every element that existed when the iterator was created, and wasn't removed, is returned exactly once.

Snapshot:

* Used by: `CopyOnWriteArrayList/Set`.
* Changes during the loop: allowed, never visible.
* Cost: every write copies the whole array.
* `Iterator.remove()` throws `UnsupportedOperationException`.
