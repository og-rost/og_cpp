/*

A spanning tree is a connected subgraph in an undirected graph where all vertices are connected with the minimum number of edges.

A minimum spanning tree is a spanning tree with the minimum possible total edge weight in a “weighted undirected graph”.

In graph theory, a cut is a partition of the vertices of a graph into two disjoint sets.
In other words, it is a division of the graph into two parts, such that each part contains some vertices,
and there are no vertices that belong to both parts. A cut can be represented by a set of edges that,
when removed from the graph, would result in the separation of the two sets of vertices.

Cuts are often used to study the connectivity and flow properties of graphs. A common example is the "minimum cut" problem,
which seeks to find the cut with the smallest number of edges (or the minimum total weight for weighted graphs) that,
when removed, would disconnect the graph. This has applications in network design, transportation, and other fields
where it is essential to understand the weakest points or bottlenecks in a system.




Kruskal's algorithm is a greedy algorithm for finding the minimum spanning tree (MST) of an undirected, connected, and weighted graph.


Time Complexity: O(E*logE).

*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "common.hpp"

int findParent(int vertex, std::vector<int>& parent) {
    if (parent[vertex] == -1) {
        return vertex;
    }
    return findParent(parent[vertex], parent);
}

void kruskalMST(std::vector<Edge>& edges, int numVertices) {
    std::sort(edges.begin(), edges.end(), compareEdges);
    
    std::vector<int> parent(numVertices, -1);
    std::vector<Edge> mst;
    
    for (Edge& edge : edges) {
        int srcParent = findParent(edge.src, parent);
        int destParent = findParent(edge.dest, parent);
        
        if (srcParent != destParent) {
            mst.push_back(edge);
            parent[srcParent] = destParent;
        }
    }
    
    for (Edge& edge : mst) {
        std::cout << "Edge: " << edge.src << " - " << edge.dest << ", Weight: " << edge.weight << std::endl;
    }
}
