#pragma once

#include <stack>

#include "../graph.hpp"



// Time Complexity: O(V + E).
// Here, V represents the number of vertices, and E represents the number of edges.
// We need to check every vertex and traverse through every edge in the graph.

// Space Complexity: O(V).
// Either the manually created stack or the recursive call stack can store up to V vertices.

/*

In Graph theory, the depth-first search algorithm (abbreviated as DFS) is mainly used to:

Traverse all vertices in a “graph”;
Traverse all paths between any two vertices in a “graph”.

*/

std::vector<int> DFSTraverseAll(int v, const Graph& graph) {
    std::stack<int> st;
    std::vector<int> result;
    std::vector<bool> visited(graph.GetSize(), false);

    st.push(v);

    while (!st.empty()) {
        v = st.top();
        st.pop();

        if (visited[v]) {
            continue;
        }

        result.push_back(v);
        visited[v] = true;

        for (int i : graph.GetConnections(v)) {          
            st.push(i);
        }
    }
    return result;
}