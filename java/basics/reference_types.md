# Weak, soft and phantom references

**Strong reference**:
* For example: `StringBuffer buffer = new StringBuffer();`.
* If an object is reachable via a chain of strong references (**strongly reachable**), it is not eligible for garbage collection.
* A cyclic reference is a case in which an object with strong reference will be garbage collected. 
* **When strong reference is too strong:** for example in the caching mechanism - having only strong references, we would decide what to remove from cache on our own, to enable GC mechanism.

**`ReferenceQueue`**:
* When passed into reference's constructor, the reference will be automatically inserted into the reference queue when the object to which it pointed became garbage.

**`WeakReference`**:
* Reference which isn't strong enough to force object to remain in memory.
* For example: `WeakReference<Widget> weakWidget = new WeakReference<Widget>(widget);`.
* When `WeakReference#get()` starts returning `null`, it means that the object it pointed to has become garbage.

**`SoftReference`**:
* This reference may stick around after the object became **weakly reachable** and before it is collected.
* **Object recurrection**: calling `get()` on an object that is **weakly reachable** but before the garbage collector collects it.
* The object will surely be collected before 

**`Phantom reference`**:
* `PhantomReference#get()` always returns `null` - it can never be resurrected.
* The point of this reference is to know when an object has been collected, by inspecting the `ReferenceQueue` used when creating the reference.
