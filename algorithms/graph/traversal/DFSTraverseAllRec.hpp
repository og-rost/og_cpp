#pragma once

#include "../graph.hpp"

void DFSRec(int v, const Graph& graph,
            std::vector<int>& result,
            std::vector<bool>& visited) {

    visited[v] = true;
    result.push_back(v);

    for (int i : graph.GetConnections(v)) {
        if (!visited[i]) {
            DFSRec(i, graph, result, visited);
        }
    }
}

std::vector<int> DFSTraverseAllRecursive(int v, const Graph& graph) {
    std::vector<int> result;
    std::vector<bool> visited(graph.GetSize(), false);

    DFSRec(v, graph, result, visited);

    return result;
}