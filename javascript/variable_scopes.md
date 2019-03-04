# JavaScript variable scopes

## Global scope

**Variables can be accessed and modified anywhere in the code (almost).**

Declaring:
1. Using `var` outside any function. (**not recommended**)

This way, a variable becomes a property of the global `window` object.

```javascript
var name = 'Franz Kafka'; // global variable

function printName() {
  console.log(name);
}

printName(); // Franz Kafka
console.log(
```

2. As a part of a global object. (**more recommended**)

Using global namespace for variables can result in unexpected bugs. 
It is a good idea to namespace these variables so that they bocome properties of a global object.

```javascript
var app = {}; // a global object
app.name = 'Homer';
app.surname = 'Simpson';

function printNames() {
  console.log("App name is " + app.name + " " + app.surname + ".");
}

printNames(); // App name is Homer Simpson.
```

3. In NodeJS using global namespace object.

In NodeJS top-level scope is not the same as the global scope. 
Using `var foo` in a NodeJS module makes the variable local to that module.

To define global variable in NodeJS use global namespace object - `global`.

```javascript
global.foobar = 'Hello World!'; // this is global variable in NodeJS
```

4. Without any keywords. (**not recommended**)

**If you do not declare a variable using one of keywords: `var`, `let` or `const`, the variable is given global scope.**

```javascript
function setGlobalName() {
  globalName = "Joergen Klopp";
}

setGlobalName();
console.log(globalName); // Joergen Klopp
console.log(window.globalName); // Joergen Klopp
```

## Local scope

**Variables declared within a function are scoped locally to that function.**

```javascript
var globalName = "Superman";

function foo(name) {
  // name is scoped locally to function foo
  console.log(name);
}

function bar() {
  var barName = "Spiderman";
  console.log(barName);
}
foo(globalName); // Superman
bar(); // Spiderman
console.log(barName); // error!
```

### Hoisting with `var`

**When using `var` JavaScript initiates the variable at the top of the current scope, regardless of the original poisition of declaration.** **This is called hoisting.**

This way this code:
```javascript
var name = 'Tom';

function foo() {
  if (name === undefined) {
    var name = 'Jerry';
  }
  console.log(name); // Jerry
}
foo();
```
is equivalent to this code:
```javascript
var name = 'Tom';

function foo() {
  var name;
  if (name === undefined) {
    name = 'Jerry';
  }
  console.log(name); // Jerry
}
foo();
```

## Block scope

**Both `let` and `const` allow to scope to a block of code - anything between two curly braces `{` and `}`.**

* **Locally scoped variable: `var`**
* **Block scoped variable: `let` or `const`**

The block scoping of `let` and `const` includes conditional blocks and loops:
```javascript
for (let i = 0; i < 5; i++) {
  console.log(i); // 0 1 2 3 4
}

console.log(i); // error!
```

Whereas local scoping of `let`:
```javascript
for (var i = 0; i < 5; i++) {
  console.log(i);
}

console.log("From outside: " + i); // From outside: 5
```

### Hoisting with `let` and `const`

In case of `let` and `const` hoisting happens as with `var` but the variable remains uninitiated and exist in *temporal dead zone*.

* **Hoisting with initating to `undefined`: `var`**
* **Hoisting without initiating: `let` and `const`**

```javascript
var name = 'Tom';

function foo() {
  if (name === undefined) {
    let name = 'Jerry';
  }
  console.log(name); // Tom
}
foo();
```

This way trying to early-access variable defined with `var` and with `let` differs significantly:
```javascript
function getTooEarly() {
  console.log(varName); // undefined
  console.log(letName); // error!
  var varName = 'Harry Kane';
  let letName = 'Johan Cruyff';
}
getTooEarly();
```

### Global scope with `let`

Using `let` in a global scope **does not** result in adding the variable to `window` object.

```javascript
var vName = 'Alex Ferguson';
let lName = 'Jose Mourihno';

console.log(window.vName); // Alex Ferguson
console.log(window.lName); // Jose Mourihno
```

### Constness of `const`

**Variables defined by `const` cannot be changed through re-assignment. However, the contents of the object can be changed.**
```javascript
const array = ['David', 'Tom'];
array.pop();
array.push('Carol');
console.log(array); // (2) ["David", "Carol"]

array = ['George', 'Tim'] // error!
```

### Making an object immutable `Object.freeze()`

**To make the object immutable, use `Object.freeze()`.**

For arrays this will prevent from altering, adding and removing elements.
```javascript
const array = ['David', 'Tom'];
array.pop();
array.push('Carol');
console.log(array); // (2) ["David", "Carol"]

array.freeze();
array.push('Xavier'); // error!
```

The values that are objects can still be modified, unless they are also frozen.
```javascript
class Car {
  constructor(driver) {
    this.driver = driver;
  }
}

class Driver {
  constructor(name) {
    this.name = name;
  }
}

let tom = new Driver('Tom');
const car = new Car(tom);
console.log(car.driver.name); // Tom

let ann = new Driver('Ann');
car.driver = ann;
console.log(car.driver.name); // Ann 

Object.freeze(car);
car.driver = tom; // modification is disallowed silently
console.log(car.driver.name); // Ann

car.driver.name = "Mary";
console.log(car.driver.name); // Mary
```

Note that any attempt to add or remove properties set of a frozen object **will fail silently or by throwing an error.**

