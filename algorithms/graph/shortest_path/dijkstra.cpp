/*

We've used the BFS algorithm to find the shortest path between two vertices.
However, the BFS algorithm can only solve the shortest path problem in unweighted graphs.


“Dijkstra’s algorithm” solves the “single-source shortest path” problem in a weighted directed graph with non-negative weights.

We take the starting point u as the center and gradually expand outward while updating
the “shortest path” to reach other vertices.

“Dijkstra's Algorithm” uses a “greedy approach”. Each step selects the “minimum weight”
from the currently reached vertices to find the “shortest path” to other vertices.

Time complexity:

O(E + VlogV) when fibonacci heap is used
O(E + ElogV) when binary heap is used

Space complexity: O(V)

*/


#include <iostream>
#include <limits>
#include <queue>
#include <vector>

typedef std::pair<int, int> pii;

std::vector<int> dijkstra(int source, const std::vector<std::vector<pii>>& adj_list) {
    int n = adj_list.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    dist[source] = 0;

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) {
            continue;
        }

        for (const auto& edge : adj_list[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    int n = 5, m = 6;
    std::vector<std::vector<pii>> adj_list(n);

    adj_list[0] = {{1, 10}, {3, 5}};
    adj_list[1] = {{0, 10}, {2, 1}, {3, 2}};
    adj_list[2] = {{1, 1}, {4, 4}};
    adj_list[3] = {{0, 5}, {1, 2}, {2, 9}, {4, 2}};
    adj_list[4] = {{2, 4}, {3, 2}};

    int source = 0;

    std::vector<int> dist = dijkstra(source, adj_list);

    std::cout << "Shortest path distances from vertex " << source << ":" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "To vertex " << i << ": " << dist[i] << std::endl;
    }

    return 0;
}
