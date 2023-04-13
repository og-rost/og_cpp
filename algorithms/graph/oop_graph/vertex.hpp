#pragma once

#include <string>
#include <list>
#include <memory>
#include <iostream>

#include "edge.hpp"

class Vertex {
private:
    std::string data;
    std::list<Edge*> edges;
public:
    Vertex(std::string inputData) : data(inputData) {}

    void addEdge(Vertex* endVertex, int weight) {
        edges.push_back(new Edge(this, endVertex, weight));
    }

    void removeEdge(Vertex* vertex) {
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if ((*it)->getEnd() == vertex) {
                edges.erase(it++);
            }
        }
    }

    std::string getData() {
        return data;
    }

    std::list<Edge*> getEdges() {
        return edges;
    }

    void print(bool showWeights) {
        if (edges.size() == 0) {
            std::cout << data << " -->" << std::endl;
        }

        std::string msg = "";

        auto last = edges.end();
        --last;

        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (it == edges.begin()) {
                msg += (*it)->getStart()->data + " --> ";
            }

            msg += (*it)->getEnd()->data;

            if (showWeights) {
                msg += " (" + std::to_string((*it)->getWeight()) + ")";
            }

            if (it != last) {
                msg += ", ";
            }
        }

        std::cout << msg << std::endl;
    } 

};