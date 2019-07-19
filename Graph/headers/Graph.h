// Copyright 2019 Grama Nicolae
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <vector>

class Graph {
   private:
    std::vector<std::list<std::pair<int, int>>> adjency;
    int nodeCount;

   public:
    Graph() : nodeCount(0) {}
    Graph(const Graph& other) {}
    ~Graph() {}

    void addNodes(const int count) {
        for (int i = 0; i < count; i++) {
            addNode();
        }
    }

    void addNode() {
        std::list<std::pair<int, int>> add;
        adjency.push_back(add);
        nodeCount++;
    }

    void link(const uint first, const uint second, const uint distance = 1) {
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

    void linkBoth(const uint first, const uint second,
                  const uint distance = 1) {
        link(first, second, distance);
        link(second, first, distance);
    }

    void unlink(const uint first, const uint second) {
        std::list<std::pair<int, int>>::iterator it;
        for (it = adjency[first].begin(); it != adjency[first].end(); ++it) {
            if ((*it).first == int(second)) {
                adjency[first].erase(it);
                break;
            }
        }
    }

    void unlinkBoth(const uint first, const uint second) {
        unlink(first, second);
        if (isLink(second, first)) {
            unlink(second, first);
        }
    }

    void removeAllLinks(const uint node) {
        for(int i = 0 ; i < nodeCount; i++) {
            if(i != int(node)) {
                unlinkBoth(node, i);
            }
        }
    }

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

    bool isLinkBoth(const uint first, const uint second) const {
        return (isLink(first, second) && isLink(second, first));
    }

    int nodesCount() const { return nodeCount; }

    // Dijkstra algorithm for finding the shortest path
    int distance(uint first, uint second) const {
        return 0;
    } 

    int connectedComponents() {
        return 0;
    }

    void topologicalSort() {
        // If there is one cycle in the graph, it can't be sorted topologically
    }

    bool bipartiteGraph() {
        return false;
    }

    bool hamiltonianGraph() {
        return false;
    }

    friend std::ostream& operator<<(std::ostream& output, const Graph& g) {
        int size = g.nodeCount;
        int** adjencyMatrix = new int*[size];
        for (int i = 0; i < g.nodeCount; i++) {
            adjencyMatrix[i] = new int[size]();
        }

        int cRow = 0;
        for (auto& i : g.adjency) {
            for (auto& j : i) {
                adjencyMatrix[cRow][j.first] = j.second;
            }
            cRow++;
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                output << adjencyMatrix[i][j] << " ";
            }
            output << "\n";
        }

        for (int i = 0; i < size; i++) {
            delete[] adjencyMatrix[i];
        }
        delete[] adjencyMatrix;

        return output;
    }
};

#endif  // GRAPH_H_