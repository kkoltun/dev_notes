# Topological sort

## Properties

Topological sort:
* uses depth-first search to perform sorting of directed acyclic graph (DAG).
* is a linear ordering of all dag `G = (V, E)` vertices such that if `G` contains an edge `(u, v)`, then `u` appears before `v` in the ordering;
* in other words, is an ordering of vertices along a horizontal line so that all directed edges go from left to right.

## Schema

![Topological sort in CLRS](./images/topological_sort.png)

```
TOPOLOGICAL_SORT(G)
  call DFS(G) to compute finishing times v.f for each vertex v
  as each vertex is finished, insert it onto the from of a linked list
  return the linked list of vertices
```

