#pragma once

#include <queue>

#include "../graph.hpp"

/*

In Graph theory, the primary use cases of the “breadth-first search” (“BFS”) algorithm are:

1) Traversing all vertices in the “graph”;
2) Finding the shortest path between two vertices in a graph where all edges have equal and positive weights.

The most advantageous use case of “breadth-first search” is to efficiently find the shortest path between
two vertices in a graph where all edges have equal and positive weights.

Although the “depth-first search” algorithm can find the shortest path between two vertices in a “graph”
with equal and positive weights, it must traverse all paths between two vertices before finding the shortest one.
The “breadth-first search” algorithm, in most cases, can find the shortest path without traversing all paths.
This is because when using "breadth-first search", as soon as a path between the source vertex and target vertex is found,
it is guaranteed to be the shortest path between the two nodes.

*/

std::vector<int> BFSTraverseAll(int v, const Graph& graph) {
    std::vector<bool> visited(graph.GetSize(), false);

    std::queue<int> q;
    std::vector<int> result;

    q.push(v);

    while (!q.empty()) {
        v = q.front();
        q.pop();

        if (visited[v]) {
            continue;
        }

        result.push_back(v);
        visited[v] = true;

        for (int i : graph.GetConnections(v)) {
            q.push(i);
        }
    }
    return result;
}


/*

Time complexity O(E + V)
Space complexit O(V)

*/