#include "../headers/Graph.h"

// Test graph functionality

int main() {
    Graph g;
    g.addNodes(10);
    g.link(0,1);
    g.link(1,2);
    g.link(2,3);
    g.link(3,4);
    g.link(4,5);
    g.link(5,6);
    g.link(6,7);
    g.link(7,8);
    g.link(8,9);

    Graph h;
    h.addNodes(10);
    h.linkBoth(0,1);
    h.linkBoth(1,2);
    h.linkBoth(2,3);
    h.linkBoth(3,4);
    h.linkBoth(4,5);
    h.linkBoth(5,6);
    h.linkBoth(6,7);
    h.linkBoth(7,8);
    h.linkBoth(8,9);

    Graph j;
    j.addNodes(5);
    j.linkBoth(0,1);
    j.linkBoth(1,2);
    j.linkBoth(2,3);
    j.linkBoth(3,4);
    j.linkBoth(4,0);

    std::cout << "Is graph G bipartite ? : " << g.bipartiteGraph() << "\n";
    std::cout << "Is graph H bipartite ? : " << h.bipartiteGraph() << "\n";
    std::cout << "Is graph J bipartite ? : " << j.bipartiteGraph() << "\n";

    

    return 0;
}
