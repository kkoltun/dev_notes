# Lambdas and streams - TODO

## Method reference vs lambda

### Handling nulls

This code will print both messages:
```java
public class LambdaWithNull {
    public static void main(String[] args) {
        class Car {
            void drive() {
                System.out.println("driving");
            }
        }

        Car car = null;

        System.out.println("Creating runnable");
        Runnable carRunnable = () -> car.drive();

        System.out.println("Running runnable");
        carRunnable.run();
    }
}
```

This code will fail on the runnable creation:
```java
public class MethodReferenceWithNull {
    public static void main(String[] args) {
        class Car {
            void drive() {
                System.out.println("driving");
            }
        }

        Car car = null;

        System.out.println("Creating runnable");
        Runnable carRunnable = car::drive;

        System.out.println("Running runnable");
        carRunnable.run();
    }
}
```

Materials:
* [Lambdas and streams course](https://blogs.oracle.com/thejavatutorials/jdk-8-massive-open-and-online-course:-lambdas-and-streams-introduction)
* [Get a Taste of Lambdas and Get Addicted to Streams by Venkat Subramaniam](https://www.youtube.com/watch?v=1OpAgZvYXLQ)
* [Design patterns in Lambdas by Subramaniam](https://www.youtube.com/watch?v=e4MT_OguDKg)
