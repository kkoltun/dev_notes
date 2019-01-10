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

Features:
* **sorts in place**, like insertion sort;
* **O(n lg(n)) worst-case running time**;
* uses heap to manage information;
* 