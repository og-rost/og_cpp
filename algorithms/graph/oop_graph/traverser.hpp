#pragma once

#include <unordered_set>
#include <iostream>

#include "graph.hpp"

class Traverser {
public:
    void dfs(Vertex* start, std::unordered_set<Vertex*> visited) {
        std::cout << start->getData() << std::endl;

        for (Edge* e : start->getEdges()) {
            Vertex* neighbor = e->getEnd();

            if (!visited.count(neighbor)) {
                visited.emplace(neighbor);
                dfs(neighbor, visited);
            }
        }
    }
};