#define _USE_MATH_DEFINES

#include <cmath>
#include "graph.h"
#include<bits/stdc++.h>
using namespace std;


Graph::~Graph() {
    //delete all allocated nodes
    for (auto const &pair: nodeMap) {
        Node* to_delete = pair.second;
        delete to_delete;
        to_delete = nullptr;
    } 

    //delete all allocated edges
    for(auto pair: adjList) {
        for(Edge * e: pair.second) {
            Edge* to_delete = e;
            delete to_delete;
            to_delete = nullptr;
        }
    }
};

void Graph::addNode(Node* n) {
    if(adjList.size() != adjListVector.size()) { cout << "insertion error!" << endl; return; }; 
    if(nodeMap.find(n->id) != nodeMap.end()) {  //if node name already exists, do not allow
        cout << "insertion error!" << endl; 
        cout << "node ids must be unique!" << endl << endl; 
        cout << "node with id: " <<  n->id << ", already exists" << endl;
        return;
    } 
    n->index = adjList.size();

    vector<Node*> new_nlist;
    new_nlist.push_back(n); 
    adjListVector.push_back(new_nlist); //insert into the index based adjacency list

    vector<Edge *> new_elist; 
    adjList.insert({n->id, new_elist});

    nodeMap.insert({n->id, n}); //insert into the node map
    
    nodeCount++;
}

void Graph::addEdge(Edge* e) {
    if(e->source->id == e->dest->id) { //do not allow self-loops
        delete e;
        return;
    }

    adjList[e->source->id].push_back(e); //map find
    edgeCount++;

    adjListVector[e->source->index].push_back(e->dest);
    //e->weight = distance(e->source, e->dest);
}

//function to print out the graph's basic structure and edge weights
void Graph::print_graph() {   
    cout <<"printing graph structure" << endl;
    //prints out each node and its neighbors

    //for cases when graph is not weighted
    for(unsigned int j = 0; j < adjListVector.size(); j++) { 
        //find the node based on the index alone
        Node* current_node = adjListVector[j][0];
        string node_id = current_node->id; //find the node id
        cout << "node: " << node_id << ", neighbor(s): ";
        vector<Edge*> edges = adjList[node_id];
        for(unsigned int i = 0; i < edges.size(); i++) {
            double n_weight = edges[i]->weight;
                
            cout << edges[i]->dest->id << "(" << n_weight << ")" <<", "; 

        }
        cout << endl;
    }
    cout << endl;
} 

//constructs graph. This is used for test purposes. The string relations are the node ids
void Graph::construct_basic_graph(const V2D_strings &relations, const V2D_numbers &weights) {
    for(unsigned int j = 0; j < relations.size(); j++) { 
        vector<string> related_classes = relations[j];

        string node_source = related_classes[0]; //the first will always be the new
        Node* source_node = new Node(node_source);
        addNode(source_node); //add node   
    }
    //then, iterate only among the edges, while keeping track of the source node
    for(unsigned int j = 0; j < relations.size(); j++) { 
        vector<string> related_classes = relations[j];
        string node_source = related_classes[0];
        Node* source_node = nodeMap[node_source];

        for(unsigned int i = 1; i < related_classes.size(); i++) { 
            string node_end = related_classes[i];
            
            //only add the edge if the end is a valid node
            if(nodeMap.count(node_end) != 0) {
                Node* end_node = nodeMap[node_end];
                
                Edge* new_edge = new Edge(source_node, end_node, weights[j][i]); //create and add a new edge
                addEdge(new_edge);
            }
        }
    }
} //constructs an graph from a 2d vector of strings representing an adjacency list. Each row represents a node's connections, with the first element in each row being the actual node and the rest being nodes connected to it.  

bool Graph::exists(string abbr) { //checks if the id is already present
    if(nodeMap.count(abbr) == 0) {
        return false;
    }
    return true;
}

double Graph::getDistance(Node* src, Node* dest){
    long double source_long_rad = (src->longitude)/(180.0/57.29577951); //j\hard code 180/pi
    long double source_lat_rad = (src->latitude)/(180.0/57.29577951); 
    long double dest_long_rad = (dest->longitude)/(180.0 /57.29577951);
    long double dest_lat_rad = (dest->latitude)/(180.0/57.29577951);

    long double latdiff = dest_lat_rad - source_lat_rad;
    long double longdiff = dest_long_rad - source_long_rad;
    long double adder = pow(sin(latdiff / 2.0), 2) + cos(source_lat_rad) * cos(dest_lat_rad) * pow(sin(longdiff / 2.0), 2);
    
    long double halfway = 2 * asin(sqrt(adder)); 
    long double dist_out = abs(6371.0 * halfway); //to make km instead of miles

    //take absolute value to be safe - no need, we square the number.
    return dist_out;
}


std::vector<std::string> Graph::BFS(Graph::Node* source) {
    std::vector<std::string> result;
    std::vector<bool> visited(14111, false);
    std::queue<Graph::Node*> bfs;
    bfs.push(source);
    Graph::Node* current = source;
    visited.at(current->index) = true;
    while (!bfs.empty()) {
        current = bfs.front();
        result.push_back(current->id);
        for (auto iter : getNodeNeighbors(current->id)) {
            if (visited.at(iter->index) == false) {
                bfs.push(iter);
                visited.at(iter->index) = true;
            }
        }
        bfs.pop();
    }
    return result;
}

//adapt code
/* double Graph :: Win(int m,int o){
    int k = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[i][m] != INT_MAX){
            k++;
        }
    }
    int l = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[o][i] != INT_MAX){
            for(int j=0;j<adjSize;j++){
                if(adjMatrix[j][i] != INT_MAX){
                    l++;
                }
            }
        }
    }
    return (double)k/(double)l;
}


double Graph :: Wout(int m,int o){
    int k = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[0][i] != INT_MAX){
            k++;
        }
    }
    int l = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[o][i] != INT_MAX){
            for(int j=0;j<adjSize;j++){
                if(adjMatrix[i][j] != INT_MAX){
                    l++;
                }
            }
        }
    }
    return (double)k/(double)l;
} */

//adapt code
/* double Graph :: PageRankofNode(int o,vector<double> &p){
    double a = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[i][o] != INT_MAX){
            int k = 0;
            for(int s=0;s<adjSize;s++){
                if(adjMatrix[i][s] != INT_MAX){
                    k++;
                }
            }
            a += ((double)p[i]/k) * Win(i,o) * Wout(i,o);
        }
    }
    return a;
} */

Graph::Node* Graph::getNode(string abbr){
    return nodeMap[abbr];

}

//function to get a list of all neighbors
vector<Edge*> Graph::getEdgeNeighbors(string input) {
    return adjList[input];
}

vector<Node*> Graph::getNodeNeighbors(string input) {
    vector<Edge*> edges = adjList[input];
    vector<Node*> to_return;
    for (Edge* edge : edges) {
        to_return.push_back(edge->dest);
    }
    return to_return;
}

//returns the vector of the shortest path between any two given nodes in terms of the node id and distance. only works for graphs with weighted edges with doubles.  
vector<string> Graph::dijkstra_A_find_shortest_path(string start, string end) { 
    vector<string> to_return; //represents the optimal path taken

    //check if this graph is a valid, weighted graph
    if(nodeMap.count(start) == 0 || nodeMap.count(end) == 0) {cout << "the starting or end points do not exist for this graph" <<endl; return to_return;}

    //naive implementation : this implementation is faster for much larger datasets
    unordered_map<string, double> distances; //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    priority_queue<pair<double, string>> nodes_by_distance; //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
    
    unordered_map<string, string> parents; //stores the parents nodes in order to keep track of the path. Its a map from the one node to the parents

    distances.insert({start, 0}); //intialize starting distance
    nodes_by_distance.push({0 ,start}); //special case for first node
    parents.insert({start, start});//the parent of the source is itself

    bool node_found = false;
    while(!nodes_by_distance.empty()) { //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
        string min_node = nodes_by_distance.top().second;  //find the minimum distance vertex
        nodes_by_distance.pop(); //remove the visited node
        
        if(min_node == end) {                //stop algorithm if the node has been found
            node_found = true; //set this to be true 
            break; //end the loop
        }
            
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);
        for(Edge* e : neighbor_connections) {
            string neighbor = e->dest->id; 
            double curr_distance = distances[min_node] + e->weight; //distance to source based on addition
            
            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below
            if(distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) { //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
                distances[neighbor] = curr_distance; //else if the new distance is shorter or new, change this
                nodes_by_distance.push({curr_distance * -1, neighbor});   //do this to get the effects of a min-heap so that the sorted is reversed
                //cout << "neighbor changed: " << neighbor << " to " << min_node<< endl;
                parents[neighbor] = min_node; 
            }
        }
    }
    if (node_found == false) { //if the node has not been found
        cout << "the destination could not be found likely because the destination is not connected in any way to the source" << endl; //if the destination does not end up being found
        return to_return;
    } 

    //populate the path vector iteratively until the source node is reached
    
    //insert the end node if it does not equal start
    if(end != start) {
        to_return.insert(to_return.begin(), end);
    }
    string current_value = parents[end];  //set to the start
    while(current_value != start) {
        to_return.insert(to_return.begin(), current_value); //insert at front
        current_value = parents[current_value];
    }
    return to_return;
}

double Graph::dijkstra_A_find_shortest_distance (string start, string end) { //returns the shortest possible distance between two nodes
    if(nodeMap.count(start) == 0 || nodeMap.count(end) == 0) {cout << "the starting or end points do not exist for this graph" <<endl; return -1;}

    //naive implementation : this implementation is faster for much larger datasets
    unordered_map<string, double> distances; //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    priority_queue<pair<double, string>> nodes_by_distance; //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
     
    distances.insert({start, 0}); //intialize starting distance
    nodes_by_distance.push({0 ,start}); //special case for first node

    while(!nodes_by_distance.empty()) { //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
        string min_node = nodes_by_distance.top().second;  //find the minimum distance vertex
        nodes_by_distance.pop(); //remove the visited node
        
        if(min_node == end) {                //stop algorithm if the node has been found
            return distances[end]; 
        }
            
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);
        for(Edge* e : neighbor_connections) {
            string neighbor = e->dest->id; 
            double curr_distance = distances[min_node] + e->weight; //distance to source based on addition

            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below
            if(distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) { //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
                distances[neighbor] = curr_distance; //else if the new distance is shorter or new, change this. //this operator also inserts a new key if the key did not already exist
                nodes_by_distance.push({curr_distance * -1, neighbor});   //do this to get the effects of a min-heap so that the sorted is reversed.
            }
        }
    }

    cout << "the destination could not be found likely because the destination is not connected in any way to the source" << endl; //if the destination does not end up being found
    return -1;
}

//returns the hashmap of shortest distances to every node in a connected graph from a source, represented as pair of the node id and distance. This is the classic dijkstra's algorithm.
unordered_map<string, double> Graph::general_dijkstra(string start) { 
    if(nodeMap.count(start) == 0) {cout << "the starting point does not exist for this graph" <<endl; return unordered_map<string, double>(); }

    //naive implementation : this implementation is faster for much larger datasets
    unordered_map<string, double> distances; //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    priority_queue<pair<double, string>> nodes_by_distance; //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
     
    distances.insert({start, 0}); //intialize starting distance
    nodes_by_distance.push({0 ,start}); //special case for first node

    while(!nodes_by_distance.empty()) { //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
        string min_node = nodes_by_distance.top().second;  //find the minimum distance vertex
        nodes_by_distance.pop(); //remove the visited node
        
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);
        for(Edge* e : neighbor_connections) {
            string neighbor = e->dest->id; 
            double curr_distance = distances[min_node] + e->weight; //distance to source based on addition

            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below
            if(distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) { //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
                distances[neighbor] = curr_distance; //else if the new distance is shorter or new, change this. //this operator also inserts a new key if the key did not already exist
                nodes_by_distance.push({curr_distance * -1, neighbor});   //do this to get the effects of a min-heap so that the sorted is reversed.
            }
        }
    }

    return distances;
}