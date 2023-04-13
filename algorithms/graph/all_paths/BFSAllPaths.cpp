#include <iostream>
#include <queue>

#include "../graph.hpp"

std::vector<std::vector<int>> GetAllPaths(int start, int end, Graph& graph) {  
    std::queue<std::vector<int>> q;
    std::vector<int> route;

    route.push_back(start);
    q.push(route);

    std::vector<std::vector<int>> ans;

    while (!q.empty()) {
        route = q.front();
        q.pop();
        int curr = route.back();
        if (curr == end) {
            ans.push_back(route);
            continue;
        }
        for (int i : graph.GetConnections(curr)) {
            auto vec = route;
            vec.push_back(i);
            q.push(vec);
        }
    }
    return ans;
}

int main() {
    Graph graph(4, true);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(0, 3);
    graph.AddEdge(2, 1);
    graph.AddEdge(1, 3);

    auto res = GetAllPaths(0, 3, graph);
    for (auto v : res) {
        for (int i : v) {
        std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    return 0;
}