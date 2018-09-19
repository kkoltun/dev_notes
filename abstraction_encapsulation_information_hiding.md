# Abstraction, Encapsulation, and Information Hiding
By Edward V. Berard
The Object Agency

> A powerful agent is the right word. Whenever we come upon one of those intensely right words in a book or a newspaper the resulting effect is physical as well as spiritual, and electrically prompt.

*Mark Twain (Samuel Langhorne Clemens), Essay on William Dean Howells,1906*

## PROLOGUE
I recently read a magazine article that said, "Encapsulation is just a fancy name for information hiding." Since the writer was non-technical, I just assumed that he was attempting to show that he really did not understand technical matters. However, the passage reminded me of several situations in which other authors -- both technical and non-technical -- had confused encapsulation and information hiding.

Information hiding is not only confused with encapsulation, it is also often confused with abstraction. For example, in a class I was teaching recently, one of the students remarked that my definition of information hiding was remarkably close to my definition of abstraction. Since I had taken both definitions from different sources at different times, I had not thought of comparing them side-by-side. When I did, I was startled at how close the definitions were.

This led to some fanciful speculation on my part. "If encapsulation could be confused with information hiding," I reasoned, "and information hiding could also be confused with abstraction, then could someone argue that abstraction and encapsulation were the same thing?" Of course, when I said it this way, the argument sounded absurd.

Still, I was curious. I decided to gather a number of different definitions for abstraction, information hiding, and encapsulation, and to compare them. This article details what I found.

## ABSTRACTION
> A view of a problem that extracts the essential information relevant to a particular purpose and ignores the remainder of the information.

*IEEE, 1983*

> The essence of abstraction is to extract essential properties while omitting inessential details.

*Ross et al, 1975*

> Abstraction is a process whereby we identify the important aspects of a phenomenon and ignore its details.

*Ghezzi et al, 1991*

> Abstraction is generally defined as *the process of formulating generalised concepts by extracting common qualities from specific examples.*

*Blair et al, 1991*

> Abstraction is the selective examination of certain aspects of a problem. The goal of abstraction is to isolate those aspects that are important for some purpose and suppress those aspects that are unimportant.

*Rumbaugh et al, 1991*

> The meaning [of abstraction] given by the Oxford English Dictionary (OED) closest to the meaning intended here is *The act of separating in thought*. A better definition might be *Representing the essential features of something without including background or inessential detail.*

*Graham, 1991*

> [A] simplified description, or specification, of a system that emphasizes some of the system's details or properties while suppressing others. A good abstraction is one that emphasizes details that are significant to the reader or user and suppress details that are, at least for the moment, immaterial or diversionary.

*Shaw, 1984*

> An abstraction denotes the essential characteristics of an object that distinguish it from all other kinds of object and thus provide crisply defined conceptual boundaries, relative to the perspective of the viewer.

*Booch, 1991*

One point of confusion regarding abstraction is its use as both a process and an entity. Abstraction, as a process, denotes the extracting of the essential details about an item, or a group of items, while ignoring the inessential details. Abstraction, as an entity, denotes a model, a view, or some other focused representation for an actual item. Abstraction is most often used as a complexity mastering technique. For example, we often hear people say such things as: "just give me the highlights" or "just the facts, please." What these people are asking for are abstractions.

We can have varying degrees of abstraction, although these "degrees" are more commonly referred to as "levels." As we move to higher levels of abstraction, we focus on the larger and more important pieces of information (using our chosen selection criteria). Another common observation is that as we move to higher levels of abstraction, we tend to concern ourselves with progressively smaller volumes of information, and fewer overall items. As we move to lower levels of abstraction, we reveal more detail, typically encounter more individual items, and increase the volume of information with which we must deal.

[IEEE, 1983], [Ross et al, 1975], [Ghezzi et al, 1991], [Blair et al, 1991], [Rumbaugh et al, 1991], and [Graham, 1991] all appear to view abstraction as a process. (Note that the [Blair et al, 1991] definition is somewhat different from the others in that it suggests examining a number of "specific examples" -- as opposed to examining a single item.) [Shaw, 1984] and [Booch, 1991] describe abstraction as an entity. Both views are equally valid, and, in fact, necessary.

We also note that there are many different types of abstraction, e.g., functional abstraction, data abstraction, process abstraction, and even object abstraction. (See, for example, the following references: [Alexandridis, 1986], [Guttag, 1977], [Liskov and Guttag, 1986], [Park, 1991], [Shaw, 1984], and [Zimmer, 1985].) Each of the above definitions, because they are general definitions of abstraction, correctly avoids describing which specific categories of information are emphasized or de-emphasized.

Usually, abstraction is not defined in terms of information hiding, e.g., note the use of words such as "ignore" and "extracting." However, we should also note the use of the words "suppress" and "suppressing" in some of the above examples. In short, you might say that abstraction dictates that some information is more important than other information, but (correctly) does not specify a specific mechanism for handling the unimportant information.

## INFORMATION HIDING

> The second decomposition was made using 'information hiding' ... as a criterion. The modules no longer correspond to steps in the processing. ... Every module in the second decomposition is characterized by its knowledge of a design decision which it hides from all others. Its interface or definition was chosen to reveal as little as possible about its inner workings.

*Parnas, 1972b*

> ... the purpose of hiding is to make inaccessible certain details that should not affect other parts of a system.

*Ross et al, 1975*

> ... [I]nformation hiding: a module is characterized by the information it hides from other modules, which are called its clients. The hidden information remains a secret to the client modules.

*Ghezzi et al, 1991*

> [Information hiding is] the principle that users of a software component (such as a class) need to know only the essential details of how to initialize and access the component, and do not need to know the details of the implementation.

*Budd, 1991*

> The technique of encapsulating software design decisions in modules in such a way that the module's interfaces reveal little as possible about the module's inner workings; thus each module is a 'black box' to the other modules in the system.

*IEEE, 1983*

> The process of hiding all the details of an object that do not contribute to its essential characteristics; typically, the structure of an object is hidden, as well as the implementation of its methods. The terms information hiding and encapsulation are usually interchangeable.

*Booch, 1991*

> The principle of information hiding is central. It says that modules are used via their specifications, not their implementations. All information about a module, whether concerning data or function, is encapsulated with it and, unless specifically declared public, hidden from other modules.

*Graham, 1991*

In his classic 1972 article ([Parnas, 1972b]), D.L. Parnas describes two different implementation scenarios for a simple key word in context (KWIC) application. One is decomposed and modularized based on the steps one might take in accomplishing the purpose of the application. (Parnas speculates that this approach would be taken by someone who is basing their design on a flowchart.)

The second (and better) scenario is modularized based on "design decisions." Parnas observes, "We propose instead that one begins with a list of difficult design decisions or design decisions which are likely to change. Each module is then designed to hide such a decision from the others." Like Dijkstra ([Dijkstra, 1968]), Parnas advocates that the details of these difficult and likely-to-change decisions be hidden from the rest of the system. Further, the rest of the system will have access to these design decisions only through well-defined, and (to a large degree) unchanging interfaces. (See also [Parnas, 1972a].)

In truth, both of the scenarios presented by Parnas involve "information hiding." In his first scenario, the hidden information involves the details of the procedural steps necessary to accomplish the application. (By 1971, when Parnas first published his work in a university technical report, programmers had known for almost 20 years of the usefulness of subroutines in mastering complexity.) The second, and (very arguably) superior, scenario requires that the hidden information be the details of difficult and/or likely-to-change design decisions.

"Hiding information," in and of itself, was not new. For that matter, the isolation of difficult and/or likely-to-change design decisions in modules was also not new. (Dijkstra had done this earlier in his implementation of the "THE"-Multiprogramming System.) 

The significance of Parnas's 1972 article on software module specification lay in two areas:

* His avocation and specification of the (then innovative) technique of basing system modularization on design decisions. (You would have to say that the article presented a significantly different view of Dijkstra's "levels of abstraction" approach.)

* His use of the term "information hiding." Virtually every article which mentions the topic traces its origin to [Parnas, 1972b].

Obviously, Parnas did not say all information hiding is good, nor did he say that all information hiding techniques are equally useful. He was identifying a particularly pragmatic approach to information hiding.

Just as with abstraction, there are degrees of information hiding. For example, at the programming language level, C++ provides for public, private, and protected members ([Ellis and Stroustrup, 1990]), and Ada has both private and limited private types ([ARM, 1983]).

We can now identify some of the sources of confusion about the differences between information hiding and abstraction, i.e.:

* Abstraction can be (and often is) used as a technique for identifying which information should be hidden. For example, in functional abstraction we might say that it is important to be able to add items to a list, but the details of how that is accomplished are not of interest and should be hidden. Using data abstraction, we would say that a list is a place where we can store information, but how the list is actually implemented (e.g., as an array or as a series of linked locations) is unimportant and should be hidden.

Confusion can occur when people fail to distinguish between the hiding of information, and a technique (e.g., abstraction) that is used to help identify which information is to be hidden.

* Some of the definitions for abstraction can also be sources of confusion. For example, words like "ignore," "omit," "extract," and "without including" are rather passive, and would not necessarily imply the deliberate hiding of any information, e.g., "the information is there, and accessible, but we just ignore it." However, words like "suppress" and "suppressing" present a somewhat different image -- quite possibly the active and deliberate hiding of information.

Now, let's look at the other definitions for information hiding:

* The [Ross et al, 1975] definition somewhat generalizes Parnas's definition, but still stipulates that the information that should be hidden are those "details that should not affect other parts of a system."

* The [Ghezzi et al, 1991] definition also presents a somewhat generalized view of Parnas's view on information hiding.

* The [Budd, 1991] and [Booch, 1991] definitions are specialized to an object-oriented view of the world.

* Note the use of the words "encapsulating" and "encapsulated" in [IEEE, 1983] and [Graham, 1991] respectively. As we shall see in the next section, there is a significant difference between information hiding and encapsulation. However, some people might attempt to infer incorrectly from the [IEEE, 1983] and [Graham, 1991] definitions for information hiding, that encapsulation and information hiding are the same thing.

## ENCAPSULATION
> 1. to enclose in or as if in a capsule

*Mish, 1988*

> The concept of encapsulation as used in an object-oriented context is not essentially different from its dictionary definition. It still refers to building a capsule, in the case a conceptual barrier, around some collection of things.

*Wirfs-Brock et al, 1990*

> It is a simple, yet reasonable effective, system-building tool. It allows suppliers to present cleanly specified interfaces around the services they provide. A consumer has full visibility to the procedures offered by an object, and no visibility to its data. From a consumer's point of view, and object is a seamless capsule that offers a number of services, with no visibility as to how these services are implemented ... The technical term for this is encapsulation.

*Cox, 1986*

> Encapsulation or equivalently information hiding refers to the practice of including within an object everything it needs, and furthermore doing this in such a way that no other object need ever be aware of this internal structure.

*Graham, 1991*

> We say that the changeable, hidden information becomes the secret of the module; also, according to a widely used jargon, we say that such information is encapsulated within the implementation.

*Ghezzi et al, 1991*

> Data hiding is sometimes called encapsulation because the data and its code are put together in a package or 'capsule.'"

*Smith, 1991*

> Encapsulation is used as a generic term for techniques which realize data abstraction. Encapsulation therefore implies the provision of mechanisms to support both modularity and information hiding. There is therefore a one to one correspondence in this case between the technique of encapsulation and the principle of data abstraction.

*Blair et al, 1991*

> Encapsulation (also information hiding) consists of separating the external aspects of an object which are accessible to other objects, from the internal implementation details of the object, which are hidden from other objects."

*Rumbaugh et al, 1991*

> [E]ncapsulation -- also known as information hiding -- prevents clients from seeing its inside view, were the behavior of the abstraction is implemented."

*Booch, 1991*

Like abstraction, the word "encapsulation" can be used to describe either a process or an entity. As a process, encapsulation means the act of enclosing one or more items within a (physical or logical) container. Encapsulation, as an entity, refers to a package or an enclosure that holds (contains, encloses) one or more items. It is extremely important to note that nothing is said about "the walls of the enclosure." Specifically, they may be "transparent," "translucent," or even "opaque."

Programming languages have long supported encapsulation. For example, subprograms (e.g., procedures, functions, and subroutines), arrays, and record structures are common examples of encapsulation mechanisms supported by most programming languages. Newer programming languages support larger encapsulation mechanisms, e.g., "classes" in Simula ([Birtwistle et al. 1973]), Smalltalk ([Goldberg and Robson, 1983]), and C++, "modules" in Modula ([Wirth, 1983]), and "packages" in Ada.

If encapsulation was "the same thing as information hiding," then one might make the argument that "everything that was encapsulated was also hidden." This is obviously not true. For example, even though information may be encapsulated within record structures and arrays, this information is usually not hidden (unless hidden via some other mechanism).

Another example of encapsulated, but not hidden, information is the (highly undesirable) "block of global information" technique reminiscent of FORTRAN's common blocks. Unfortunately, it is quite easy in some object-oriented languages to create blocks of global data in the form of classes. Specifically, it is possible to create classes with nothing but constants and variables in their public interfaces, i.e., there are no operations in the interface. (For reasons why this is undesirable, see discussions of "module coupling," e.g., [Myers, 1978] and [Yourdon and Constantine, 1979].)

It is indeed true that encapsulation mechanisms such as classes allow some information to be hidden. However, these same encapsulation mechanisms also allow some information to be visible. Some even allow varying degrees of visibility, e.g., C++'s public, protected, and private members.

Even arguing that encapsulation is necessary for information hiding is not as simple as one might suspect. Of course, one could very loosely define encapsulation such that any hidden information is (logically or physically) encapsulated in something.

Examining the cited definitions for encapsulation above, we make the following observations:

* [Wirfs-Brock et al, 1990] comes closest to a simple, straightforward definition for encapsulation.
* Brad Cox's definition ([Cox, 1986]) allows for encapsulation to hide some information ("full visibility to the procedures offered by an object"), while hiding other information ("no visibility to its data").
* Although not as clean as it could be, the definition supplied by [Blair et al, 1991] presents an accurate view of the relationship among abstraction, information hiding, and encapsulation.
* [Ghezzi et al, 1991] at least acknowledges the confusion associated with information hiding and encapsulation, i.e., "widely used jargon."
* [Booch, 1991], [Graham, 1991], [Rumbaugh et al, 1991], and [Smith, 1991] make no (or very little) distinction between "information hiding" and "encapsulation."

## CONCLUSIONS

Abstraction, information hiding, and encapsulation are very different, but highly-related, concepts. One could argue that abstraction is a technique that helps us identify which specific information should be visible, and which information should be hidden. Encapsulation is then the technique for packaging the information in such a way as to hide what should be hidden, and make visible what is intended to be visible.

It is not hard to see how abstraction, information hiding, and encapsulation became confused with one another. Further, one could argue that, regardless of their "dictionary definitions," these terms have evolved new meanings in the context of software engineering, e.g., in much the same way as "paradigm" has. (See, e.g., [Kuhn, 1962].) However, a stronger argument can be made for keeping the concepts, and thus the terms, distinct.

## BIBLIOGRAPHY
[Alexandridis, 1986]. N.A. Alexandridis, "Adaptable Software and Hardware : Problems and Solutions," Computer , Vol. 19, No. 2, February 1986, pp. 29 - 39.

[ARM, 1983]. Reference Manual for the Ada Programming Language, ANSI/MIL-STD 1815A (1983) , United States Department of Defense, February 1983.

[Birtwistle et al. 1973]. G. Birtwistle, O. Dahl, B. Myhrtag and K. Nygaard, Simula Begin, Auerbach Press, Philadelphia, 1973.

[Blair et al, 1991]. G. Blair, J. Gallagher, D. Hutchison, and D. Sheperd, Object-Oriented Languages, Systems and Applications, Halsted Press, New York, New York, 1991.

[Booch, 1991]. G. Booch, Object-Oriented Design With Applications, Benjamin/Cummings, Menlo Park, California, 1991.

[Budd, 1991]. T. Budd, An Introduction to Object-Oriented Programming, Addison-Wesley, Reading, Massachusetts, 1991.

[Cox, 1986]. B.J. Cox, Object Oriented Programming: An Evolutionary Approach, Addison-Wesley, Reading, Massachusetts, 1986.

[Dijkstra, 1968]. E.W. Dijkstra, "Structure of the 'THE'-Multiprogramming System," Communications of the ACM, Vol. 11, No. 5, May 1968, pp. 341-346.

[Ellis and Stroustrup, 1990]. M.A. Ellis and B. Stroustrup, The Annotated C++ Reference Manual, Addison-Wesley, Reading, Massachusetts, 1990.

[Ghezzi et al, 1991]. C. Ghezzi, M. Jazayeri, and D. Mandrioli, Fundamentals of Software Engineering, Prentice-Hall, Englewood Cliffs, New Jersey, 1991.

[Goldberg and Robson, 1983]. A. Goldberg and D. Robson, Smalltalk-80: The Language and Its Implementation, Addison-Wesley, Reading, Massachusetts, 1983.

[Graham, 1991]. I. Graham, Object-Oriented Methods, Addison-Wesley, Reading, Massachusetts, 1991.

[Guttag, 1977]. J. Guttag, "Abstract Data Types and the Development of Data Structures," Communications of the ACM, Vol. 20, No. 6, June 1977, pp. 396 - 404.

[IEEE, 1983]. IEEE, IEEE Standard Glossary of Software Engineering Terminology, The Institute of Electrical and Electronic Engineers, New York,New York, 1983.

[Kuhn, 1962]. T.S. Kuhn, The Structure of Scientific Revolutions, University of Chicago Press, Chicago, Illinois, 1962.

[Liskov and Guttag, 1986]. B. Liskov and J. Guttag, Abstraction and Specification in Program Development, The MIT Press, Cambridge, Massachusetts, 1986.

[Mish, 1988], F.C. Mish, Editor in Chief, Webster's Ninth New Collegiate Dictionary, Merriam-Webster Inc., Springfield, Massachusetts, 1988.

[Myers, 1978]. G.J. Myers, Composite/Structured Design, Van Nostrand Reinhold, New York, New York, 1978.

[Park, 1991]. H.-S. Park, "Abstract Object Types = Abstract Knowledge Types + Abstract Data Types + Abstract Connector Types," Journal of Object-Oriented Programming, Vol. 4, No. 3, June 1991, pp. 37 - 39, 42 - 44, 46 - 48, 51 - 52.

[Parnas, 1971]. D.L. Parnas, Information Distribution Aspects of Design Methodology, Technical Report, Department of Computer Science, Carnegie-Mellon University, February 1971.

[Parnas, 1972a]. D.L. Parnas, "A Technique for Software Module Specification With Examples," Communications of the ACM, Vol. 15, No. 5, May 1972, pp. 330 - 336.

[Parnas, 1972b]. D.L. Parnas, "On the Criteria To Be Used in Decomposing Systems Into Modules," Communications of the ACM, Vol. 5, No. 12, December 1972, pp. 1053-1058.

[Ross et al, 1975]. D.T. Ross, J.B. Goodenough, and C.A. Irvine, "Software Engineering: Process, Principles, and Goals," IEEE Computer, Vol. 8, No. 5, May 1975, pp. 17 - 27.

[Rumbaugh et al, 1991]. J. Rumbaugh, M. Blaha, W. Premerlani, F. Eddy, and W. Lorensen, Object-Oriented Modeling and Design, Prentice-Hall, Englewood Cliffs, New Jersey, 1991.

[Shaw, 1984]. M. Shaw, "Abstraction Techniques in Modern Programming Languages," IEEE Software, Vol. 1, No. 4, October 1984, pp. 10 - 26.

[Smith, 1991]. D.N. Smith, Concepts of Object-Oriented Programming, McGraw-Hill, New York, New York, 1991.

[Wirfs-Brock et al, 1990]. R. Wirfs-Brock, B. Wilkerson, and L. Wiener, Designing Object-Oriented Software, Prentice-Hall, Englewood Cliffs, New Jersey, 1990.

[Wirth, 1983]. N. Wirth, Programming In Modula-2, Second Edition, Springer-Verlag, New York, New York, 1983.

[Yourdon and Constantine, 1979]. E. Yourdon and L.L. Constantine, Structured Design: Fundamentals of a Discipline of Computer Program and Systems Design, Prentice-Hall, Englewood Cliffs, New Jersey, 1979.

[Zimmer, 1985]. J.A. Zimmer, Abstraction for Programmers, McGraw-Hill, New York, New York, 1985.
