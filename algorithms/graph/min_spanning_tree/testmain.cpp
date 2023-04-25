#include "kruskal.hpp"
#include "kruskal_union.hpp"
#include "prim.hpp"
#include "prim_optimal.hpp"

int main() {
    int numVertices = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    
    std::cout << "Kruskal's algorithm" << std::endl;

    kruskalMST(edges, numVertices);

    std::cout << "Kruskal's algorithm using Union-Find" << std::endl;

    kruskalUnion(edges, numVertices);

    std::cout << "Prim's algorithm" << std::endl;

    primMST(edges, numVertices);

    std::cout << "Prim's algorithm optimized" << std::endl;

    primOptimal(edges, numVertices);
    
    return 0;
}