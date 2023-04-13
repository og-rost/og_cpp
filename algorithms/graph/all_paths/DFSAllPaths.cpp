#include <iostream>
#include <stack>

#include "../graph.hpp"

// iterative solution for a directed acyclic graph

std::vector<std::vector<int>> GetAllPaths(int start, int end, Graph& graph) {  
    std::stack<std::vector<int>> st;
    std::vector<int> route;

    route.push_back(start);
    st.push(route);

    std::vector<std::vector<int>> ans;

    while (!st.empty()) {
        route = st.top();
        st.pop();
        int curr = route.back();
        if (curr == end) {
            ans.push_back(route);
            continue;
        }
        for (int i : graph.GetConnections(curr)) {
            auto vec = route;
            vec.push_back(i);
            st.push(vec);
        }
    }
    return ans;
}

// backtracking

void Backtrack(int start, int end,
               std::vector<int>& path,
               std::vector<std::vector<int>>& results,
               const Graph& graph) {
    if (start == end) {
        results.push_back(path);
        return;
    }
    for (int nextNode : graph.GetConnections(start)) {
        path.push_back(nextNode);
        Backtrack(nextNode, end, path, results, graph);
        path.pop_back();
    }
}

std::vector<std::vector<int>> GetAllPathsRec(int start, int end, const Graph& graph) {
    std::vector<int> path{start};
    std::vector<std::vector<int>> results;

    Backtrack(start, end, path, results, graph);
    return results;
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

    res = GetAllPathsRec(0, 3, graph);
    for (auto v : res) {
        for (int i : v) {
        std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}