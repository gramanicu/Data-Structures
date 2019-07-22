// Copyright 2019 Grama Nicolae
#ifndef GRAPH_H_
#define GRAPH_H_

/*  This is a implementation of a general graph. The links between
    nodes can be unidirectional or bidirectional (be carefull what
    method to use. Some give different results depending on the path
    direction). The connections are stored using a adjency list,
    as it is more memory efficient, especially for "sparse" graphs.
*/

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

/*  This is a "<<" operator overload for a list of integers, used by the
   "getPath" method.
*/
std::ostream& operator<<(std::ostream& output, const std::list<int>& list) {
    for (auto& i : list) {
        output << i << " ";
    }
    return output;
}

/*  This is a "<<" operator overload for a list of integers, used by the
    "topologicalSort" method.
*/
std::ostream& operator<<(std::ostream& output,
                         const std::vector<std::pair<int, int>>& vector) {
    for (auto& i : vector) {
        output << i.second << "(" << i.first << ") ";
    }
    return output;
}

class Graph {
   private:
    // The adjency list
    std::vector<std::list<std::pair<int, int>>> adjency;
    int nodeCount;  // The number of nodes in the graph

    // Comparision function for the topological sort
    static bool sortInRev(const std::pair<int, int>& a,
                          const std::pair<int, int>& b) {
        return (a.first > b.first);
    }

    // Algorithm to detect cylces (taken from www.geeksforgeeks.org)
    bool isCyclicUtil(const int n, bool visited[], bool* recStack) {
        if (!visited[n]) {
            visited[n] = true;
            recStack[n] = true;

            for (auto& i : adjency[n]) {
                if (!visited[i.first] &&
                    isCyclicUtil(i.first, visited, recStack)) {
                    return true;
                } else if (recStack[i.first]) {
                    return true;
                }
            }
        }
        recStack[n] = false;
        return false;
    }

    bool isCyclic() {
        bool* visited = new bool[nodeCount]();
        bool* recStack = new bool[nodeCount]();

        for (int i = 0; i < nodeCount; i++) {
            if (isCyclicUtil(i, visited, recStack)) {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recStack;
        return false;
    }

    /*  Dijkstra algorithm for finding the shortest path between two nodes.
        As it would need to return two values (the shortest path and the
       distance), which could cause confusion when using the class, this
       algorithm is declared as private, and there are two function "wrappers"
       that use it : "getPath" and "getDistance".
    */
    std::list<int> Dijkstra(uint first, uint second, uint* distance = 0) const {
        int* distances = new int[nodeCount]();
        bool* queued = new bool[nodeCount]();
        std::vector<std::list<int>> paths;

        for (int i = 0; i < nodeCount; i++) {
            distances[i] = 0;
            queued[i] = false;
            std::list<int> aux;
            aux.push_back(i);
            paths.push_back(aux);
        }

        std::queue<int> q;
        q.push(first);
        while (!q.empty()) {
            for (auto& i : adjency[q.front()]) {
                // Check if the node was queued
                if (!queued[i.first]) {
                    q.push(i.first);
                    queued[i.first] = true;
                }

                int newDist = distances[q.front()] + i.second;
                if ((distances[i.first] == 0 || distances[i.first] > newDist) &&
                    i.first != int(first)) {
                    distances[i.first] = newDist;
                    paths[i.first] = paths[q.front()];
                    paths[i.first].push_back(i.first);
                }
            }
            q.pop();
        }

        if (distance != nullptr) {
            *distance = distances[second];
        }

        delete[] distances;
        delete[] queued;
        return paths[second];
    }

   public:
    // Constructor
    Graph() : nodeCount(0) {}

    // Copy-Constructor
    Graph(const Graph& other) : nodeCount(other.nodeCount) {
        for (auto& i : other.adjency) {
            adjency.push_back(i);
        }
    }

    // Destructor
    ~Graph() {}

    // Adds the specified number of nodes
    void addNodes(const int count) {
        for (int i = 0; i < count; i++) {
            addNode();
        }
    }

    // Adds just one node
    void addNode() {
        std::list<std::pair<int, int>> add;
        adjency.push_back(add);
        nodeCount++;
    }

    // Creates a path from the first node to the second, of the specified
    // distance
    void link(const uint first, const uint second, const uint distance = 1) {
        if (distance == 0) return;

        if (first != second && first < uint(nodeCount) &&
            second < uint(nodeCount)) {
            // Check if the link exist (if true, just update the distance)
            for (auto& i : adjency[first]) {
                if (i.first == int(second)) {
                    i.second = distance;
                    return;
                }
            }

            adjency[first].push_back(std::make_pair(second, distance));
        }
    }

    // Creates a path between two nodes, of the specified distance
    void linkBoth(const uint first, const uint second,
                  const uint distance = 1) {
        link(first, second, distance);
        link(second, first, distance);
    }

    // Removes the path from the first node to the second
    void unlink(const uint first, const uint second) {
        std::list<std::pair<int, int>>::iterator it;
        for (it = adjency[first].begin(); it != adjency[first].end(); ++it) {
            if ((*it).first == int(second)) {
                adjency[first].erase(it);
                break;
            }
        }
    }

    // Removes the path between the nodes
    void unlinkBoth(const uint first, const uint second) {
        unlink(first, second);
        if (isLink(second, first)) {
            unlink(second, first);
        }
    }

    /*  This is the closest way you can get to removing a node. It
        will remove all paths to and from it.

        A function to properly remove a node can't be implemented,
        as it would greatly increase the complexity and memory footprint
        of the graph. (ex.: removing one node would need to change all the
        other nodes numbers. As this would be very difficult to keep track of,
        the nodes should be accessible by a "alias", which would need probably
        a hashtable for fast access, and so on)
    */
    void removeAllLinks(const uint node) {
        for (int i = 0; i < nodeCount; i++) {
            if (i != int(node)) {
                unlinkBoth(node, i);
            }
        }
    }

    // Checks if there is a path from the first node to the second
    bool isLink(const uint first, const uint second) const {
        if (first == second) {
            return true;
        }

        for (auto& i : adjency[first]) {
            if (i.first == int(second)) {
                return true;
            }
        }
        return false;
    }

    // Checks if two nodes are linked
    bool isLinkBoth(const uint first, const uint second) const {
        return (isLink(first, second) && isLink(second, first));
    }

    // Returns the number of nodes in the graph
    int nodesCount() const { return nodeCount; }

    // Returns the shortest path from the first node to the second (the
    // output has the following format "n1 n2 n3 ... ", with a space at the end)
    // If there is no path, it will return -1
    std::list<int> getPath(const uint first, const uint second) const {
        if (first == second) {
            std::list<int> p;
            p.push_back(first);
            return p;
        }
        std::list<int> path = Dijkstra(first, second);
        if (path.size() == 1) {
            std::list<int> p;
            p.push_back(-1);
            return p;
        } else {
            return path;
        }
    }

    // Returns the minimal distance between two nodes (and -1 if there is none)
    int getDistance(const uint first, const uint second) const {
        if (first == second) {
            return 0;
        }
        uint distance = 0;
        Dijkstra(first, second, &distance);
        if (distance == 0) {
            return -1;
        }
        return int(distance);
    }

    /*  Returns the number of connected components
        Connected components are subgraphs made only with nodes
        that can be reached from one another (a path exists)
    */
    int connectedComponents() const {
        int connected = 0;
        bool* visited = new bool[nodeCount]();

        // Go through each node in the graph
        for (int i = 0; i < nodeCount; i++) {
            if (!visited[i]) {
                connected++;
                // Start a dfs from the current node
                std::stack<int> s;

                // Visit the node
                visited[i] = true;
                s.push(i);

                // DFS
                while (!s.empty()) {
                    int topNode = s.top();
                    int neighbor = -1;

                    // Search for the first unvisited neighbor
                    for (auto& j : adjency[topNode]) {
                        if (!visited[j.first]) {
                            neighbor = j.first;
                            break;
                        }
                    }

                    // If there is a neighbor
                    if (neighbor != -1) {
                        visited[neighbor] = true;
                        s.push(neighbor);
                    } else {
                        s.pop();
                    }
                }
            }
        }

        delete[] visited;
        return connected;
    }

    /*  By doing a topological sort, we linearise the graph. By starting in the
        first node of the topologically sorted graph, we can go through all of it
        without ever repeating a node (no returns, we move in 1 direction).
    */
    void topologicalSort() {
        // If there is one cycle in the graph, it can't be sorted topologically
        if (isCyclic()) {
            return;
        } else {
            bool* visited = new bool[nodeCount]();
            int* parent = new int[nodeCount]();
            int* dTime = new int[nodeCount]();
            std::vector<int> fTime;
            int tCount = 0;

            for (int i = 0; i < nodeCount; i++) {
                fTime.push_back(int());
            }

            // For each node in graph
            for (int i = 0; i < nodeCount; i++) {
                // If the node wasn't visited already, do a DFS from it
                if (!visited[i]) {
                    std::stack<int> s;
                    s.push(i);

                    // Visit node
                    tCount++;
                    dTime[i] = tCount;
                    visited[i] = true;

                    // While the stack isn't empty
                    while (!s.empty()) {
                        int topNode = s.top();
                        int neighbor = -1;

                        for (auto& j : adjency[topNode]) {
                            if (!visited[j.first]) {
                                neighbor = j.first;
                                break;
                            }
                        }

                        // If there is a unvisited neighbor
                        if (neighbor != -1) {
                            parent[neighbor] = topNode;
                            // Visit the node
                            tCount++;
                            dTime[neighbor] = tCount;
                            visited[neighbor] = true;
                            s.push(neighbor);
                        } else {
                            tCount++;
                            fTime[topNode] = tCount;
                            s.pop();
                        }
                    }
                }
            }

            std::vector<std::pair<int, int>> finalOrder;
            int count = 0;
            for (auto& i : fTime) {
                finalOrder.push_back(std::make_pair(i, count));
                count++;
            }

            std::sort(finalOrder.begin(), finalOrder.end(), sortInRev);
            std::cout << "Graph in topological order is :\n"
                      << finalOrder << "\n\n";

            delete[] visited;
            delete[] parent;
            delete[] dTime;
        }
    }

    /*  Checks if the graph is bipartite
        This is done by starting a BFS in a node (0 in this case), and give
        each encountered node a level (1 greater than the "parent"). In this
        case, we just keep count if they are odd or even. If we find two
        connected nodes that are both even/odd, the graph is not bipartite.
        If we finish the BFS without encountering this situation, the graph
        is bipartite.
    */
    bool bipartiteGraph() {
        int source = 0;
        int *level = new int[nodeCount](); // 2 - odd, 1 - even, 0 - undefined
        bool *visited = new bool[nodeCount]();

        std::queue<int> q;
        q.push(source);

        // BFS
        while(!q.empty()) {
            int n = q.front();
            visited[n] = true;
            q.pop();

            for(auto& i : adjency[n]) {
                if(level[i.first] == 0) {
                    // If the "n" node is odd, his neighbors are even etc.
                    level[i.first] = (level[n] == 2) ? 1 : 2;
                    q.push(i.first);
                } else if (level[n] == level[i.first]) {
                    // If two consecutive nodes have the same level, not bipartite
                    return false;
                }
            }
        }
 
        delete[] level;
        delete[] visited;
        return true; 
    }

    // Checks if the graph is hamiltonian
    bool hamiltonianGraph() { return false; }

    /*  Operator overload for output. It will print the adjency MATRIX of the
       graph. Be carefull using this function, as it uses a lot of resources.
       For a graph of 1000 nodes it can use approximately 4GB of RAM.
    */
    friend std::ostream& operator<<(std::ostream& output, const Graph& g) {
        int size = g.nodeCount;
        int** adjencyMatrix = new int*[size];

        // Initialise the matrix
        for (int i = 0; i < g.nodeCount; i++) {
            adjencyMatrix[i] = new int[size]();
        }

        // Move the data from the adjency list to the matrix
        int cRow = 0;
        for (auto& i : g.adjency) {
            for (auto& j : i) {
                adjencyMatrix[cRow][j.first] = j.second;
            }
            cRow++;
        }

        // Print the matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                output << adjencyMatrix[i][j] << " ";
            }
            output << "\n";
        }

        // Free the memory used
        for (int i = 0; i < size; i++) {
            delete[] adjencyMatrix[i];
        }
        delete[] adjencyMatrix;

        return output;
    }
};

#endif  // GRAPH_H_