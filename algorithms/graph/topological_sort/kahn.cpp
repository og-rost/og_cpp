/*


Both the DFS-based topological sort algorithm and Kahn's algorithm have similar time complexities:

DFS-based topological sort:
The time complexity of this algorithm is O(V + E), where V is the number of vertices and E is the number of edges in the graph.
This is because each vertex is visited once during the depth-first search, and each edge
is traversed once during the exploration of the adjacency list.

Kahn's algorithm:
The time complexity of Kahn's algorithm is also O(V + E), where V is the number of vertices and E is the number of edges in the graph.
This is because we iterate through all vertices to calculate the in-degree and add the initial vertices with in-degree 0 to the queue.
Then, for each vertex, we process its neighbors (edges) and update their in-degrees accordingly.
In total, the algorithm visits each vertex and traverses each edge once.

In terms of time complexity, both algorithms have comparable performance.
However, the actual running time and performance may differ depending on the input graph and implementation details.

It is also worth mentioning that the DFS-based topological sort algorithm
is more space-efficient because it only requires a depth-first search stack,
while Kahn's algorithm requires an additional in-degree vector and a processing queue.
Thus, the DFS-based topological sort algorithm might be more suitable for situations where memory usage is a concern.
However, Kahn's algorithm is more intuitive and easier to understand,
which can be beneficial in terms of code readability and maintainability.

*/

#include <iostream>
#include <vector>
#include <queue>

std::vector<int> kahn_topological_sort(const std::vector<std::vector<int>>& adj_list) {
    int n = adj_list.size();
    std::vector<int> in_degree(n, 0);

    for (const auto& neighbors : adj_list) {
        for (int neighbor : neighbors) {
            in_degree[neighbor]++;
        }
    }

    std::queue<int> q;
    for (int v = 0; v < n; v++) {
        if (in_degree[v] == 0) {
            q.push(v);
        }
    }

    std::vector<int> sorted;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        sorted.push_back(v);

        for (int neighbor : adj_list[v]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
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

    std::vector<int> sorted = kahn_topological_sort(adj_list);

    std::cout << "Topological sort (Kahn's algorithm):" << std::endl;
    for (int v : sorted) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    return 0;
}
