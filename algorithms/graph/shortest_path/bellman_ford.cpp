/*

The Bellman-Ford algorithm is used for finding the shortest path from a single source vertex
to all other vertices in a weighted graph. It can handle graphs with negative weight edges,
unlike Dijkstra's algorithm, which assumes non-negative edge weights.

Key differences between the Bellman-Ford algorithm and Dijkstra's algorithm are:

1) Handling of negative weights: The Bellman-Ford algorithm can handle negative weight edges,
while Dijkstra's algorithm cannot. If a graph with negative weight edges is used with Dijkstra's algorithm,
it may result in incorrect shortest path calculations.

2) Detection of negative-weight cycles: The Bellman-Ford algorithm can detect negative-weight cycles in the graph.
If a negative-weight cycle is present, it means that no shortest path exists, as the path can be continuously
traversed through the cycle to obtain a smaller and smaller total weight.
Dijkstra's algorithm does not have this detection capability.

3) Time complexity: Dijkstra's algorithm is generally faster, with a time complexity of O(V^2) or O(V + E * log V)
when implemented with a priority queue, where V is the number of vertices and E is the number of edges.
The Bellman-Ford algorithm has a time complexity of O(V * E),
which makes it slower for dense graphs but potentially faster for sparse graphs with negative weight edges.

4) Algorithm approach: Dijkstra's algorithm is a greedy algorithm that makes locally optimal choices at each step,
while the Bellman-Ford algorithm is a dynamic programming-based algorithm that iteratively
refines the solution based on the relaxation of all edges.

*/


#include <iostream>
#include <limits>
#include <vector>

typedef std::pair<int, int> pii;

bool bellman_ford(int source, const std::vector<std::vector<pii>>& adj_list, std::vector<int>& dist) {
    int n = adj_list.size();
    dist.assign(n, std::numeric_limits<int>::max());
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (const auto& edge : adj_list[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + w < dist[v]) {
                return false; // Negative-weight cycle detected
            }
        }
    }

    return true; // No negative-weight cycle
}

int main() {
    int n = 5, m = 7;
    std::vector<std::vector<pii>> adj_list(n);

    adj_list[0] = {{1, 6}, {3, 5}};
    adj_list[1] = {{0, 6}, {2, 1}, {3, 2}};
    adj_list[2] = {{1, 1}, {4, 4}};
    adj_list[3] = {{0, 5}, {1, 2}, {2, 9}, {4, 2}};
    adj_list[4] = {{2, 4}, {3, 2}};

    int source = 0;

    std::vector<int> dist;
    bool success = bellman_ford(source, adj_list, dist);

    if (success) {
        std::cout << "Shortest path distances from vertex " << source << ":" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "To vertex " << i << ": " << dist[i] << '\n';
        }
    } else {
        std::cout << "Negative-weight cycle detected." << std::endl;
    }

    return 0;
}
