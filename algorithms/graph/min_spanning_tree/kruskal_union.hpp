#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "common.hpp"

class UnionFind {
public:
    std::vector<int> group;
    std::vector<int> rank;

    UnionFind(int size) {
        group = std::vector<int>(size);
        rank = std::vector<int>(size);
        for (int i = 0; i < size; ++i) {
            group[i] = i;
        }
    }

    int find(int node) {
        if (group[node] != node) {
            group[node] = find(group[node]);
        }
        return group[node];
    }

    bool join(int node1, int node2) {
        int group1 = find(node1);
        int group2 = find(node2);
        
        // node1 and node2 already belong to same group.
        if (group1 == group2) {
            return false;
        }

        if (rank[group1] > rank[group2]) {
            group[group2] = group1;
        } else if (rank[group1] < rank[group2]) {
            group[group1] = group2;
        } else {
            group[group1] = group2;
            rank[group2] += 1;
        }

        return true;
    }
};

void kruskalUnion(std::vector<Edge>& edges, int numVertices) {
    std::sort(edges.begin(), edges.end(), compareEdges);
        
    UnionFind uf(numVertices);
    int mstCost = 0;
    int edgesUsed = 0;
        
    for (int i = 0; i < edges.size() && edgesUsed < numVertices - 1; ++i) {
        int node1 = edges[i].src;
        int node2 = edges[i].dest;
        int weight = edges[i].weight;
            
        if (uf.join(node1, node2)) {
            mstCost += weight;
            std::cout << "Edge: " << node1 << " - " << node2 << ", Weight: " << weight << std::endl;
            ++edgesUsed;
        }
    }
}