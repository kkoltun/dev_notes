# Spring IoC Container

## Inversion of Control

**Inversion of Control (IoC) = Dependency Injection (DI)**

IoC is a process in which objects define their dependencies only through constructor arguments, arguments to a factory method or properties that are set on the object instance after it is contructed or returned from a factory method.
The container then injects those dependecies when it creates the bean.

Links:
* [Fowler on IoC Containers](https://www.martinfowler.com/articles/injection.html),
* [Fowler on IoC as a whole](https://martinfowler.com/bliki/InversionOfControl.html)
* [Service locator](https://adamcod.es/2013/11/22/tell-dont-ask.html),
* [Service locator vs IoC](https://adamcod.es/2013/11/25/service-locator-vs-dependency-injection-container.html),
* [Service locator vs IoC 2](http://guy-murphy.github.io/2014/11/24/service-locator-vs-dependency-injection/)

## IoC in Spring

Basic packages for IoC:
* `org.springframework.beans` - BeanFactory provides advenced configuration mechanism capable of managing any type of object.
* `org.springframework.context` - ApplicationContext is a sub-interface of BeanFactory, it ads more enterprise-specific functionality. It is a complete superset of BeanFactory.

## Beans

* objects that form the backbone of the application;
* managed by Spring IoC container;
* **A bean is instantiated, assembled and otherwise managed by a Spring IoC container;**
* container gets its instructions on what objects to instantiate, configure and assemble from configuration metadata;
* configuration metadata is represented in XML, Java annotations or Java code;
* bean metadata and manually supplied singleton instances need to be registered as early as possible, in order for the container to properly reason about them during autowirin and other introspection steps.

### XML configuration

* usually more than one bean elements in beans element;
* every bean element is an actual object that makes up the application;
* usually service layer objects are created, not fine-grained domain objects - creation of these is the responsibility of DAOs and business logic;
* there can be multiple XML configuration files;
* while creating beans, their scope, lifecycle callbacks, dependencies etc. can be set.

### Bean instantiation

* instantiation with a constructor
* instantiation with a static factory method

## Dependencies

Thanks for DI, the object does not look up its dependencies and does not know the location or class of the dependencies.
Classes become easier to test, in particular when the dependencies are on interfaces or abstract base classes (enable stubs, mocks).

### Constructor-based dependency injection

Constructor with a number of arguments, each representing a dependency.
Calling static factory method with specific arguments to construct the bean is nearly equivalent.

If no ambiguity exists, the matching between Java code constructor and xml configuration happens.
Other ways - matching by types, names, etc ([here](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-constructor-injection)).

### Setter-based dependency injection

Container calls setter methods on a bean after invoking a no-argument constructor or no-argument static factory method to instantiate the bean.

### Constructor-based vs setter-based

* It is a good rule of thumb to use constructors for mandatory dependencies and setter methods or configuration methods for optional dependencies.
* Use of @Required annotation on a setter method can be used to make the property a required dependency;

Why use constructor-based:
* enables one to implement application components as immutable objects and to ensure that dependencies are not null;
* components are always returned to client (calling) code in a fully initialized state.

Why use setter-based:
* only for optional dependencies that can be assigned reasonable default values within the class, otherwise not-null checks are required everywhere;
* makes objects of the class amenable to reconfiguration or re-injection later.

### Referencing other beans in bean properties and constructor arguments

This is used in <property/> and <constructor-arg/> elements:
* the <ref/> element value references another bean (a collaborator) managed by the container.
* the referenced bean is a dependency of a bean for which the reference was created and is initialized on demand as needed before the property is set.
* all references all ultimately a reference to another object;
* `bean`, `local` and `parent` attributes are used.

### Autowiring collaborators

Relationships between collaborating beans can be resolved automatically by inspecting `ApplicationContext`. Advantages:
* reduce the need to specify properites or constructor arguments;
* update a configuration as objects evolve.

#### Autowiring modes

Set in `autowire` attribute of the `<bean>` element:

attribute value | meaning
------|------
no | bean references must be defined via a `ref` element. Changing this is not recommended for larger deployments.
byName | look for a bean with the same name as the property that needs to be autowired. Example: bean with *master* property (has a *setMaster(...)* method) -> Spring looks for a bean definition named `master`
byType | property is autowired if exactly one bean of the property type exists in the container. If there are more than one - fatal exception. If ther are none - property is not set.
constructor | analogous to *byType* but applies to constructor arguments.

With `constructor` and `byType` arrays and typed-collections can be wired. Also strongly-typed Maps can be autowired when type is String (?).

To block certain bean from being autowired into the property of other beans `autowire-canditate="false"` should be used.

### Dependency resolution process

1. ApplicationContext is created and initialized with configuration metadata (XML, Java code or annotations).
2. For each bean, its dependecies are expressed in form of properties, construtor arguments or arguments to the static-facotry.
Dependencies are provided to the bean at its creation.
3. Each property or constructor argument is an actual definition of the value to set or a reference to another bean.

* The configuration of each bean is validated on container creation.
* The bean properties are not set until the bean is actually created.

### Bean initialization

#### Pre-instantiation

Beans are created when container is created. This enables fail-fast behavior - configuration issues can be discovered when the ApplicationContext is created, not later.
However, it can be changed, then the bean can throw an exception caused by eg. missing or invalid property pretty late.

#### Lazy initialization

Beans with lazy-init, are not created on container creation, unless they are dependencies of another not lazy-iniialized beans.

## Bean scopes

### Singleton (default) - best for stateless beans

* only one shared instance of a singleton bean is managed;
* default scope of a bean in Spring.

### GoF singleton vs Spring singleton

* GoF: singleton scope is hard-coded such that *one and only one* instance of a particular class is created *per ClassLoader*
* Spring - one and only one per container and per bean. If one bean is defined for a particular class in a single Spring container, then the *one and only one* instance of class defined by that bean definition is created.

### Prototype - best for stateful beans

* creation of a new bean instance every time a request for that specific bean is made;
* request is made = bean is injected into another bean or you request it through a `getBean()` method call on container;
* after instantiation, configuration and assemby of a prototype object, it is handed to the client (there will be *initialization* callbacks but no *destruction* callbacks). The client code must clean up prototype-scoped objects and release expensive resources that the prototype bean(s) are holding.
* the role of Spring container here is like a replacement for the Java `new` operator.
* configuration model
* dependency injection mechanism
