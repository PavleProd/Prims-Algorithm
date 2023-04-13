# Prims-Algorithm
Implementation of Prim's algorithm in O(E log V) time complexity.
E is the number of edges
V is the number of vertices in a graph

* The code defines a Graph class that represents an undirected weighted graph using
an adjacency list.
* The Tuple class is a simple data structure that holds information about an edge,
including its weight and the indices of its two vertices.
* The Comparator class is a functor that compares two Tuple objects by their weights,
used for sorting elements in the priority queue.
* The primsAlgorithm() function takes a Graph object representing the original graph
as an argument and returns a Graph object representing the minimal spanning tree
using Prim's algorithm.
* edges.txt contains lines of i j weight with whitespace separator for initializing the
graph. i and j are vertices and weight is the weight of the edge between them
