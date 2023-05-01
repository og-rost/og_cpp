/*

The Floyd-Warshall algorithm is an all-pairs shortest path algorithm that finds the shortest paths
between all pairs of vertices in a weighted graph. It is a dynamic programming-based algorithm and works
for both directed and undirected graphs. The algorithm can handle graphs with negative weight edges,
but it does not work if the graph has negative-weight cycles.

Key differences between Floyd-Warshall, Dijkstra, and Bellman-Ford algorithms:

Scope of the problem:
Floyd-Warshall: All-pairs shortest paths (finds shortest paths between every pair of vertices in the graph).
Dijkstra: Single-source shortest paths (finds the shortest path from a given source vertex to all other vertices in the graph).
Bellman-Ford: Single-source shortest paths (similar to Dijkstra, but can handle negative weight edges and detect negative-weight cycles).

Time complexity:
Floyd-Warshall: O(V^3), where V is the number of vertices.
Dijkstra: O(V^2) or O(V + E * log V) when implemented with a priority queue, where V is the number of vertices and E is the number of edges.
Bellman-Ford: O(V * E), where V is the number of vertices and E is the number of edges.
Handling of negative weights:

Floyd-Warshall: Can handle negative weight edges but not negative-weight cycles.
Dijkstra: Cannot handle negative weight edges.
Bellman-Ford: Can handle negative weight edges and detect negative-weight cycles.

Algorithm approach:
Floyd-Warshall: Dynamic programming-based algorithm that iteratively refines the solution using a three-level nested loop structure.
Dijkstra: Greedy algorithm that makes locally optimal choices at each step.
Bellman-Ford: Dynamic programming-based algorithm that iteratively refines the solution based on the relaxation of all edges.


In summary, the Floyd-Warshall algorithm is best suited for all-pairs shortest path problems,
particularly when the graph is dense, and the number of vertices is relatively small.
Dijkstra's algorithm is ideal for single-source shortest path problems with non-negative edge weights.
Bellman-Ford is most useful for single-source shortest path problems when negative edge weights
are present or when the detection of negative-weight cycles is required.

*/

#include <iostream>
#include <vector>
#include <limits>

void floyd_warshall(const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& dist) {
    int n = graph.size();
    dist = graph;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max()
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n, std::numeric_limits<int>::max()));

    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }

    graph[0][1] = 2;
    graph[0][2] = 3;
    graph[1][2] = 1;
    graph[1][3] = 5;
    graph[2][3] = 2;

    std::vector<std::vector<int>> dist;
    floyd_warshall(graph, dist);

    std::cout << "All-pairs shortest path distances:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != std::numeric_limits<int>::max()) {
                std::cout << "From vertex " << i << " to vertex " << j << ": " << dist[i][j] << std::endl;
            } else {
                std::cout << "No path from vertex " << i << " to vertex " << j << std::endl;
            }
        }
    }

    return 0;
}
