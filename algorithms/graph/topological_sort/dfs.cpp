/*

Topological sort is an algorithm for linearly ordering the vertices of a directed acyclic graph (DAG)
such that for every directed edge (u, v) from vertex u to vertex v, vertex u comes before vertex v in the ordering.

In other words, a topological sort provides a valid sequence of vertices in which all the edges
point from an earlier vertex to a later vertex in the sequence.

Topological sort is used in various applications, such as scheduling tasks with dependencies,
determining the order of compilation for a set of files with dependencies, or finding a valid sequence of courses
to take in a curriculum with prerequisite courses.

There are two common algorithms to perform a topological sort:

Depth-First Search (DFS) based algorithm:
This algorithm uses DFS to explore the graph, and as vertices finish their DFS exploration (all descendants have been visited),
they are added to the result in reverse order. This algorithm is also known as the "reverse postorder" approach.

Kahn's algorithm:
This algorithm iteratively finds and removes vertices with no incoming edges (in-degree equals zero)
and adds them to the result. After removing a vertex, its outgoing edges are also removed, potentially reducing
the in-degree of other vertices to zero, which can then be processed in the next iteration.

Note that a topological sort is only possible for directed acyclic graphs (DAGs). If the graph contains a cycle,
no valid topological ordering exists, as there would be a circular dependency between the vertices involved in the cycle.

*/

#include <iostream>
#include <vector>
#include <stack>


void dfs(int v, const std::vector<std::vector<int>>& adj_list, std::vector<bool>& visited, std::stack<int>& result) {
    visited[v] = true;

    for (int neighbor : adj_list[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj_list, visited, result);
        }
    }

    result.push(v);
}

std::vector<int> topological_sort(const std::vector<std::vector<int>>& adj_list) {
    int n = adj_list.size();
    std::vector<bool> visited(n, false);
    std::stack<int> result;

    for (int v = 0; v < n; v++) {
        if (!visited[v]) {
            dfs(v, adj_list, visited, result);
        }
    }

    std::vector<int> sorted;
    while (!result.empty()) {
        sorted.push_back(result.top());
        result.pop();
    }

    return sorted;
}

int main() {
    int n = 6;
    std::vector<std::vector<int>> adj_list(n);

    adj_list[0] = {1};
    adj_list[1] = {2, 3};
    adj_list[2] = {4};
    adj_list[3] = {4};
    adj_list[4] = {5};
    adj_list[5] = {};

    std::vector<int> sorted = topological_sort(adj_list);

    std::cout << "Topological sort:" << std::endl;
    for (int v : sorted) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    return 0;
}
