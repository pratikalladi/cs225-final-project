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
        for (auto iter : getNodeNeighbors(current->name)) {//help fix this error. Dude look at the object you are currently on! Look at class definitions
            if (visited.at(iter->index) == false) {
                bfs.push(iter);
                visited.at(iter->index) = true;
            }
        }
        bfs.pop();
    }
    return result;
}