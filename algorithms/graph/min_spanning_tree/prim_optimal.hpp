#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

#include "common.hpp"

void primOptimal(const std::vector<Edge>& edges, int numVertices) {
    int edgesUsed = 0;

    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    for (const Edge& edge : edges) {
        adjList[edge.src].push_back({edge.dest, edge.weight});
        adjList[edge.dest].push_back({edge.src, edge.weight});
    }

    std::vector<bool> inMST(numVertices);
    std::vector<int> minDist(numVertices, INT_MAX);
    std::vector<int> parent(numVertices, -1);
    minDist[0] = 0;

    while (edgesUsed < numVertices) {
        int currMinEdge = INT_MAX;
        int currNode = -1;

        for (int node = 0; node < numVertices; ++node) {
            if (!inMST[node] && currMinEdge > minDist[node]) {
                currMinEdge = minDist[node];
                currNode = node;
            }
        }

        if (currNode != -1 && parent[currNode] != -1) {
            std::cout << "Edge: " << parent[currNode] << " - " << currNode << ", Weight: " << currMinEdge << std::endl;
        }
        
        ++edgesUsed;
        inMST[currNode] = true;

        for (const auto &[nextNode, weight] : adjList[currNode]) {
            if (!inMST[nextNode] && minDist[nextNode] > weight) {
                minDist[nextNode] = weight;
                parent[nextNode] = currNode;
            }
        }
    }
}