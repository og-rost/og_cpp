#pragma once

#include <list>
#include <string>

#include "vertex.hpp"

class Graph {
private:
    std::list<Vertex*> vertecies;
    bool _isWeighted;
    bool _isDirected;
public:
    Graph(bool inputIsWeighted, bool inputIsDirected)
        : _isWeighted(inputIsWeighted), _isDirected(inputIsDirected) {}

    Vertex* addVertex(std::string data) {
        Vertex* v = new Vertex(data);

        vertecies.push_back(v);
        return v;
    }

    void addEdge(Vertex* v1, Vertex* v2, int weight = -1) {
        v1->addEdge(v2, weight);
        if (!_isDirected) {
            v2->addEdge(v1, weight);
        }
    }

    void removeEdge(Vertex* vertex1, Vertex* vertex2) {
        vertex1->removeEdge(vertex2);
        if (!_isDirected) {
            vertex2->removeEdge(vertex1);
        }

        // TODO update vertexes connected to this edge
    }

    void removeVertex(Vertex* vertex) {
        for (auto it = vertecies.begin(); it != vertecies.end(); ++it) {
            if (*it == vertex) {
                vertecies.erase(it);
                return;
            }
        }

        // TODO remove also edges connected to this vertex
    }

    std::list<Vertex*> getVertices() {
        return vertecies;
    }

    bool isWeighted() {
        return _isWeighted;
    }

    bool isDirected() {
        return _isDirected;
    }

    Vertex* getVertexByValue(std::string value) {
        for (Vertex* vertex : vertecies) {
            if (vertex->getData() == value) {
                return vertex;
            }
        }

        return nullptr;
    }

    void print() {
        for (Vertex* vertex : vertecies) {
            vertex->print(_isWeighted);
        }
    }
};