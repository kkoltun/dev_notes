# Stream parallel() method

`.parallelStream()` (or `.parallel()`) splits the source into chunks, runs them on the JVM-wide common `ForkJoinPool`
(about one thread per core) and merges the results. Splitting and merging have a fixed cost, so it pays off only when
the work is large enough to cover it.

A parallel stream is faster with:

* A lot of data.
* Real CPU work per element, for example hashing a million passwords.
* A source that splits cheaply: `ArrayList`, arrays, `IntStream.range`.

A parallel stream is slower with:

* Small or cheap work, for example summing 1,000 ints: the fixed cost of splitting and merging is larger than the
  work.
* A source that splits badly: `LinkedList`, `Stream.iterate`, lines of a file. To split these, the stream has to walk
  the elements one by one.
* Order-dependent steps such as `limit` or `findFirst`.
* Blocking I/O: it stalls the common `ForkJoinPool`, which the whole JVM shares. Running the stream inside your own
  `ForkJoinPool` works around it, but only through an undocumented implementation detail.

A parallel stream is wrong with:

* Side effects on shared state, such as `.forEach(list::add)` into an `ArrayList`: elements are lost. `collect(...)`
  merges the per-thread results safely.

In a Spring backend it rarely fits: the work there is mostly I/O, and requests already run in parallel.
