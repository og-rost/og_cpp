#pragma once

#include <memory>

class Vertex;

class Edge {
private:
    Vertex* start;
    Vertex* end;
    int weight;

public:
    Edge(Vertex* startV,
         Vertex* endV,
         int inputWeight = -1)
         : start(startV), end(endV), weight(inputWeight) {}

    Vertex* getStart() {
        return start;
    }

    Vertex* getEnd() {
        return end;
    }

    int getWeight() {
        return weight;
    }
};