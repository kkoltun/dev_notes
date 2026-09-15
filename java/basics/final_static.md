# Final

## Final class

A final class cannot be subclassed. Many classes in Java are final - `java.lang.System`, `java.lang.String`. This has
mostly security and architectural benefits.

In history, this had also efficiency benefits, but now HotSport devirualizes and inlines non-final methods using class
hierarchy analysis over the classes actually loaded.

## Final methods

A final method cannot be overridden or hidden by subclasses.
This is usually used to prevent unexpected behavior from a subclass altering a method that may be crucial to the
function or consistency of the class.

## Final variables - references

A final variable can only be initialized once, either via an initializer or an assignment statement.

If a variable is a reference:

* the variable cannot be re-bound to reference another object;
* the object it references is **still mutable**, if it was originally mutable.

Passing to methods:

* `final` applies to a variable, not the object.
* Arguments are passed by value (a copy of the reference), so a method receiving a final variable gets its own non-final
  parameter.
* The method itself can change the reference (reassign), but that doesn't affect the caller's variable.
* The method can, however, mutate the referenced object if it's mutable.

```java
public class FinalVariableSandbox {

    public static void main(String[] args) {
        final String mainFoo = "original";

        final FinalVariableSandbox sandbox = new FinalVariableSandbox();
        sandbox.bar(mainFoo);

        System.out.println("main: " + mainFoo);
    }

    private void bar(String foo) {
        foo = "CHANGED " + foo;

        System.out.println("bar: " + foo);
    }
}
```

compiles and produces:

```
bar: CHANGED original
main: original
```

## Final variables inside a class

* A blank final instance variablemust be defintely assigned:
    * By the end of every constructor.
    * In its declaration.
    * In an instance initializer block.
* A blank static final variable must be definitely assigned:
    * In a static initializer block.
    * In its declaration.

Instance initializer block:

```java
public class Foo {
    private final List<String> names;
    private final int id;

    // instance initializer block
    {
        names = new ArrayList<>();
        names.add("default");
    }

    Foo() {
        id = 1;
    }

    Foo(int id) {
        this.id = id;
    }
}
```

The compiler copies all instance initializer blocks and field initializers, in the order they appear in the source, into
the start of each constructor - right after the `super(...)` call and before the constuctor's own body.

So for the class above `new Foo(5)`:

1. `super()` runs.
2. Field initializers and instance initializer blocks run, in source order.
3. The body of `Foo(int)` runs.

If the constructor is delegating via `this(...)`, then steps 1, 2 are omitted, because the constructor it delegates to
already did them. This is why such a constructor must not assign a blank final, it would be a second assignment.

Such initializer block is the magic behind:

```java
new HashMap<>() {{ put("a", 1); }}
```

which is rarely used - it creates a subclass per use and holds a reference to the enclosing instance.

# Static

## Runtime polymorphism

Like in C++, when method is static, runtime polymorphism **does not happen**.
This means this code:

```java
class Base {
    public static void show() {
        System.out.println("Base::show() called");
    }
}

class Derived extends Base {
    public static void show() {
        System.out.println("Derived::show() called");
    }
}

class Main {
    public static void main(String[] args) {
        Base b = new Derived();
        b.show();
    }
}
```

results in printing `Base::show() called`.

## Static with null

Calling static methods on objects that are `null` **does not** cause `NullPointerException`. This code compiles and runs
well:

```java
public class Test {
    public static void main(String args[]) {
        Test obj = null;
        obj.staticMethod();
    }

    public static void staticMethod() {
        System.out.println("Hello world!");
    }
}
```
