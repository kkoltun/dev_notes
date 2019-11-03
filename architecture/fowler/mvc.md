# Model View Controller

> Splits user interface interaction into three distinct roles.

## The three roles

**Model:**
* Nonvisual object that represents some information about the domain (data, behavior).
* In most pure OO, it is an object from the *Domain Model*.

**View:**
* Represents the display of the model in the UI.
* It could be a frame full of UI widgets or an HTML page rendered with information from the model.
* All about presentation, any changes to the information are handled by the Controller. 

**Controller:**
* Takes user input, manipulates the model and causes the view to update properly.

## Two principal separations

### Separation of presentation from model

**One of the most fundamental heuristics of good software design.**
**The presentation depends on model, but the model does not depend on presentation.**

1. Presentation and model are about different concerns.
2. This allows developing multiple presentations and yet use the same model code.
3. Presentation changes without altering the model.
4. When there are multiple presentations of the model, usually Observer patterns is useful. 

### Separation of view and controller

This is less important, but valuable to know.
Separating view and controller enables having one view and two controllers as strategies to support for example editable and uneditable mode.
