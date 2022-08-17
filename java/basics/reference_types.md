# Weak, soft and phantom references

## Problem to solve here

Many computer programming languages offer dynamic memory allocation.
This feature requires also the memory to be somehow freed up when the objects are no longer needed.

According to a great restaurant analogy created by Uberto Barbini [here](https://medium.com/@ramtop/weak-soft-and-phantom-references-in-java-and-why-they-matter-c04bfc9dc792), it is similar to the restaurants:
* You have a limited set of tables (memory units) in the restaurant (system).
* The restaurant (memory) can fill up after some time.
* You need to somehow have the tables (memory units) free up after they are no longer used.
* In some restaurants you should clean up after yourself, for example MCDonalds (C programming language). Everything works well provided that everyone behaves well.
* In other restaurants, you can leave the table untidy (Java programming language). The staff (Garbage Collector) will take care of cleaning up the table (memory) and freeing it up for next people (processes).

In Java, there is a separate program called Garbage Collector that uses sophisticated methods to free up the memory.
It will automatically remove the objects that are not reachable anymore.

So, the proglem is: **what if we want to keep a reference to an object, but we don't want to prevent GC to free it when there is no other reference?**

The problem is solved using the reference-object classes, which support a limited degree of interaction with the garbage collector.

## Object reachability

There are different levels of reachability that reflect the life cycle of an object:

1. **Strongly reachable** - can be reached by some thread without traversing any reference objects. New object is strongly reachable by the thread that created it.
2. **Softly reachable** - not strongly reachable, but can be reached by traversing a soft reference.
3. **Weakly reachable** - neither strongly, not softly reachable but can be reached by traversing a weak reference. **When the weak references to weakly-reachable object are cleared, the object becomes eligible for finalization.**
4. **Phantom reachable** - neither strongly, softly, nor weakly reachable, it has been finalized, and some phantom references to it.
5. **Unreachable** - not reachabe in any of the above ways

## Strong reference

* For example: `StringBuffer buffer = new StringBuffer();`.
* If an object is reachable via a chain of strong references (**strongly reachable**), it is not eligible for garbage collection.
* A cyclic reference is a case in which an object with strong reference will be garbage collected.
* **When strong reference is too strong:** for example in the caching mechanism - having only strong references, we would decide what to remove from cache on our own, to enable GC mechanism.

## Reference objects

* These are special classes to use, when the strong reference turns out to be too strong.
* There is a `get()` method that returns the referent (a strong reference to it). If this reference object has been cleared, either by the program or by the garbage collector, then this method returns `null`.
* There is a reference queue - a queue to which the registered reference objects are appended by the garbage collector after the appropriate reachability changes are detected.

### Soft reference objects

* Class: `java.lang.ref.SoftReference`.
* GC behavior: objects cleared at the discretion of the garbage collector in response to memory demand. All soft references are guaranteed to have been cleared before the virtual machine throws an `OutOfMemoryError`.
* Automatically-cleared reference: YES.
* Shortly speaking: *this one ries to keep the reference*.
* Resurrecting an object: calling `get()` can resurrect the referent (go from soft reachable to strong reachable).
* Checking if the object is finalized: the reference is automatically-cleared, so check if `get()` returned `null`.
* Reference queue: object is added there **after** finalization.
* Usage: memory sensitive caches. Idea: a sophisticated cache can prevent its most recently used entries from being discarded by keeping strong referents to those entries, leaving the remaining entries to be discarded at the discretion of the garbage collector.

> Suppose that the garbage collector determines at a certain point in time that an object is softly reachable.
> At that time **it may choose** to clear atomically all soft references to that object and all soft references to any other softly-reachable objects from which that object is reachable through a chain of strong references.

### Weak reference objects

* Class `java.lang.ref.WeakReference`.
* GC behavior: objects that do not prevent their referents from being finalizable, finalized and then reclaimed.
* Automatically-cleared reference: YES.
* Shortly speaking: *this one does not keep the reference*.
* Resurrecting an object: calling `get()` on an object can resurrect it (go from weak reachable to strong reachable).
* Checking if the object is finalized: the reference is automatically-cleared, so check if `get()` returned `null`.
* Reference queue: object is added there **after** finalization.
* Usage: canonicalizing mappings.

> Suppose that the garbage collector determines at a certain point in time that an object is weakly reachable.
> At that time **it will** atomically clear all weak references to that object and all weak references to any other weakly-reachable objects from which that object is reachable through a chain of strong and soft references.
> At the same time it will declare all of the formerly weakly-reachable objects to be finalizable.

## Phantom reference objects

* Class `java.lang.ref.PhantomReference`.
* GC behavior: When an object becomes phantom reachable, it will be enqueued. However, you cannot reach the object itself, because it cannot leave that state. So, `get()` always returns `null` here. Otherwise, the object would become strongly reachable again. The referent of a phantom reference is always inaccessible.
* Automatically-cleared reference: NO.
* Shortly speaking: this one *does not free the reference until cleared*.
* Resurrecting an object: not way to do this, `get()` returns `null`.
* Checking if the object is finalized: here the `get()` method will not work. You need to use the reference queue instead.
* Reference queue: object is added there **before** finalization. So, if you don't poll the queue, the actual objects referenced by Phantom will not be finalized and might end up in `OutOfMemory` error.
* Usage: scheduling pre-mortem cleanup actions in a more flexible way than is possible with the Java finalization mechanism.

> If the garbage collector determines at a certain point in time that the referent of a phantom reference is phantom reachable, then at that time or at some later time it will enqueue the reference.
> In order to ensure that a reclaimable object remains so, the referent of a phantom reference may not be retrieved: The get method of a phantom reference always returns null.
> Unlike soft and weak references, phantom references are not automatically cleared by the garbage collector as they are enqueued. An object that is reachable via phantom references will remain so until all such references are cleared or themselves become unreachable.