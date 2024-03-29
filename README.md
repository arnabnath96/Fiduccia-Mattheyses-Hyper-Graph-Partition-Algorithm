# Fiduccia-Mattheyses-Hyper-Graph-Partition-Algorithm

THE HYPER-GRAPH BI-PARTITIONING PROBLEM
---------------------------------------
Given an input hyper-graph, partition it into a given number of **almost equal-sized parts** in such a way that the cutsize, i.e., the sum of the edge weights whose end vertices are in different parts, is minimized . This problem has many variations as well as important applications in VLSI. Unfortunately, the problem is NP-hard.

A hypergraph is a generalization of a graph in which an edge can join any number of vertices. Formally, a hypergraph H is a pair H=(X,E) where X is a set of elements called nodes or vertices, and E is a set of non-empty subsets of X called hyperedges or edges. Since hypergraphs can model electronic circuits well, a hypergraph is often said to have cells and nets instead of vertices and hyperedges. In a circuit cell where a net is connected is called a pin.

HOW TO RUN
----------
```
$ gcc hypergraph-partition-FM-Algorithm.c -o fm
$ ./fm
```
or
```
$ gcc hypergraph-partition-FM-Algorithm.c -o fm
$ ./fm input_file
```

INPUT_FILE FORMAT
------------
First Line : *No. of verties(n)* (space) *No. of hyperedges(m)*

Next m lines : *No. of vertices in each hyperedge* (space) *list of the Node Numbers in that hyperedge seperated by space*

last line(area constraint) : *min_val* (space) *max_val*

**Example :** 

8 6

3 0 2 4

3 1 2 3

3 2 4 5

3 5 6 7

2 3 5

2 4 6

3 5

HOW THE ALGORITHM WORKS
-----------------------

Reference : (http://limsk.ece.gatech.edu/book/slides/pdf/FM-partitioning.pdf)
