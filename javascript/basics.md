# Javascript

## Objects

### Methods

* methods are nothing more than properties that hold function values;
* methods have access to `this`;

### Prototypes

* in addition to the set of properties, most objects also have a `prototype`;
* a prototype is another object that is used as a fallback source of properties;
* when an object gets a request for a property that is does not have, its prototype will be searched for the property, then the prototype's prototype, and so on;
* the prototype relations of JavaScript objects form a tree-shaped structure and at the root of this structure sits `Object.prototype`;
* the prototype object acts as a container for the properties that are shared by all objects that derive from it.

Prototypes:
* functions derive from `Function.prototype`;
* arrays derive from `Array.prototype`.

To create an object with specified prototype, use `Object.create`.

### Classes
JavaScript's prototype system can be interpreted as a somewhat informal take on an object-oriented concept called *classes*.

* prototypes are useful for defining properties for which all instances of a class share the same value, such as methods;
* properties which differ per instance need to be stored directly in the objects themselves.

#### Constructor

##### Creating objects - old and new way

Lets say we have a following prototype:
```javascript
let protoRabbit = {
  speak(line) {
    console.log(`The ${this.type} rabbit says '${line}'`);
  }
}
```

A first, straightforward approach to making a constructor may be the following:
```javascript
function makeRabbit(type) {
  let rabbit = Object.create(protoRabbit);
  rabbit.type = type;
  return rabbit;
}
```

JavaScript provides a keyword for this - `new`:
* if you put the keyword `new` in front of a function call, the function is treated as a constructor;
* object with the right prototype is automatically created, bound to `this` in the function and returned at the end of the function.

```javascript
function Rabbit(type) {
  this.type = type;
}
Rabbit.prototype.speak = function(line) {
  console.log(`The ${this.type} rabbit says '${line}'`);
};

let weirdRabbit = new Rabbit("weird");
```

What is the difference between functions `makeRabbit(type)` and `Rabbit(type)`?

##### Difference between functions and constructors

ECMAScript 6+ distinguishes between *callable* and *constructable* functions:
* *callable* functions can be called without `new`;
* *constructable* functions can be called with `new`.

The following functions are *not constructable*:
* functions created via the arrow function;
* method definitions in classes;
* object literals.

Functions created via `class` syntax are *not callable*.

Functions created in any other way - function expression/declaration, `Function` constructor) are *callable* and *constructable*.

Built-in functions are *not constructable* unless explicitly stated otherwise.

#### Class notation

Generally speaking, JavaScript classes are constructor functions with a prototype property.

After 2015, there is a new notation for writing classes in JavaScript.

```javascript
class Rabbit {
  constructor(type) {
    this.type = type;
  }

  speak(line) {
    console.log(`The ${this.type} rabbit says '${line}'`);
  }
}

let killerRabbit = new Rabbit("killer");
let blackRabbit = new Rabbit("black");
```

Keyword `class`:
* starts a class declaraction which allows constructor and methods definition;
* the `constructor` method provides constructor function, which will be bound to the name `Rabbit`;
* functions inside the class definitions are methods - properties that hold functions;
* all things apart from `constructor` are packaged into constructor's prototype.


### Maps

A `map` is a data structure that associates values (the keys) with other values.

#### Using objects as maps

It is possible to use objects for this matter.

```javascript
let ages = {
  Boris: 39,
  Julia: 22,
  Ola: 29
};
```

This way:
* object's property names are the people's names;
* object's property values are their ages.

There is a pitfall here - we did not list anybody named `toString` in our map. Yet because plain objects derive from `Object.prototype`, it looks like the property is there.

#### Using objects without a prototype as maps

It is possible to create objects with *no* prototype - by passing `null` to `Object.create`.

#### Using Map objects

Object property names must be strings, if you need a map whose key's can't be easily converted to string use `Map` class:
```javascript
let ages = new Map();
ages.set("Boris", 39);
ages.set("Julia, 22);
ages.set("Ola", 29);
```

### Symbols

Property names can be strings or *symbols*. 

Symbols are:
* values creates with the `Symbol` function;
* unlike strings, newly created symbols are unique.

This way you can add a new property to a class which lives alongside other properties, no matter what the names are:
```javascript
const toStringSymbol = Symbol("toString");
Array.prototype[toStringSymbol] = function() {
  return `This array is about ${this.length} meters long.`;
};

console.log([1, 2].toString());
console.log([1, 2][toStringSymbol]());
```

### The iterator interface

There is a `Symbol.iterator` symbol which is a symbol value defined by the language and stored as a property of the `Symbol` function. 

To be *iterable*, an object must have a method named with it, which returns an object providing an *iterator* interface, which in turn:
* has a `next` method which returns next result - an object wit a `value` property;
* has a `done`property which should be true when there are no more results and false otherwise.


