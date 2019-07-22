#include "../headers/Graph.h"

// Test graph functionality

int main() {
    Graph g;
    g.addNodes(9);
    
    g.link(0, 1);
    g.link(1, 2);
    g.link(0, 3);
    g.link(3, 2);
    g.link(5, 6);
    g.link(5, 7);
    g.link(5, 3);
    g.link(6, 7);
    g.link(8, 7);

    std::cout << "There are " << g.connectedComponents()
              << " connected components\n";
    g.topologicalSort();

    return 0;
}
