/*

Prim's algorithm is a greedy algorithm used to find the minimum spanning tree (MST) of a connected, undirected,
and weighted graph. The algorithm starts from an arbitrary vertex and iteratively adds the edge with
the minimum weight that connects a vertex already in the MST to a vertex not yet in the MST.


The time complexity of the provided Prim's algorithm implementation is dominated by three main operations:
    building the adjacency list, inserting edges into the priority queue, and extracting edges from the priority queue.

1) Building the adjacency list: O(E) time, where E is the number of edges in the graph.

2) Inserting edges into the priority queue: In the worst case, all edges are inserted into the priority queue,
which takes O(E * log(E)) time. The insertion of each edge into the priority queue takes O(log(E)) time,
and this operation is performed for E edges.

3) Extracting edges from the priority queue: In the worst case, we extract all edges from the priority queue,
which takes O(E * log(E)) time. The extraction of each edge from the priority queue takes O(log(E)) time,
and this operation is performed for E edges.

4) Combining these complexities, the overall time complexity of the provided Prim's algorithm implementation is O(E + E * log(E) + E * log(E)) = O(E * log(E)).

However, it's important to note that this implementation can be optimized using more efficient data structures like a Fibonacci heap,
which can reduce the time complexity of inserting and extracting edges in the priority queue. With a Fibonacci heap,
the time complexity of Prim's algorithm can be reduced to O(E + V * log(V)), where V is the number of vertices in the graph.

*/

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

#include "common.hpp"


void primMST(const std::vector<Edge>& edges, int numVertices) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    
    for (const Edge& edge : edges) {
        adjList[edge.src].push_back({edge.dest, edge.weight});
        adjList[edge.dest].push_back({edge.src, edge.weight});
    }
    
    std::vector<bool> visited(numVertices, false);
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> minHeap;
    
    visited[0] = true;
    for (const auto &[dest, weight] : adjList[0]) {
        minHeap.push({0, dest, weight});
    }
    
    while (!minHeap.empty()) {
        Edge currentEdge = minHeap.top();
        minHeap.pop();
        
        if (visited[currentEdge.dest]) continue;
        visited[currentEdge.dest] = true;

        std::cout << "Edge: " << currentEdge.src << " - " << currentEdge.dest << ", Weight: " << currentEdge.weight << std::endl;
        
        for (const auto &[dest, weight] : adjList[currentEdge.dest]) {
            if (!visited[dest]) {
                minHeap.push({currentEdge.dest, dest, weight});
            }
        }
    }
}