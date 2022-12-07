/**
 * @file BFS.cpp
 * For BFS
 */
#include "BFS.h"
#include "graph.h"
std::vector<std::string> BFS(Graph::Node* source, Graph::Node* destination) {
    std::vector<std::string> result;
    std::vector<bool> visited(14111, false);
    std::queue<Graph::Node*> bfs;
    bfs.push(source);
    Graph::Node* current = source;
    visited.at(current->index) = true;
    while (!bfs.empty()) {
        current = bfs.front();
        result.push_back(current->name);
        for (auto iter : getNodeNeighbors(current->name)) {//help fix this error pls
            if (visited.at(iter->index) == false) {
                bfs.push(iter);
                visited.at(iter->index) = true;
            }
        }
        bfs.pop();
    }
    return result;
}
/*
std::vector<std::string> BFS(int origin_airport) {
    std::vector<std::string> result;
    std::vector<bool> visited(14111, false);
    std::queue<int> bfs;
    bfs.push(origin_airport);
    int current_airport = origin_airport;
    visited.at(current_airport) true;
    while (!bfs.empty()) {
        current_airport = bfs.front();
        result.push_back(name);
        for (auto iter : graph of all flights that originate at current_airport) {
            if (visited.at(iter.first) == false) {
                bfs.push(iter.first);
                visited.at(iter.first) = true;
            }
        }
        bfs.pop();
    }
    return result;
}
*/