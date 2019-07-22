#include "../headers/Graph.h"

// Test graph functionality

int main() {
    Graph g;
    g.addNodes(12);
    g.linkBoth(0, 1);
    g.linkBoth(0, 2);
    g.linkBoth(1, 2);
    g.linkBoth(2, 7);
    g.linkBoth(3, 4);
    g.linkBoth(3, 5);
    g.linkBoth(3, 6);
    g.linkBoth(4, 5);
    g.linkBoth(6, 8);
    g.linkBoth(9, 10);

    std::cout << "There are " << g.connectedComponents()
              << " connected components\n";
    g.topologicalSort();

    return 0;
}
