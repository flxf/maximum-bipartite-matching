Simple Maximum Bipartite Matching
=================================

This is also known as the **augmenting path algorithm**.

So, you've just learned the augmenting path proof for finding the maximum
cardinality matching in a bipartite graph! This is pretty much the direct
translation of that proof into an algorithm.

It runs in O(VE) time and is probably the easiest thing you can code from
scratch if you're doing ACM and can afford it.

We assume that you're working with an unweighted undirected graph.

Input Format
------------
The first line of input contains 3 integers `n`, `m` and `e` 
`( 0 <= n, m, e <= 500)` -- the number of vertices in partition A, the number of
vertices in partition B and the number of edges respectively. The next `e` lines
describe two vertices each. A vertex starts with a character 'A' or 'B' denoting
its partition followed by a number `[ 0, size of partition )`.

### Sample Input

    2 3 9
    A0 B0
    A1 B0
    A2 B0
    A2 B1
    A3 B1
    B2 A3
    A4 B2
    B1 A4
    B3 A4

### Sample Output

This is one of a few possible outputs.

    size of maximum matching: 4
    A0 B0
    A2 B1
    A3 B2
    A4 B3
