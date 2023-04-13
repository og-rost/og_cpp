#include <iostream>

#include "BFSTraverseAll.hpp"
#include "DFSTraverseAll.hpp"
#include "DFSTraverseAllRec.hpp"

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

      std::cout << std::endl << "DFS from " << sp << std::endl;
      auto gr = DFSTraverseAll(sp, graph);
      for (int v : gr) {
        std::cout << v << " ";
      }
      std::cout << std::endl;

      std::cout << std::endl << "Recursive DFS from " << sp << std::endl;
      gr = DFSTraverseAllRecursive(sp, graph);
      for (int v : gr) {
        std::cout << v << " ";
      }
      std::cout << std::endl;

      std::cout << std::endl << "BFS from " << sp << std::endl;
      gr = BFSTraverseAll(sp, graph);
      for (int v : gr) {
        std::cout << v << " ";
      }
      std::cout << std::endl;
    }

    return 0;
}