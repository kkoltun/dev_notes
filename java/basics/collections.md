# Java Collections

Facts:
* **Main interface**: `java.util.Collection` is the root interface of Collections Framework.
* **Subinterfaces of `java.util.Collection`**: `Deque<E>`, `List<E>`, `NavigableSet<E>`, `Queue<E>`, `Set<E>`, `SortedSet<E>`.
* **The `Map` interface does not inherit from `Collection` interface.**
* **Implementation Classes**: `ArrayList`, `LinkedList`, `HashMap`, `TreeMap`, `HashSet`, `TreeSet`.
* **Thread-safe collections**: `java.util.concurrent` with `CopyOnWriteArrayList`, `ConcurrentHashMap`, `CopyOnWriteArraySet`.
* **Algorithms**: interfaces `Comparator<E>`, `Iterator<E>`...

Why do we need collections:
* Reduce development effort.
* Increase quality.
* Provide reusability and interoperability.
* Reduce effort to learn a new API.

## Interfaces

**`Set`**:
* Unordered collection.
* Cannot contain duplicate elements.
* Does not allow random-access.

**`List`**:
* Ordered collection.
* Can contain duplicate elements.
* Usually provides random-access.

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
* You can provide the initial capacity and load factor while creating a `HashSet`. Load factor is a measure of how full the underlying map is allowed to get, before increasing capacity automatically.

**`TreeSet`**:
* This is an implementation of `NavigableSet` based on a `TreeMap`.
* You can use natural ordering of elements or provide a `Comparator`.

**`ArrayList`**:
* Resizable-array implementation of the `List` interface.
* Most operations run in (roughly speaking) linear time.

**`LinkedList`**:
* Doubly-linked list implementation of `List` and `Deque` interfaces.
* Operations that index into the list will traverse the list from the end which is closer to the specified index (see [here](https://github.com/openjdk-mirror/jdk/blob/adea42765ae4e7117c3f0e2d618d5e6aed44ced2/src/share/classes/java/util/LinkedList.java#L566)).

**`TreeMap`**:
* A Red-Black tree based `NavigableMap` implementation.

## Wrappers and other implementations

There are different kinds of wrappers;
* **Synchronized wrappers** - collections with automatic synchronization (thread-safety).
* **Unmodifiable wrappers** - used for example to provide clients with a reference to which they have read-only access while you have a reference to the backing collection.
* **Thread-safe collections** - collections that allow to be modified while iterating. By default, the iterator is fail-fast and throws `ConcurrentModificationException`.


