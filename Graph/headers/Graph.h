// Copyright 2019 Grama Nicolae
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <queue>
#include <vector>

std::ostream& operator<<(std::ostream& output, const std::list<int>& list) {
    for (auto& i : list) {
        output << i << " ";
    }
    return output;
}

class Graph {
   private:
    std::vector<std::list<std::pair<int, int>>> adjency;
    int nodeCount;

    // Dijkstra algorithm for finding the shortest path
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

        if(distance!=nullptr) {
            *distance = distances[second];
        }

        delete[] distances;
        delete[] queued;
        return paths[second];
    }

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
        for (int i = 0; i < nodeCount; i++) {
            if (i != int(node)) {
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

    std::list<int> getPath(const uint first, const uint second) const {
        if(first == second) {
            std::list<int> p;
            p.push_back(first);
            return p;
        }
        return Dijkstra(first, second);
    }

    int getDistance(const uint first, const uint second) const {
        if(first == second) {
            return 0;
        }
        uint distance = 0;
        Dijkstra(first, second, &distance);
        return int(distance);
    }

    int connectedComponents() const { return 0; }

    void topologicalSort() {
        // If there is one cycle in the graph, it can't be sorted topologically
    }

    bool bipartiteGraph() { return false; }

    bool hamiltonianGraph() { return false; }

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