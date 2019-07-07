# CSS basics

## Box model

Facts:
* Every element is comprised of one or more rectangular boxes;
* The box model describes how the elements are laid out on the page;
* Setting the `height` and `width` of the element sets only the width and height of the content area inside the element;

![box model](./image/box_model.svg)

The acutal area is created by the following dimensions:
```
total-width = width + padding-left + padding-right + border-left + border-right + margin-left + margin-right
total-height = height + padding-top + padding-bottom + border-top + border-bottom + margin-top + margin-bottom
```

**Margin**:
* outside the border of the element;
* does not have a `background-color`, totally transparent.

**Border**:
* space between margin and padding;
* can have different styles and colors;
* the size of the border could have impact on the outer elements.

**Padding**:
* separates the border of the element from the content;
* does have a `background-color`.

**Outline**:
* line drawn outside the border edge to make the element stand out;
* does not take space which means it could overlap with other elements;
* the size of the outline does not have impact on the outer elements;
* could be non-rectangular.

## Layout of the boxes

The following factors matter when rendering the boxes:
* box dimensions;
* element type - **block** or **inline**;
* positioning scheme - **static**, **relative**, **absolute**, **fixed**;
* relationships between the elements in the document tree;
* external information - eg. viewport size, built-in dimensions of images, etc.

### Element types

Two major element types can be distinguished.

**Block-level elements**:
* formatted visually as blocks, take up the full width available with a line break before and after;
* elements: `<p>`, `<div>`, `<h1` to `<h6>`, etc.;
* may contain inline or block-level elements.

**Inline-level elements**:
* do not form new blocks of content; the content is distributed in lines;
* take up as much width as necessary, do not force line breaks;
* elements: `<em>`, `<strong>`, `<span>`, etc.;
* may contain other inline elements.

**Changing the display of the element with `display` property**:
* `display: block` makes the inline element display as a block element;
* `display: inline` makes the block element display as an inline element;
* `display: inline-block` makes the element display as an inline element but with height and width available.

### Positioning scheme

**Static**:
* positioning according to the normal flow of the page;
* properties `top`, `bottom`, `left`, `right` do not affect the position of the element.

**Relative**:
* positioning relative to the normal position of the element;
* properties `top`, `bottom`, `left`, `right` move the element away from its normal position;
* the element may overlap other elements, but the space originally reserved for it in the normal flow is kept.

**Absoulute**:
* positioning relative to the first parent element which has position other than static;
* if no such element is found, the positioning is relative to top-left corner of the viewport (slight simplification);
* the element is taken out of the normal flow and takes no space when placing sibling elements.

**Fixed**:
* a subcategory of the absolute positioning;
* the element is fixed to the viewport and does not move when the page is scrolled.

