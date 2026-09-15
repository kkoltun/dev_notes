# Java `Object#equals()` and `Object#hashCode()` methods

Every `java.lang.Object` has two important methods defined:

* `public boolean equals(Object obj)`;
* `public int hashCode()`).

## equals () method

Java method `equals()` is used to compare equality of two Objects. There are two ways of comparison:

* **Shallow comparison** - this is the default implementation of `java.lang.Object.equals()`. Is simply checks if two
  Object references refer to the same object (using `==` operator);
* **Deep comparison** - this can be provided as own implementation. The comparison can be done w.r.t. state of the
  Objects.

Any implementation of `equals()` method has to be:

* **Reflexive** - for any reference value `a`, `a.equals(a)` should return `true`.
* **Symmetric** - for any reference values `a` and `b`, if `a.equals(b)` returns `true`, then `b.equals(a)` should
  return `true`.
* **Transitive** - for any reference values `a`, `b` and `c`, if `a.equals(b)` and `b.equals(c)` then `a.equals(c)`
  should return `true`.
* **Consistent** - for any reference values `a` and `b`, multiple invocations of `a.equals(b)` consistently return
  `true` or consistently return `false`, provided no information used in comparison on the object is modified.

Furthermore, for any non-null reference `a`, `a.equals(null)` should return false.

## hashCode () method

Java method `hashCode()` returns hashcode value as an Integer. **This method must be overridden in every class which
overrides equals () method.**

The general contract of `hashCode()` is:

* Consistent - it must be consistent, although it is not necessary that it returns the same numbers from one execution
  of the application to another.
* Equality - if two objects are equal (according to `equals()` method), then `hashCode()` method must produce the same
  `Integer` on each of the two objects.
* Inequality - if two objects are unequal (according to `equals()` method), the `hashCode()` does not have to produce
  two distinct numbers. However, producing distinct values on each of the two objects is better for improving
  performance of hashing based collections.

## JVM implementations of hashCode ()

The implementation depends on the `-XX:hashCode=` value. There are different implementations, even a constant 1 for
sensitivity testing. Default is 5.

The default implementation:

1. Every Java thread carries a tiny private random-number generator: four 32-bit numbers called X, Y, Z, W.
2. When a thread asks an object for its identity hash for the first time, the JVM cranks that generator one step - shift
   some bits, XOR them together, slide the state along.
3. The resultant number becomes the object's hash.

Important parts:

1. It never looks at the object, not its address, not its contents. It is virtually "give me the next number from my
   private stream".
2. It is lazy.
3. It is sticky. The first time you ask, the value is written into the object's header and stays there forever. GC can
   move the object around across the heap withou the hash changing.
4. It is cheap and scales. The generator state lives on the thread. Two threads hasing objects at the same time never
   touch the same memory. **This is important, because older implementations (JDK 6 and 7) used one global generator.
5. Fun fact: it is never negative, because the value is masked down to 31 bits AND if it produces 0, you get 0xBAD
   (2989) instead, because 0 is reserved for "no hash stored yet".

**Hashcode is not using the objects memory location.** Java 1.0 through Java 8 docs suggested that, which is the source
of the myth ([javadoc](https://docs.oracle.com/javase/8/docs/api/)):

> As much as is reasonably practical, the hashCode method defined by class Object does return distinct integers for
> distinct objects. (This is typically implemented by converting the internal address of the object into an integer, but
> this implementation technique is not required by the Java™ programming language.)

## Implementing these methods

Check:

* [artima](https://www.artima.com/articles/how-to-write-an-equality-method-in-java)
* [jenkov](https://jenkov.com/tutorials/java-collections/hashcode-equals.html)
* [graceful blog](http://gracelang.org/applications/2011/02/07/values-equals-and-hashcodes/)

## Implementing these methods in the Hibernate context

Check:

* [Vlad Mihalcea](https://vladmihalcea.com/the-best-way-to-implement-equals-hashcode-and-tostring-with-jpa-and-hibernate/)

Put shortly:

* If you have an entity with assigned identifiers (natural identifiers, database-agnostic UUIDs) then the ID is known
  when persisting, so you can just implement ordinary hashCode () basing on the ID value (e.g. Objects.hash (getIsbn
  ())). However here you must **make sure that the properties used for these operations are immutable and unique**.
* If you have an entity with database-generated identifiers, then the identifier is assigned by the database during
  flush-time, the consistency guarantee breaks - the object representing same entity will have different `hashCode()`
  values before and after persisting. Then you can just implement a static hashCode () e.g. `getClass().hashCode();`.
    * The performance penalty due to a single hash bucket will be visible only in large collections with tens of
      thousands of object, but then... why are you fetching so many entities from the database? This has multiple orders
      of magnitude higher cost than the issues with collections!
* **Take into consideration that Hibernate uses proxies.** E.g. do not use `getClass() != o.getClass()` in equals (),
  use `o instanceof Account other` instead. The `return getClass().hashCode();` is safe here, because the proxy doesn't
  answer `hashCode()` itself.

* [Hibernate docs](https://docs.hibernate.org/stable/core.old/reference/en/html/persistent-classes-equalshashcode.html)

## Java `record` classes

`equals()` implementation:

* Reference types use `Objects.equals(a, b)`.
* Primitive types other than float/double use `==`.
* `float` use `Float.compare(a, b) == 0`.
* `double` use `Double.compare(a, b) == 0`.

The last two points are deliberate, because:

* `Double.compare` treats `NaN` as equal to itself and `+0.0` **not** equal to `-0.0`. Using `==` produces exactly
  opposite results, in which case `NaN` would break reflexivity. Same for `Float`.

`hashCode` implementation is derived from the components' hash codes. It is explicitly declined what exactly is done.

Storing arrays in a record is **not a good idea**: `record Data(byte[] payload) {}`. These go through `Object.equals`
and `Object.hashCode` which means reference identity. Two `Data` instances holding identical bytes are not equal.
