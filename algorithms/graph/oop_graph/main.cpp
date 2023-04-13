#include "graph.hpp"

int main() {
    Graph busNetwork(true, false);

    Vertex* cliftonStation = busNetwork.addVertex("Clifton");
    Vertex* capeMayStation = busNetwork.addVertex("Cape May");

    busNetwork.addEdge(cliftonStation, capeMayStation, 1000);

    busNetwork.print();

    return 0;
}