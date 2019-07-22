#include "../headers/Graph.h"

// Test graph functionality

int main() {
    Graph g;
    g.addNodes(13);
    g.linkBoth(0,1);
    g.linkBoth(0,3);
    g.linkBoth(0,5);
    g.linkBoth(1,2);
    g.linkBoth(1,3);
    g.linkBoth(1,4);
    g.linkBoth(2,4);
    g.linkBoth(2,7);
    g.linkBoth(3,5);
    g.linkBoth(3,6);
    g.linkBoth(4,6);
    g.linkBoth(4,7);
    g.linkBoth(5,8);
    g.linkBoth(5,10);
    g.linkBoth(6,8);
    g.linkBoth(6,9);
    g.linkBoth(7,9);
    g.linkBoth(7,12);
    g.linkBoth(8,10);
    g.linkBoth(8,11);
    g.linkBoth(9,11);
    g.linkBoth(9,12);
    g.linkBoth(10,11);
    g.linkBoth(11,12);

    std::cout << "Is graph G hamiltonian ? : " << g.isHamiltonian() << "\n";
    std::cout << "It has " << g.numberOfHCycles() << " cycles\n";

    Graph h;
    g.addNodes(4);

    std::cout << "Is graph H hamiltonian ? : " << h.isHamiltonian() << "\n";
    std::cout << "It has " << h.numberOfHCycles() << " cycles\n";

    return 0;
}
