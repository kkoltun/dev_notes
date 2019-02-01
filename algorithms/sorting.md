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

Pseudocode for the `MERGE` step:
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

Pseudocode for the `MERGE_SORT`:
```
MERGE_SORT(A, p, r)
    if p < r
        q = (p + 1)/2

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
1. Use BUILD_MAX_HEAP on input array.
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
