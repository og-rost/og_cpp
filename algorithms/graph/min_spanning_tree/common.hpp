#pragma once

struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

struct CompareEdges {
    bool operator()(const Edge& e1, const Edge& e2) const {
        return e1.weight > e2.weight;
    }
};