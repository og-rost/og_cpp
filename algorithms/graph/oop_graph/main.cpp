#include "graph.hpp"
#include "traverser.hpp"


void test() {
    Graph testGraph(false, true);

    Vertex* start = testGraph.addVertex("v0.0.0");
    Vertex* v1 = testGraph.addVertex("v1.0.0");
    Vertex* v2 = testGraph.addVertex("v2.0.0");

    Vertex* v11 = testGraph.addVertex("v1.1.0");
    Vertex* v12 = testGraph.addVertex("v1.2.0");
    Vertex* v21 = testGraph.addVertex("v2.1.0");

    Vertex* v111 = testGraph.addVertex("v1.1.1");
    Vertex* v112 = testGraph.addVertex("v1.1.2");
    Vertex* v121 = testGraph.addVertex("v1.2.1");
    Vertex* v211 = testGraph.addVertex("v2.1.1");

    testGraph.addEdge(start, v1);
    testGraph.addEdge(start, v2);

    testGraph.addEdge(v1, v11);
    testGraph.addEdge(v1, v12);
    testGraph.addEdge(v2, v21);

    testGraph.addEdge(v11, v111);
    testGraph.addEdge(v11, v112);
    testGraph.addEdge(v12, v121);
    testGraph.addEdge(v21, v211);

    // create a cycle
    testGraph.addEdge(v211, v2);

    Traverser t;
    std::unordered_set<Vertex*> visited;
    visited.emplace(start);
    t.dfs(start, visited);
}


int main() {
    Graph busNetwork(true, false);

    Vertex* cliftonStation = busNetwork.addVertex("Clifton");
    Vertex* capeMayStation = busNetwork.addVertex("Cape May");

    busNetwork.addEdge(cliftonStation, capeMayStation, 1000);

    busNetwork.print();


    test();

    return 0;
}