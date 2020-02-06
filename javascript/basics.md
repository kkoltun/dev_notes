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

Constructors are functions:
* that can be used with the `new` operator to create new objects;
* whose names usually start with a capital letter.

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

**The `class` notation provides a clear way to define a constructor and its prototype.**

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
* starts a class declaration which allows constructor and methods definition;
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
ages.set("Julia", 22);
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

### Getters, setters and statics

Interfaces may include properties that hold non-function values (such as `size` for `Map` objects).
Accessing and setting properties can be set with keywords `get` for *getters* and `set` for *setters*.

```javascript
class Temperature {
  constructor(celsius) {
    this.celsius = celsius;
  }
  get fahrenheit() {
    return this.celsius * 1.8 + 32;
  }
  set fahrenheit(value) {
    this.celsius = (value - 32) / 1.8;
  }
  static fromFahrenheit(value) {
    return new Temperature((value - 32) / 1.8);
  }
}

let temp = new Temperature(22);
console.log(temp.fahrenheit); // 71.6
temp.fahrenheit = 86;
console.log(temp.celsius); // 30
```

**Non-static properties are attached to the prototype. Static properties are attached to the constructor function.**

### Inheritance

In JavaScript inheritance is introduced by `extends` keyword.
This indicates that this class shouldn't be directly based on the default `Object` prototype but on some other class.

```javascript
class SymmetricMatrix extends Matrix {
  constructor(size, element = (x, y) => undefined) {
    super(size, size, (x, y) => {
      // swap the coordinates for values below the diagonal
      if (x < y) return element(y, x);
      else return element(x, y);
    });
  }

  set(x, y, value) {
    super.set(x, y, value);
    if (x != y) {
      super.set(y, x, value);
    }
  }
}
```

Here:
* `SymmetricMatrix` will be based on `Matrix`, not `Object` which is default;
* `SymmetricMatrix` is the subclass, `Matrix` is the superclass;
* `super` is used to call the methods already defined in the superclass.

## Bugs and errors

### Strict mode

**Strict mode** makes JavaScript a little bit stricter:
1. JavaScript does not allow omitting `let` in front of the binding. Normally, if allowed this would create a global binding.
2. There is no `with` statement.
3. Giving a function multiple parameters with the same name is prohibited.

## Regular expressions

Ways to create a `RegExp` object:
```javascript
let re1 = new RegExp("abc")
let re2 = /abc/;
let eighteenPlus = /eighteen\+/;
```

### Testing for matches

**The `test` method:**

```javascript
console.log(/abc/.test("abcde"));
// true
```

### Getting matches and groups

**The `exec` method:**

```javascript
let match = /\d+/.exec("one two 100");
console.log(match);
// ["100"]
console.log(match.index);
// 8
```

The array returned by `exec` method has the whole match in the first element and then parts matched by groups:
1. If a group ends up not being matched at all, its position in the output array will hold `undefined`.
2. If a group is matched multiple times, only the last match ends up in the array.

```javascript
let quotedText = /'([^']*)'/;
console.log(quotedText.exec("she said 'hello'"));
// ["'hello'", "hello"]

console.log(/bad(ly)?/.exec("bad"));
// ["bad", undefined]
console.log(/(\d)+/.exec("123"));
// ["123", "3"]
```

**Example usage - parsing a mm-DD-yyy date:**
```javascript
function getDate(string) {
    let [_, month, day, year] = 
      /(\d{1,2})-(\d{1,2})-(\d{4})/.exec(string);

    return new Date(year, month - 1, day); // months start at 0
}

console.log(getDate("1-30-2003"));
// Thu Jan 30 2003 00:00:00 GMT+0100 (CET)
```

### The Date class

**Months start at zero (December is 11); days start at one.**

### The replace method

**Simply replacing using regex:**

```javascript
console.log("Borobudur".replace(/[ou]/, "a"));
// Barobudur - only first match replaced

console.log("Borobudur".replace(/[ou]/g, "a"));
// Barabadar - all matches replaced
```

**Replacing using groups:**

```javascript
console.log(
  "Liskov, Barbara\nMcCarthy, John\nWadler, Philip"
    .replace(/(\w+), (\w+)\g, "$2 $1"));
// Barbara Liskov
  John McCarthy
  Philip Wadler
```

**Passing function to replace:**

```javascript
let s = "the cia and fbi"
console.log(s.replace(/\b(fbi|cia)\b/g,
  str => str.toUpperCase()));
// the CIA and FBI
```

### Backtracing

Expression `/\b([01]+b|[\da-f]+h|\d+)\b/ matches either:
* a binary number followed by a `b`;
* a hexadecimal number followed by an `h`;
* a regular decimal number with no suffix character.

The three choices in divided by the `or` operators are three branches the mechanism can enter.
Taking a string "103" the mechanism:
1. Saves its current position before entering the branch (in this case the start of the string).
2. Tries the first branch and after encountering the 3 character, it goes back to the saved position - **backtracks**.
3. Tries the second branch and finds out that there is no `h` after the number.
4. Tries the thidr branch and this one fits.

This means that if multiple branches could potentially match a string, only the first one is used (ordered by where the branches appear in regular expression).


For pattern `/^.*x/` against "abcxe"
1. The `.*` part will first try to consume the whole string (**greed**).
2. The matcher realises it needs `x` to match the pattern.
3. There is no `x` past the end of the string, so the start operator tries to match one character less.
4. The matcher backtracks until the star operator matches `abc` and now, the x is found in the right place.
5. Successful match is returned from positions 0 to 4.

### Greed

The repetition operators - `+`, `*`, `?` and `{}` match as much as they can and backtrack from there - they are **greedy**. 

**To make repetition operator non-greedy, place a question mark after it.** This makes the operator match as little as possible, matching more only when the remaining pattern does not fit the smaller match.

* Greedy operators: `+`, `*`, `?` and `{}`.
* Non-greedy operators: `+?`, `*?`, `??`, `{}?`.

```javascript
let endedWithX_greedy = /^.*X/;

console.log(endedWithX_greedy.exec("abcXdeXf"));
// abcXdeX

let endedWithX_nongreedy = /^.*?X/;

console.log(endedWithX_nongreedy.exec("abcXdeXf"));
// abcX
```

**When using a repetition operator, consider using the nongreedy variant first.**

## Packages

A package:
* can be copied and installed;
* may contain one or more modules and has information about which other packages it depends on;
* usually comes with documentation explaining what it does.

In JavaScript the repository is provided by (NPM)[npmjs.org].

### Improvised isolation

There is a way to achieve a certain degree of isolation:

```javascript
const weekDay = function() {
  const names = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]

  return {
    name(number) { return names[number]; },
    number(name) { return names.indexOf(name); }
  };
}();

console.log(weekDay.name(weekDay.number("Sunday")));
// Sunday
```

This way:
* local binding `names` is hidden inside scope of a function expression;
* the interface is put into the global scope and expects dependencies to do the same (**no dependencies are declared**).

This is mostly obsolete now, but until 2005 this was the only way to improvise modularity.

### Evaluating data as code

Taking the data as a string and executing it is a crucial feature in order to achieve modularity.

First possibility is using `eval` - this will execute a string **in the current scope**:

```javascript
const x = 1;
function evalAndReturnX(code) {
  eval(code);
  return x;
}

console.log(evalAndReturnX("var x = 2"));
// 2
console.log(evalAndReturnX("var y = 3"));
// 1
console.log(x);
// 1
```

This is usually a bad idea because it reduces the predictability which binding a given name refers to.

Instead of executing in the current scope, we need to wrap the module's code in a function and **use that function's scope as module scope**.
This can be done with `Function` constructor:

```javascript
let plusOne = Function("n", "return n + 1;");
console.log(plusOne(4));
// 5
```

The arguments passed to the constructor re:
* string containing a comma-separated list of argument names;
* string containing the function body.

### CommonJS

CommonJS is a most widely used modules solution. It is used by Node.js and most packages on NPM.
**The main concept of CommonJS are two functions - `require` and `export`.** This ensures that:
* when you call `require` with the dependency name, the module is loaded and the function returns its interface;
* modules get automatically their own scope, as the loader wraps the module code in a function;
* modules who want to expose their interface, put it in the object bound to `exports`.

```javascript
const ordinal = require("ordinal");
const {days as dayNames, months} = require("date-names")

exports.formatDate = function(date, format) { /* ... */ }
```

In the example, the imported interfaces:
* `ordinal` is a single function;
* `date-names` exports an object containing multiple things - `days` and `months` are arrays of names.

### ECMAScript modules

**The main concept of ECMAScript modules are two keywords - `import` and `export`.** This is a notation built in the language. 

In this feature:
* When you import from another module, **you import the binding, not the value**.
This mean the exporting module may change the value of the binding, and the importing modules will see the new value.
* The import without curly braces (`ordinal` in the example) imports the `default` binding. Alongside the `default` binding, other ones can be exported. By a module.
* Renaming imported bindings is possible with `as`.

```javascript
import ordinal from "ordinal";
import {days, months} from "date-names";

export function formatDate(date, format) { /* ... */ }
```

**The main difference between CommonJS and ECMAScript modules is that ES module imports happen before a module's script starts running.**

## Asynchronous programming

### Callbacks

**Callback is a function called when a chosen process finishes.**

Examples of callbacks:
```javascript
setTimeout(() => console.log("Tick"), 500);

tomMailbox.send("jane", "letter", "Meet me at 7 PM",
  () => console.log("Letter delivered"));
```

### Promises

**A promise is an asynchronous action that mey complete at some point and produce a value.**
**It is able to notify anyone who is interested when its value is available.**

Creating a promise: `Promise.resolve`;
* registering a callback: `promiseObject.then()`.

Note that multiple callbacks can be assigned to a single promise and they will be executed even if they are added after the promise has already *resolved*.

**The `then` method returns another promise which either:
* resolves to the value that the handler function returns;
* or returns a promise, waits for that promise and ther resolves its result.

Example of simple usage of a `Promise`:

```javascript
let fifteen = Promise.resolve(15);
fifteen.then(value => console.log(`Got ${value}`));
// Got 15
```
Example of creating a promise-based interface:

```javascript
function storage(disk, name) {
  return new Promise(resolve => {
    disk.readStorage(name, result => resolve(result));
  });
}

storage(mainDisk, "signal")
  .then(value => console.log("Got", value));
```

### Handling failures

a 
