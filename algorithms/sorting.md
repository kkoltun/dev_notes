# Sorting algorithms

## Glossary:

* **the algorithm sorts in place**: the algorithm rearranges the elements within the input array, with at most a constant number of them stored outside the array at any time;

## Insertion sort

Features:
* **O(n^2) worst-case running time**;
* **sorts in place**;
* good for sorting a small number of elements;
* works the way many people sort a hand of playing cards.

Steps:
1. Start with empty target array.
2. Remove one element at a time from input.
3. Find a correct position for the element by comparing it with each of the elements already in target.
4. Insert the element at the chosen position.

Pseudocode:
```
for j = 2 to A.length
  key = A[j]
  // Insert A[j] into the sorted sequence A[i..j-1]
  i = j - 1
  while i > 0 and A[i] > key
    A[i+1] = A[i]
    i = i - 1
  A[i+1] = key
```

## Merge sort

Features:
* **0(n lg(n)) worst-case running time**;
* **does not sort in place**;
* good example of divide-and-conquer approach;
* main procedure is the `MERGE` step, O(n) worst-case running time;
* whole algorithm is a combination of itself called recursively and `MERGE` step.

Steps:
1. Divide the input array to be sorted into two subarrays of n/2 elements each.
2. Sort the two subarrays recursively using merge sort.
3. Merge the two sorted subsequences to produce the sorted answer.

Pseudocode for the `MERGE` step (p, q, r are idices such that p <= q < r):
```
MERGE(A, p, q, r)
    n1 = q - p + 1
    n2 = r - q
    let L[1..n1 + 1] and R[1..n2 + 1] be new arrays

    for i = 1 to n1
        L[i] = A[p + i - 1]

    for j = 1 to n2
        R[j] = A[q + j]

    L[n1 + 1] = inf
    R[n2 + 1] = inf

    for k = p to r
        if L[i] =< R[j]
            A[k] = L[i]
            i = i + 1
        else
            A[k] = R[j]
            j = j + 1
```

Pseudocode for the `MERGE_SORT` which sorts the elements in the subarray `A[p..r]` (if p >= r the subarray has at most one lement and is therefore already sorted):
```
MERGE_SORT(A, p, r)
    if p < r
        q = (p + r)/2

        MERGE_SORT(A, p, q)
        MERGE_SORT(A, q + 1, R)
        MERGE(A, p, q, r)
```

## Heap sort

### Heaps

Features:
* aray object that can be viewed as nearly complete binary tree;
* each node of the tree corresponds to an element of an array;
* the tree is completely filled on all levels except possibly the lowest;

Functions:
```cpp
parent(i) { return array[(i-1)/2]; }
left(i) { return array[2*i+1]; }
right(i) { return array[2*i+2]; }
```

Max-heap:
* maintains property for every node `i` other than the root `array[parent(i)] >= array[i]`;
* usually used for sorting.

Min-heap:
* maintains property for every node `i` other than the root `array[parent(i)] <= array[i]`;
* usually used for priority queues.

### Sorting using heap sort

Features:
* **sorts in place**, like insertion sort;
* **O(n lg(n)) worst-case running time**, like merge sort;
* **combines the better attributes of the two - insertion sort and merge sort**;
* uses heap to manage information;

#### Maintaining the heap property

In order to maintain the max-heap property, we call the procedure `MAX_HEAPIFY`.
When it is called, `MAX_HEAPIFY` assumes that binary trees rooted at `LEFT(i)` and `RIGHT(i)` are max-heaps, but that `A[i]` might be smaller than its children, thus violating the max-heap property.

`MAX_HEAPIFY` lets the value `A[i]` "float down" in the max-heap so that the subtree at index `i` obeys the max-heap property.

```
MAX_HEAPIFY(A, i):
    l = LEFT(i)
    r= RIGHT(i)

    if l <= A.heap_size and A[l] > A[i]
        largest = l
    else
        largest = i

    if r <= A.heap_size and A[r] > A[largest]
        largest = r

    if largest != i
        exchange A[i] with A[largest]
        MAX_HEAPIFY(A, largest)
```

#### Building a heap

`MAX_HEAPIFY` can be used in a bottom-up manner to convert an array `A` into a max-heap.

```
BUILD_MAX_HEAP(A):
    A.heap_size = A.length
    for i = A.length/2 downto 1
        MAX_HEAPIFY(A, i)
```

Starting from the lowest level, there are only leaves of the tree, and so each is a 1-element heap to begin with. The procedure goes through the remaining nodes of the tree and runs `MAX_HEAPIFY` on each one.

#### Heap sort algorithm

The heapsort algorithm:
1. Use `BUILD_MAX_HEAP` on input array.
2. The resultant array is a max-heap, however it is not sorted. 
3. Since the maximum element of the array is stored at the root `A[1]` we can put it into its correct final position - exchange values with `A[n]`.
4. Discard the node `n` by decrementing A.heap_size.
5. The children of the root remain max-heaps, but the new rootelemnt might violate the max-heap property.
6. Call `MAX_HEAPIFY(A, 1)`.
7. Go to point 1.

```
HEAPSORT(A)
    BUILD_MAX_HEAP(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heap_size = A.heap_size - 1
        MAX_HEAPIFY(A, 1)
```

## Quicksort

Features:
* **O(n^2) worst case running time, however its expected running time is O(n*lg(n)) with quite small constant factors**;
* **sorts in place**;
* employs divide-and-conquer paradigm.

### Description

Quicksort employs three-step divide-and-conquer process for sorting typical subarray `A[p..r]`:
1. Divide: partition the array `A[p..r]` into two (possibly empty) subarrays:
* `A[p..q-1]` such that each element of if is less than or equal to `A[q]`;
* `A[q+1, r]` such that each element of it is greater than or equal to `A[q]`.
2. Conquer: sort the two subarrays `A[p..q-1]` and `A[q+1..r]` by recursive calls to quicksort.
3. Combine: because the subarrays are already sorted, no work is needed to combine them: the entire array `A[p..r]` is now sorted.

```
QUICKSORT(A, p, r)
    if p < r
        q = PARTITION(A, p, r)
        QUICKSORT(A, p, q - 1)
        QUICKSORT(A, q + 1, r)
```

Partitioning rearranges the subarray in place. It always selects an element `x =A[r]` as pivot element around which to partition the subarray `A[p..r]`.

```
PARTITION(A, p, r)
    x = A[r]
    i = p - 1
    for j = p to r - 1
        if A[j] <= x
            i = i + 1
            exchange A[i] with A[j]
    exchange A[i+1] with A[r]
    return i+1
```

### Performance of quicksort

The running time of quicksort depends on whether the partioning is balanced or unbalanced, which in turn depends on which elements are used for partitioning:
* for balanced partitioning, the algorithm runs asymptoticalyl as fast as merge sort;
* for unbalanced, it can run asymptotically as slow as insertion sort.

The two boundary cases are:
* Worst-case partitioning - occurs when partitioning routine produces on subproblem with `n-1` elements and one with 0 elements. This case running time is O(n^2).
* Best-case partitioning - in the most even possible split, `PARITION` produces two subproblems, each of size no more than `n/2`. In this case quicksort runs much faster - running time is O(nlgn).

**The average-case running time of quicksort is much closer to the best case than to the worst case.**

## Sorting in linear time

### Comparison sort

**Comparison sort** is a sorting algorithm that uses comparisons between input elements to determine the sorted order. All described above algorithms are comparison sort algorithms.

**It can be proved that any comparison sort must make `S(nlgn)` comparisons in the worst case to sort n elements. Thus, merge sort and heapsort are asymptotically optimal and no comparison sort exists that is faset by more than a constant factor.**

Next, three linear time sorting algorithms are introduced - counting sort, radix sort and bucket sort. Of course, these algorithms use operations other than comparisons to determine the sorted order. The `S(nlgn)` lower bound does not apply to them.

### Counting sort

**Assumption: `n` integer input elements in range `0` to `k`, for some integer `k`.**

Features:
* **sorts `n` integer input elements in range `0` to `k`, for some integer `k`**;
* **overall time is `O(k+n)`**; when `k=O(n)` the sort runs in `O(n)` time;
* determines, for each input element `x`, the number of elements less than `x`; then uses this information to place element `x` directly into its position in the output array;
* **it is stable** - the numbers with the same value appear in the output array in the same order as they do in the input array. This is usually important only when satellite data are carried around with the element being sorted.

For the counting sort we need two additional arrays: 
* `B[1..n]` to hold the sorted output;
* `C[0..k]` to provide storage for the numbers of occurrences.

```
COUNTING_SORT(A, B, k)
    let C[0..k] be a new array
    for i = 0 to k
        C[i] = 0

    for j = 1 to A.length
        ++C[A[j]]
    // C[i] now contains the number of elements equal to i

    for i = 1 to k
        C[i] += C[i-1]
    // C[i] now contains the number of elements less than or equal to i

    // going backwards is crucial for stability of the algorithm
    for j = A.length downto 1
      value = A[j]
      numberOfLessOrEqual = C[value]
      B[numberOfLessOrEqual] = value
      --C[value]
```

### Radix sort

Features:
* sorts by sorting by the *least significant* digit first
* the digit sorts must be stable.

```
RADIX_SORT(A, d)
    for i = 1 to d
       use a stable sort to sort A on digit i
```

### Bucket sort

**Assumption: input is generated by a random process that distributes elements uniformly and independently over interval [0, 1).**

Features:
* **sorts `n`-element array `A` which satisfies `0 <= A[i] < 1`**;
* **sorts with average-case running time of O(n)**;
* divides the interval [0, 1) into `n` equal-sized subintervals or **buckets** and then distributes `n` input elements into the buckets;
* since the inputs are uniformly and independently distributed over [0, 1), we do not expect many numbers to fall into each bucket;
* as the buckets are relatively small - they are sorted using insertion sort;
* producing output: sort the numbers in each bucket and then go through the buckets in order, listing elements in each.
* cousin of radix sort in the most-to-least significant digit flavor;
* can be implemented with comparisons and therefore can be also considered a comparison sort algorithm.

```
BUCKET_SORT(A)
    let B[0..n-1] be a new array
    n = A.length

    for i = 0 to n - 1
        make B[i] an empty list // linked list

    for i = 1 to n
        insert A[i] into list B[nA[i]]

    for i = 0 to n - 1
        sort list B[i] with insertion sort // because the list should be small

    concatenate the lists B[0], B[1], ..., B[n-1] together in order
```

## Summary

### Running times

Algorithm      | Worst-case r.t. | Best-case r.t. | Average-case r.t | Assumptions about input
--- | --- | --- | --- | ---
**Insertion sort** | `O(n^2)` | `O(n)` | `O(n^2)` | No (comparison sort)
**Merge sort**     | `O(n*lg(n))` | `O(n*lg(n))` | `O(n*lg(n))` | No (comparison sort)
**Heap sort**      | `O(n*lg(n))` | `O(n)` | `O(n*lg(n))` | No (comparison sort)
**Quicksort**      | `O(n^2)` | `O(n*lg(n))` | `O(n*lg(n))` | No (comparison sort)
**Counting sort**  | `O(k + n)` | `O(k + n)` | `O(k + n)` | Input elements are integers in the set {0, 1, ..., k} |
**Radix sort**     | `O(d(n+k))` | `O(d(n+k))` | `O(d(n+k))` | Input elements are all `d`-digit numbers
**Bucket sort**    | `O(n^2)` | `O(n)` | `O(n)` | Input elements are real numbers uniformly distributed in interval [0, 1)

**Insertion sort**:
* Worst case: input array is sorted in reverse order;
* Best case: input array is already sorted;
* Overall: even faster than quicksort which uses itin small subproblems. Threshold depends on machine but is around 10.

**Quicksort**:
* Worst-case (unbalanced partitioning): in the worst case, `PARTITION` partitioning routine produces one subproblem with n-1 elements and one with 0 elements. When unbalanced partitionng arises in each recursive call, running time is quadratic.
* Best-case (balanced partitioning): `PARTITION` routine produces two subproblems, each of size no more than `n/2` (one of size `n/2`, one of size `n/2-1`).
* Average-case: the average-case running time of quicksort is much closer to the best case than to the worst case (good and bad splits are distributed randomly throughout the tree).

**Heapsort** best-case: all input elements are the same.

**Bucket sort**:
* Worst-case: when the input contains several keys that are close to each other (clustering). The worst case is when all the elements are placed in the same bucket. Then, the overall performance is dominated by the algorithm used to sort each bucket (usually `O(n^2)` insertion sort).
* Best-case: when each bucket has size 1, bucket sort degenerates to counting sort.


### Features

| Algorithm      | In place | Stable | Online | Adaptive |
| -------------- | -------- | ------ | ------ | -------- |
| Insertion sort | yes | yes | yes | yes |
| Merge sort     | no (most impl.) | yes (most impl.) | no | no |
| Heap sort      | yes | no | no | no |
| Quicksort      | yes (most impl.) | no | no | no |
| Counting sort  | no  | yes | no | no |
| Radix sort     | yes | yes | no | no |
| Bucket sort    | no | yes | no | no |

**Counting sort**:
* stability is crucial for its use in radix sort;
* it is possible to implement in-place counting sort, however it will not be stable.

**Bucket sort** requires linked lists, dynamic arrays or a large amount of preallocated memory to hold the sets of items within each bucket.

