#pragma once

#include <vector>

class Graph {
private:
    int vertics;
    bool directed;
    std::vector<std::vector<int>> graph;
public:
    Graph(int v, bool d) : vertics(v), directed(d) { graph.resize(v); }

    void AddEdge(int source, int destination) {
        graph[source].push_back(destination);
        if (!directed) {
            graph[destination].push_back(source);
        }
    }

    int GetSize() const { return vertics; }
    std::vector<int> GetConnections(int vertex) const { return graph[vertex]; }
};