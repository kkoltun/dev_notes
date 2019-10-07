# Final

## Final class

A final class cannot be subclassed. Many classes in Java are final - `java.lang.System`, `java.lang.String`. This has security and efficiency benefits.

## Final methods

A final method cannot be overriden or hidden by subclasses.
This is usually used to prevent unexpected behavior from a subclass altering a method that may be crucial to the function or consistency of the class.

## Final variables

A final variable can only be initialized once, either via an initializer or an assignment statement. 

If a variable is a reference:
* the variable cannot be re-bound to reference another object;
* the object it references is **still mutable**, if it was originally mutable.

Inside a class:
* a final variable has to be definitely assigned in every constructor of the class in which it is declared;
* a static final variable has to be definitely assigned in a static initializer of the class in which it is declared.

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

Calling static methods on objects that are `null` **does not** cause `NullPointerException`. This code compiles and runs well:
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
