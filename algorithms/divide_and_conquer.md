# Divide-and-Conquer

## Overview

In divide-and-conquer, we solve a problem recursively, applying three steps at each level of the recursion:
* **Divide** the problem into a number of subproblems that are smaller instances of the same problem.
* **Conquer** the subproblems by solving them recursively. if the subproblem sizes are small enough, however, just solve them in a straightforward manner.
* **Combine** the solutions to the subproblems into the solution for the original problem.

There are two cases in divide-and-conquer:
* **Recursive case** - when subproblems are large enough to solve recursively.
* **Base case** - when subproblems are small enough that we no longer recurse, we say that the recursion "bottoms out".

## Merge sort

The **merge sort** algorithm closely follows the divide-and-conquer paradigm:
* **Divide**: Divide the `n`-element sequence to be sorted into two subsequences of `n/2` elements each.
* **Conquer**: Sort the two subsequences recursively using merge sort.
* **Combine**: Merge the two sorted subsequences to produce the sorted answer.

The recursion "bottoms out" when the sequence to be sorted has length 1, in which case there is no work to be done, since each sequence of length 1 is already in sorted order.

## The maximum-subarray problem

The problem is to find a maximum subarray of the subarray `A[low..high]`.

### Divide-and-conquer approach

The divide-and-conquer technique suggests that we divide the subarray into two subarrays of as equal size as possible. This means we find the midpoint `mid` of the subarray and consider the subarrays `A[low..mid]` and `A[mid+1..high]`.

It is worth to note that any contiguous subarray `A[i..j]` of `A[low..high]` must lie exactly in one of the following places:
* entirely in the subarray `A[low..mid]`, so `low <= i <= j <= mid`;
* entirely in the subarray `A[mid+1..high]`, so `mid < i <= j <= high`;
* crossing the midpoint, so `low <= i <= mid < j <= high`.

**Therefore, a maximum subarray of `A[low..high]` must lie exactly in one of these places. Furthermore, it must have the greatest sum over all subarrays in either of these places.**

This reasoning suggests the following approach:
* **Divide**: Find midpoint `mid` dividing the subarray into two subarrays of as equal size as possible;
* **Conquer**: Find maximum subarrays of `A[low..mid]` (`max_right`) and `A[mid+1..high]` (`max_left`) recursively. These two problems are smaller instances of the problem of finding a maximum subarray.
* **Combine one**: Find a maximum subarray that crosses the midpoint (`max_cross`). This is a problem that is not a smaller instance of the original one, so we consider it to be in combine part.
* **Combine two**: Choose the subarray with the largest sum of the three `[max_right, max_cross, max_left]`.

### Finding the maximum subarray crossing the midpoint

It is worth to note that maximum subarray crossing the midpoint `mid` in subarray `A[low..high]` is itself made of two subarrays: `A[i..mid]` and `A[mid..j]` where `low <= i <= mid` and `mid < j <= high`. This way, we need to find maximum subarrays of the form `A[i..mid]` and `A[mid..j]` and then combine them.

`FIND_MAX_CROSSING_SUBARRAY` takes as input the array `A` and the indices `low`, `mid`, `high` and returns a tuple containing the indices of a maximum subarray that crosses the midpoint, along with the sum:

```
FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high)
    left_sum = -inf
    sum = 0

    for i = mid downto low
        sum = sum + A[i]
        if sum > left_sum
            left_sum = sum
            left_idx = i

    right_sum = -inf
    sum = 0

    for i = mid + 1 to high
        sum = sum + A[j]
        if sum > right_sum
            right_sum = sum
            right_idx = i

    return (left_idx, right_idx, left_sum + right_sum)
```

The `FIND_MAX_CROSSING_SUBARRAY` is linear-time.

### The final algorithm

Now pseudocode for a divide-and-conquer algorithm to solve the maximum-subarray problem can be written (assuming `RETURN_MAX` returns the result with largest sum of the provided):

```
FIND_MAX_SUBARRAY(A, low, high)
    if high == low                                           // base case
        return (low, high, A[low])

    mid = (high + low)/2                                     // divide step

    left = FIND_MAX_SUBARRAY(A, low, mid)                    // conquer step 1
    right = FIND_MAX_SUBARRAY(A, mid+1, high)                // conquer step 2
    crossing = FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high) // combine step 1

    return RETURN_MAX(left, right, crossing)                 // combine step 2
```

**The algorithm runs in O(n*lgn) time.**
