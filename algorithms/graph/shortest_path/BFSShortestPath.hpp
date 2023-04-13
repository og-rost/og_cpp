#pragma once

#include <queue>
#include <algorithm>
#include <iostream>

#include "../graph.hpp"

bool BFS(int start, int end, const Graph& graph, std::vector<int>& parent) {
    std::vector<bool> visited(graph.GetSize(), false);
    std::queue<int> q;

    q.push(start);

    while (!q.empty()) {
        start = q.front();
        q.pop();

        if (visited[start]) {
            continue;
        }

        visited[start] = true;

        for (int i : graph.GetConnections(start)) {
            if (visited[i]) {
                continue;
            }
            if (parent[i] == -1) {
                parent[i] = start;
            }
            // std::cout << "seetting parent of " << i << "-> " << start << std::endl;
            q.push(i);

            if (i == end) {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> BFSShortestPath(int start, int end, const Graph& graph) {
    std::vector<int> parent(graph.GetSize(), -1);
    if (BFS(start, end, graph, parent) == false) {
        return std::vector<int>();
    }
    std::vector<int> path;

    while (parent[end] != -1) {
        path.push_back(end);
        end = parent[end];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

/*

Time complexity O(E + V)
Space complexit O(V)

*/