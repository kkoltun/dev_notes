# Java `Object#equals()` and `Object#hashCode()` methods

Every `java.lang.Object` has two important methods defined:
* `public boolean equals(Object obj)`;
* `public int hashCode(Object obj`).

### equals() method

Java method `equals()` is used to compare equality of two Objects. There are two ways of comparison:
* **Shallow comparison** - this is the default implementation of `java.lang.Object.equals()`. Is simply checks if two Object references refer to the same object (using `==` operator);
* **Deep comparison** - this can be provided as own implementation. The comparison can be done w.r.t. state of the Objects.

Any implementation of `equals()` method has to be:
* **Reflexive** - for any reference value `a`, `a.equals(a)` should return `true`.
* **Symmetric** - for any reference values `a` and `b`, if `a.equals(b)` returns `true`, then `b.equals(a)` should return `true`.
* **Transitive** - for any reference values `a`, `b` and `c`, if `a.equals(b)` and `b.equals(c)` then `a.equals(c)` should return `true`.
* **Consistent** - for any reference values `a` and `b`, multiple invocations of `a.equals(b)` consistently return `true` or consistently return `false`, provided no information used in comparison on the object is modified.

Furthermore, for any non-null reference `a`, `a.equals(null)` should return false.

### hashCode() method

Java method `hashCode()` returns hashcode value as an Integer. **This method must be overridden in every class which overrides equals() method.**

The general contract of `hashCode()` is:
* Consistent - it must be consistent, although it is not necessary that it returns the same numbers from one execution of the application to another.
* Equality - if two objects are equal (according to `equals()` method), then `hashCode()` method must produce the same `Integer` on each of the two objects.
* Inequality - if two objects are unequal (according to `equals()` method), the `hashCode()` does not have to produce two distinct numbers. However, producing distinct values on each of the two objects is better for improving performance of hashing based collections.

### Implementing these methods

Check:
* [artima](https://www.artima.com/articles/how-to-write-an-equality-method-in-java)
* [jenkov](https://jenkov.com/tutorials/java-collections/hashcode-equals.html)
* [graceful blog](http://gracelang.org/applications/2011/02/07/values-equals-and-hashcodes/)

### Implementing these methods in the Hibernate context

Check:
* [Vlad Mihalcea](https://vladmihalcea.com/the-best-way-to-implement-equals-hashcode-and-tostring-with-jpa-and-hibernate/)
* [Thorben Janssen](https://thorben-janssen.com/ultimate-guide-to-implementing-equals-and-hashcode-with-hibernate/)