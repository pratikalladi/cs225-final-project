#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <sstream>
#include <fstream>
using namespace std;
typedef std::vector<std::vector<std::string> > V2D_strings;
typedef std::vector<std::vector<double> > V2D_numbers;  

//adjacency list implementation of a graph
class Graph {
    public:
        struct Node {
            string id;  //this is the unique id for each airports or abbreviation
            string name;
            int index = -1;
            double latitude = -1;
            double longitude = -1;
            string location_city; //this, if available tells people the general city an airport is int
            string location_country; //this, if available tells people the general country an airport is in


            ~Node() = default;
            Node() {}

            Node(string abbr, string name, int index, double latitude, double longitude, string location_city, string location_country) 
                : id(abbr), name(name), index(index), latitude(latitude), longitude(longitude), location_city(location_city), location_country(location_country)
            {}

            Node(string id) //simpler constructor mainly used for algorithm testing purposes
                : id(id) 
            {}

            void modifyIndex(int newIndex) {
                this->index = newIndex;
            }
        };

        struct Edge {
            Node *source;
            Node *dest; 

            
            double weight = -1; //this represents the distance between two nodes
            int airline_code; //stores the airline making this connection, as represented by the openflights code that can be converted into a string by the airlines database.

            Edge() {}

            ~Edge() = default;
            
            Edge(Node* n1, Node* n2, double weight) : source(n1), dest(n2), weight(weight) {
            }

            Edge(Node* n1, Node* n2, double weight, int airline_code) : source(n1), dest(n2), weight(weight), airline_code(airline_code) {
            }
        };

    
    private:
        unordered_map<string, vector<Edge*>> adjList;  //adjacency list in map: node id to . note that this is unordered and a hashmap, making lookup speed fast
        unordered_map<string, Node*> nodeMap; //map to nodes based on string id. note that this is unordered and a hashmap, making lookup speed fast
        vector<vector<Node*>> adjListVector; //adjacency list in vector form, where in each row, the first index represents a node, and then nodes that node is connected to

        unordered_map<string, vector<Node*>> cityToNodes; //map from a city location to nodes that represent airport(s) in a city
        unordered_map<int, string> airlinesMap; //map from a the number airline ids given in routes.dat to the actual airline name. This is basically a database of airlines.
        bool prcompare(pair<string, double> &p1, pair<string, double> &p2);
        


        //basic stats
        int nodeCount = 0; //number of nodes
        int edgeCount = 0; //number of edges

    public:
        //key modifiers
        void addNode(Node* n);
        void addEdge(Edge* e);

        //basic constructors/destructor
        Graph() = default;
        Graph(string airlines_path, string airports_path, string routes_path); //constructor to build a graph from openflights airline paths and initialize the airlines database.
        ~Graph();
        void print_graph(); //function to print the graph out used for debugging
        void construct_basic_graph(const V2D_strings &relations, const V2D_numbers &weights); //constructs an graph from a 2d vector of strings representing an adjacency list. Each row represents a node's connections, with the first element in each row being the actual node and the rest being nodes connected to it.  
                                                        //the graph's weights are added by accepting a 2d vector of doubles with the same number elements in each row, column, and in total, as the original input in construct_basic_graph, with the part that displayed the nodes connected being replaced by the numerical weights of the corresponding edges. The first index of each row is ignored.     

        //getters
        unordered_map<string, Node*> getNodeMap() { return nodeMap; };
        unordered_map<string, vector<Edge *>> getAdjList() { return adjList; }; //function to get the adjacency list
        unordered_map<string, vector<Node*>> getCityToNodes() { return cityToNodes; };
        vector<vector<Node*>> getAdjListVector () { return adjListVector; };
        unordered_map<int, string> getAirlinesMap() {return airlinesMap; };
        int getNodeCount() { return nodeCount;};
        int getEdgeCount() { return edgeCount;};
        vector<Edge*> getEdgeNeighbors(string input); //find edges to neighbors based on the string id
        vector<Node*> getNodeNeighbors(string input); //find neighboring nodes alone to neighbors based on the string id
        
        //algorithms
        double PageRankofNode(string node);
        std::vector<std::pair<std::string, int>> Graph::BFS(std::string src);
        vector<pair<string, double>> PageRank(string input);

        vector<string> dijkstra_A_find_shortest_path(string start, string end); //returns the vector of the shortest path between any two given nodes in terms of the node id and distance. only works for graphs with weighted edges with doubles. Implementation of Dijkstra and A* algorithm. The size of the vector returned equals the number of edges traveled. The vector always includes the end node if it is not equal to the start.
        double dijkstra_A_find_shortest_distance (string start, string end); //returns the shortest possible distance between two nodes using dijkstra's algorithm. Returns -1 if the end node cannot be found.
        unordered_map<string, double> general_dijkstra(string start); //returns the hashmap of shortest distances to every node in a connected graph from a source, represented as pair of the node id and distance. This is the classic dijkstra's algorithm.


        //helpers 

        double getDistance(Node* src, Node* dest);
        bool exists(string abbr);
        Node* getNode(string abbr);

};
typedef Graph::Edge Edge;
typedef Graph::Node Node;