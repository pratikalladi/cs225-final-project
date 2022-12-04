#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits>
#include <sstream>
#include <fstream>
using namespace std;

//adjacency list implementation of a graph
class Graph {
    public:
        struct Node {
            int index;
            double latitude;
            double longitude;
            double fscore;
            string name;
            string abbr;
            Node() {

            }

            Node(int index, double latitude, double longitude, string name, string abbr) 
                : index(index), latitude(latitude), longitude(longitude), name(name), abbr(abbr) 
            {}


            void modifyIndex(int newIndex) {
                this->index = newIndex;
            }
        };

        struct Edge {
            Node *source;
            Node *dest;

            Edge() {}
            
            Edge(Node* n1, Node* n2) 
                : source(n1), dest(n2)
            {}
        };



    
    private:
        int adjSize;
        
        vector<vector<Edge *>> adjList;  
        vector<vector<int>> adjMatrix;  

    public:
        Graph();
        ~Graph();
        vector<Node*> all_node;  
        vector<vector<Graph::Edge *>> getAdjList();
        vector<vector<int>> getAdjMatrix();
        
        vector<Graph::Edge*> getNeighbors(Node* source); //added
        
        void addNode(Node* n);
        void addEdge(Edge* e);
        double distance(Node* src, Node* dest);
        void BFS(string src, string dest);

        double PageRankofNode(int o,vector<double> &p);

        double Win(int m,int o);
        double Wout(int m,int o);

        int edgeCount; 

        typedef struct Compare{
            bool operator()(const Node*node1, const Node*node2){
                return node1->fscore < node2->fscore;
            }
        } Comparator;
};