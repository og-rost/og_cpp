#include <iostream>

#include "BFSShortestPath.hpp"

#include "../graph.hpp"

int main() {
    Graph graph(6, false);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(0, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(2, 5);
    graph.AddEdge(3, 5);
    graph.AddEdge(4, 5);

    int sp;
    int dest;

    while (1) {
        std::cout << "enter starting point: ";

        while (1) {
            std::cin >> sp;
            if (sp >= graph.GetSize()) {
                std::cout << "wrong starting point, enter againt: ";
            } else {
                break;
            }
        }

        std::cout << "enter destination point: ";

        while (1) {
            std::cin >> dest;
            if (dest >= graph.GetSize()) {
                std::cout << "wrong destination point, enter againt: ";
            } else {
                break;
            }
        }

        std::cout << std::endl << "Shortest path using BFS between " << sp << " and " << dest << std::endl;
        auto path = BFSShortestPath(sp, dest, graph);
        for (int v : path) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}