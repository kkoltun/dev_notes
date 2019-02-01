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
* usually used for pririty queues.

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

The running time of quicksort depends on whether the partioning is balances or unbalanced, which in turn depends on which elements are used for partitioning:
* for balanced partitioning, the algorithm runs asymptoticalyl as fast as merge sort;
* for unbalanced, it can run asymptotically as slow as insertion sort.

The two boundary cases are:
* Worst-case partitioning - occurs when partitioning routine produces on subproblem with `n-1` elements and one with 0 elements. This case running time is O(n^2).
* Best-case partitioning - in the most even possible split, `PARITION` produces two subproblems, each of size no more than `n/2`. In this case quicksort runs much faster - running time is O(nlgn).

**The average-case running time of quicksort is much closer to the best case than to the worst case.**
