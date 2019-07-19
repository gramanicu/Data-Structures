#include "../headers/Graph.h"

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

    return 0;
}
