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
            // std::cout << "setting parent of " << i << "-> " << start << std::endl;
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

/*

Time complexity O(E + V)
Space complexit O(V)

*/