### Design patterns quiz questions

**The most important part of the pattern is the intent.**

---

#### 1. UML (Unified Modeling Language)

*UML is good to describe class structures. However, it becomes less usable with larger architectures (n class diagrams are not readable).*

[Additional information on the merononmy and relationships.](https://stackoverflow.com/questions/885937/what-is-the-difference-between-association-aggregation-and-composition/34069760#34069760)

[Robert Martin on examples of association, aggregation, composition.](https://groups.google.com/g/comp.object/c/_j4g-I9jqVg/m/rouCJeVXzR4J)

[UML Class diagram reference](https://web.archive.org/web/20070103141438/http://www.objectmentor.com/resources/articles/umlClassDiagrams.pdf)

How to describe in UML:
1. Method with an argument and a returned type
2. *implements* relationship
3. *extends* relationship
4. public, private, protected, package-private fields
5. static fields or methods
6. abstract methods
7. direction and multiplicity
8. dependency
9. association
10. aggregation
11. composition

---

#### 2. Meronomy

[Meronomy definition](https://en.wikipedia.org/wiki/Meronomy)

1. What is a meronomy?
2. What are the three requirements of the merononmy?
3. List 4 relationships, 2 non-meronomy, 2 meronony, what are the differences between them?
4. Where meronomy and ownership matters?

---

#### 3. Intrinsic vs extrinsic state

*Sometimes it is really important to choose between storing a pointer to an object and passing it to the method when it is used.* 

1. How to calculate an object size basing on the class layout?
2. What is CompressedOops?
3. Give an example of how extrinsic vs intrinsic state choice can affect the memory usage (with numbers).

---

#### 4. Abstract class

[Definition and explanation by Bobby Woolf.](https://web.archive.org/web/20221015195647/https://www.javaspecialists.eu/courses/dpc/archive/AbstractClass-Woolf.pdf)

1. What is the intent?
2. What is the UML diagram?
3. What are example usages in JDK, libraries?
4. When this pattern should be used (3 cases)?
5. What are the advantages of using it (2 examples)?
6. What are the drawbacks of using it (3 examples)?
7. What are the implementation hints for this pattern?
8. What should be minimized? What is intentionally shared (behavior vs state)? Why?
9. Where is the common behavior, where is the specific one?
10. What SOLID can be broken in particular when Abstract Class is incorrectly implemented?

---

#### 5. Builder

[Builder in the Refactoring Guru site (Alexander Shvets)](https://refactoring.guru/design-patterns/builder)

1. What is the intent?
2. What is the UML diagram? Describe the roles in the diagram.
3. What are the example usages in JDK, libraries?
4. When this pattern should be used (3 cases)? What major language limitation is avoided?
5. What are the advantages of using it (3 examples)?
6. What is the general disadvantage of using it?
7. What are the implementation hints for this pattern?
8. What is special about this pattern in the group of creational patterns?
9. Who returns the result of the creation? This depends on...?
10. What is a "Simple Builder" pattern referenced in Effective Java, how it is different from the Builder pattern? What is the intent of that one?
11. What SOLID principle is expressed here in particular?

---

#### 6. Essence

[Essence by Andy Carlson.](https://web.archive.org/web/20221016192230/https://www.javaspecialists.eu/courses/dpc/archive/Essence-Carlson.pdf)

1. What is the intent?
2. What is the UML diagram? Describe the roles in the diagram.
3. When can validation be done? What can be done with the constructor of the Target class?
4. When this pattern should be used (3 cases)? What major language limitation is avoided?
5. What is the flow of the actions in this pattern (see the PDF above)?

---

#### 7. Memento

[Memento in the Refactoring Guru site (Alexander Shvets)](https://refactoring.guru/design-patterns/memento)

1. What is the intent?
2. What is the UML diagram? Describe the roles in the diagram.
3. What is the flow diagram?
4. What is an important implementation detail of the Memento class to avoid memory leaks?
5. When this pattern should be used (2 cases)? What is not exposed here (this is special feature of the pattern)?
6. What are the advantages of using it (2 examples)?
7. What are the disadvantages of using it (2 examples)?
8. Sometimes you need to verify that the right memento is set in the right source object. The memento needs to store the source. How to achieve this without leaking the memory in Java?

---

#### 8. Proxy

[Proxy in the Refactoring Guru site (Alexander Shvets)](https://refactoring.guru/design-patterns/proxy)

[Static proxy generation in Java Part 1](https://www.javaspecialists.eu/archive/Issue180-Generating-Static-Proxy-Classes---Part-1.html)
and [Part 2](https://www.javaspecialists.eu/archive/Issue181-Generating-Static-Proxy-Classes---Part-2.html)

1. What is the intent?
2. What is the UML diagram? Describe the roles in the diagram.
3. When this pattern should be used (5 cases)?
4. What are two important consequences of the Proxy usage?
5. What about equals()? What are its general requirements which can be hard to achieve here?
6. What are two ways of modern Proxy implementation in Java?
7. What SOLID principle is expressed here in particular?
8. What is the relationship between the Service and the ServiceProxy in terms of their lifecycles?

---

#### 9. Flyweight

[Proxy in the Refactoring Guru site (Alexander Shvets)](https://refactoring.guru/design-patterns/flyweight)

1. What is the intent?
2. UML diagrams:
   1. (GoF) What is the UML diagram with two types of Flyweight objects? Describe the roles in the diagram.
   2. (refactoring.guru) What is the UML diagram with a shared and unshared part of the Flyweight? Describe the roles in the diagram.
3. What are the case to use this pattern (5 requirements)?
4. What is the general requirement for the Flyweight objects?
5. What is the Java mechanism that could be used to create the Flyweight instances? What was introduced in Java 9 and is a better choice here? :-)
6. What are flyweight examples from the JDK (at least three examples, two more obvious, one less)?

---

### 10. Strategy

1. What is the intent?
2. What is the UML diagram? Describe the roles in the diagram.
3. What are two approaches to the state in the strategy?
4. What are the consequences of using the pattern (3 positive, 3 negative)?
