#include "../headers/Graph.h"

// Test graph functionality

int main() {
    Graph g;
    g.addNodes(8);
    g.linkBoth(1, 2, 7);
    g.linkBoth(1, 3, 9);
    g.linkBoth(1, 6, 14);
    g.linkBoth(2, 3, 10);
    g.linkBoth(2, 4, 15);
    g.linkBoth(3, 4, 11);
    g.linkBoth(3, 6, 2);
    g.linkBoth(4, 5, 6);
    g.linkBoth(5, 6, 9);

    std::cout << g << "\n";
    std::cout << "Shortest path from 1 to 5 is : " << g.getPath(1, 5)
              << " with the length of " << g.getDistance(1, 5) << "\n";

    Graph other = g;
    
    std::cout << other << "\n";
    std::cout << "Shortest path from 1 to 5 is : " << other.getPath(1, 5)
              << " with the length of " << other.getDistance(1, 5) << "\n";

    g.removeAllLinks(1);
    g.removeAllLinks(2);
    g.removeAllLinks(3);
    g.removeAllLinks(4);
    g.removeAllLinks(5);
    g.removeAllLinks(6);

    std::cout << g << "\n";
    std::cout << "Shortest path from 1 to 5 is : " << g.getPath(1, 5)
              << " with the length of " << g.getDistance(1, 5) << "\n";
    
    std::cout << other << "\n";
    std::cout << "Shortest path from 1 to 5 is : " << other.getPath(1, 5)
              << " with the length of " << other.getDistance(1, 5) << "\n";

    std::cout << "\nThe second time we print Graph g, we should find no path\n";
    std::cout << "However, the Graph other should remain unchanged\n";

    return 0;
}
