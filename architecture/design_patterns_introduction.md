## Design Patterns - introduction

### Why bother

1. Designing reusable object-oriented software is hard. It is virtually impossible to get "right" the first time.
2. Yet, experienced object-oriented designers do make good designs. They often reuse solutions that worked in the past. This experience makes them experts.
3. You will find recurring **patterns of classes and communicating objects** that solve specific design problems. They make the object-oriented design **flexible**, **elegant** and **reusable**.
4. The same works in novel writing, building etc.

### What is a design pattern

Christopher Alexander (describing real architecture patterns):
> Each pattern describes a problem which occurs over and over again in our environment, and then describes the core of the solution to that problem, in such a way that you can use the solution a million times over, without ever doing it the same way twice.

GoF:
> In general, a pattern has four essential elements:
> 1. The **pattern name** is a handle we can use to describe a design problem, its solutions, and consequences in a word or two. [...]
> 2. The **problem** describes when to apply the pattern. It explains the problem and its context. [...]
> 3. The **solution** describes the elements that make up the design, their relationships, responsibilities, and collaborations. [...]
> 4. The **consequences** are the results and trade-offs of applying the pattern. [...]
> 
> [...]
> 
> The design patterns in this book are descriptions of communicating objects and classes that are customized to solve a general design problem in a particular context.


My short definition:
>Design patterns are a form of recording experience in designing object-oriented software that you can use effectively to solve recurring problems.

### Identifying a pattern

*Heavily inspired by the Javaspecialists Desing Patterns course by Heinz Kibutz.*

1. Every design pattern has an intent. Looking at the points above, each DP solves a specific problem in the specific context.
2. Looking at the structure, almost all patterns are similar to the Strategy pattern.
3. **The intent is the most important factor in identifying a design pattern.**
4. You cannot identify the pattern by looking at its structure. You need to know the intent in that particular context.