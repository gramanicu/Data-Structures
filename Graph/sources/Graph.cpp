#include "../headers/Graph.h"

int main() {
    Graph g;
    g.addNodes(3);
    g.link(1, 0);
    g.linkBoth(1, 2);
    g.linkBoth(0, 2);

    std::cout << "\nThe adjency matrix is : \n" << g << "\n";

    std::cout << "Is link 0 -> 1 ? " << g.isLink(0, 1) << "\n";
    std::cout << "Is link 0 -> 2 ? " << g.isLink(0, 2) << "\n";
    std::cout << "Is link 1 -> 0 ? " << g.isLink(1, 0) << "\n";
    std::cout << "Is link 1 -> 2 ? " << g.isLink(1, 2) << "\n";
    std::cout << "Is link 2 <-> 1 ? " << g.isLinkBoth(2, 1) << "\n";
    std::cout << "Is link 1 <-> 2 ? " << g.isLinkBoth(1, 2) << "\n";
    std::cout << "Is link 0 <-> 2 ? " << g.isLinkBoth(0, 2) << "\n";

    g.link(0, 1);
    std::cout << "\nThe adjency matrix is : \n" << g << "\n";

    std::cout << "Is link 0 -> 1 ? " << g.isLink(0, 1) << "\n";
    std::cout << "Is link 1 -> 0 ? " << g.isLink(1, 0) << "\n";
    std::cout << "Is link 0 <-> 1 ? " << g.isLink(0, 1) << "\n";
    std::cout << "Is link 1 -> 1 ? " << g.isLink(1, 1) << "\n";
    std::cout << "Is link 1 <-> 1 ? " << g.isLinkBoth(1, 1) << "\n";

    return 0;
}
