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

