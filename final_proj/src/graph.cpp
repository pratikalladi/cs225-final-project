#define _USE_MATH_DEFINES
#include <cmath>
#include "graph.h"
#include "ScanGraph.h"
#include <fstream>
using namespace std;

//constructor to build a graph from openflights airline paths and initialize the airlines database
Graph::Graph(string airlines_path, string airports_path, string routes_path) {

    //scan in the airline database
    ifstream airlines{airlines_path};
    unordered_map<int, string> local;
    string line, tmp;

    if (airlines.is_open()) {
        while (getline(airlines, line)) {

            //from mp schedule SplitString()
            vector<string> vec;
            char sep = ',';
            std::string::size_type pos;

            while ((pos = line.find(sep)) != std::string::npos) {
                vec.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);  
            }

            vec.push_back(line);

            //airline name  
            string airline_name = vec[1];

            //remove parentheses and quotation marks
            airline_name = airline_name.substr(1, airline_name.size() - 2);

            //check if string is number before assigning
            int code = std::stoi(vec[0]);
            airlinesMap.insert({code, airline_name});
        }
    }

    //scan in the routes and rest
    ScanGraph sg;
    sg.scanCSV(this, airports_path, routes_path); 
} 

Graph::~Graph() {

    //delete all allocated nodes
    for (auto const &pair: nodeMap) {
        Node* to_delete = pair.second;
        delete to_delete;
        to_delete = nullptr;
    } 

    //delete all allocated edges
    for (auto pair: adjList) {
        for (Edge * e: pair.second) {
            Edge* to_delete = e;
            delete to_delete;
            to_delete = nullptr;
        }
    }
};

void Graph::addNode(Node* n) {
    if (adjList.size() != adjListVector.size()) {
        cout << "insertion error!" << endl;
        return;
    };

    //if node name already exists, do not allow
    if (nodeMap.find(n->id) != nodeMap.end()) {
        cout << "insertion error!" << endl; 
        cout << "node ids must be unique!" << endl << endl; 
        cout << "node with id: " << n->id << ", already exists" << endl;
        return;
    } 

    n->index = adjList.size();
    vector<Node*> new_nlist;
    new_nlist.push_back(n);

    //insert into the index based adjacency list
    adjListVector.push_back(new_nlist);

    //insert into the to map of cities to nodes

    //if new, do something else
    if (cityToNodes.count(n->location_city) == 0) {
        vector<Node*> new_city_list;
        new_city_list.push_back(n);
        cityToNodes.insert({n->location_city, new_city_list});
    } else { //else, push back
        cityToNodes[n->location_city].push_back(n);
    }

    vector<Edge *> new_elist; 
    adjList.insert({n->id, new_elist});

    //insert into the node map
    nodeMap.insert({n->id, n});
    nodeCount++;
}

void Graph::addEdge(Edge* e) {

    //do not allow self-loops
    if (e->source->id == e->dest->id) {
        delete e;
        return;
    }

    //map find
    adjList[e->source->id].push_back(e);
    edgeCount++;
    adjListVector[e->source->index].push_back(e->dest);
    //e->weight = distance(e->source, e->dest);
}

//function to print out the graph's basic structure and edge weights
void Graph::print_graph() {

    //prints out each node and its neighbors  
    cout << "printing graph structure" << endl;
    
    //for cases when graph is not weighted
    for (unsigned int j = 0; j < adjListVector.size(); j++) {

        //find the node based on the index alone
        Node* current_node = adjListVector[j][0];

        //find the node id
        string node_id = current_node->id;
        cout << "node: " << node_id << ", neighbor(s): ";
        vector<Edge*> edges = adjList[node_id];

        for (unsigned int i = 0; i < edges.size(); i++) {
            double n_weight = edges[i]->weight;
            cout << edges[i]->dest->id << "(" << n_weight << ")" << ", "; 
        }

        cout << endl;
    }

    cout << endl;
} 

//constructs graph. This is used for test purposes. The string relations are the node ids
void Graph::construct_basic_graph(const V2D_strings &relations, const V2D_numbers &weights) {
    for (unsigned int j = 0; j < relations.size(); j++) { 
        vector<string> related_classes = relations[j];

        //the first will always be the new
        string node_source = related_classes[0];
        Node* source_node = new Node(node_source);

        //add node  
        addNode(source_node); 
    }

    //then, iterate only among the edges, while keeping track of the source node
    for (unsigned int j = 0; j < relations.size(); j++) { 
        vector<string> related_classes = relations[j];
        string node_source = related_classes[0];
        Node* source_node = nodeMap[node_source];

        for (unsigned int i = 1; i < related_classes.size(); i++) { 
            string node_end = related_classes[i];
            
            //only add the edge if the end is a valid node
            if (nodeMap.count(node_end) != 0) {
                Node* end_node = nodeMap[node_end];

                //create and add a new edge
                Edge* new_edge = new Edge(source_node, end_node, weights[j][i]);
                addEdge(new_edge);
            }
        }
    }
}
//constructs an graph from a 2d vector of strings representing an adjacency list. Each row represents a node's connections, with the first element in each row being the actual node and the rest being nodes connected to it.  

//checks if the id is already present
bool Graph::exists(string abbr) {
    if (nodeMap.count(abbr) == 0) {
        return false;
    }
    return true;
}


//CITATION: adapted from Geeks4Geeks Haversine Formula guide
// https://www.geeksforgeeks.org/program-distance-two-points-earth/
double Graph::getDistance(Node* src, Node* dest) {
    long double radian_conversion = M_PI /180.0;

    //j\hard code 180/pi
    long double source_long_rad = (src->longitude) * radian_conversion;
    long double source_lat_rad = (src->latitude) * radian_conversion; 
    long double dest_long_rad = (dest->longitude) * radian_conversion;
    long double dest_lat_rad = (dest->latitude) * radian_conversion;

    long double latdiff = dest_lat_rad - source_lat_rad;
    long double longdiff = dest_long_rad - source_long_rad;
    long double adder = pow(sin(latdiff / 2.0), 2) + cos(source_lat_rad) * cos(dest_lat_rad) * pow(sin(longdiff / 2.0), 2);
    
    long double halfway = 2 * asin(sqrt(adder));

    //to make km instead of miles 
    long double dist_out = abs(6371.0 * halfway);

    //take absolute value to be safe - no need, we square the number.
    return dist_out;
}

vector<pair<int, string>> Graph::BFS(string src) {
    Node* source = nodeMap[src];
    vector<pair<int, string>> result;
    vector<bool> visited(nodeMap.size(), false);
    queue<Node*> bfs;
    bfs.push(source);
    Node* current = source;
    visited.at(current->index) = true;
    int hops = 0;

    //keep track of last node in level
    auto x = bfs.back();

    while (!bfs.empty()) {
        current = bfs.front();
        pair<int, std::string> temp(hops, current->id);
        result.push_back(temp);

        for (auto iter : getNodeNeighbors(current->id)) {
            if (visited.at(iter->index) == false) {
                bfs.push(iter);
                visited.at(iter->index) = true;
            }
        }

        //increase level by one once last node from previous level is popped from queue
        if (x == bfs.front()) {
            x = bfs.back();
            hops++;
        }

        bfs.pop();
    }

    return result;
}

//version of BFS that only finds the list of nodes that are a certain amount of edges (hops) from the source. Better for runtime in cases where all nodes for example, that are at most two edges from the source.
vector<pair<int, string>> Graph::BFS(string src, unsigned int limit) {
    vector<pair<int, string>> result;
    Node* source = nodeMap[src];

    //if a node's index is visited, it will be present in this set
    vector<bool> visited(nodeMap.size(), false);
    queue<Node*> bfs;
    bfs.push(source);
    Node* current = source;

    //insert int
    visited[current->index] = true;
    unsigned int hops = 0;
    auto x = bfs.back();

    while (!bfs.empty()) {
        current = bfs.front();

        if (hops > limit) {
            return result;
        } else if (hops == limit) {

            //append only if the number of hops is the same as the limit
            result.push_back({hops, current->id});
        }

        for (auto iter : getNodeNeighbors(current->id)) {
            if (visited[iter->index] == false) {
                bfs.push(iter);
                visited[iter->index] = true;
            }
        }

        if (x == bfs.front()) {
            x = bfs.back();
            hops++;
        }

        bfs.pop();
    }

    return result;
}

double Graph::PageRankofNode(string node) {
    vector<Edge*> connections = getEdgeNeighbors(node);
    double weight = 0;
    double outgoing = connections.size() + 1;
    double incoming = 1;

    for (Edge* e : connections) {
        double temp = e->weight;
        temp = temp / 13000 * 100;
        weight += temp;
    }

    vector<Node*> neighbors = getNodeNeighbors(node);

    for (Node* n : neighbors) {
        vector<Edge*> nc = getEdgeNeighbors(n->id);

        for (Edge* e : nc) {
            if (e->dest->id == node) {
                incoming++;
                double temp = e->weight;
                temp = temp / 13000 * 100;
                weight += temp;
            }
        }
    }

    double pageRankDiv = (weight * (incoming / outgoing));
    return pageRankDiv;
}

vector<pair<string, double>> Graph::PageRank() {
    vector<pair<string, double>> output;

    for (auto i : getNodeMap()) {
        double pscore = PageRankofNode(i.first);
        pair<string, double> airport(i.first, pscore);
        output.push_back(airport);
    }

    sort(output.begin(), output.end(), prcompare);
    reverse(output.begin(), output.end());
    return output;
}

bool prcompare(const pair<string, double> &p1, const pair<string, double> &p2) {
    if (p1.second < p2.second) {
        return true;
    } else {
        return false;
    }
}


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

    //represents the optimal path taken
    vector<string> to_return;

    //check if this graph is a valid, weighted graph
    if (nodeMap.count(start) == 0 || nodeMap.count(end) == 0) {
        cout << "the starting or end points do not exist for this graph" << endl;
        return to_return;
    }

    //naive implementation : this implementation is faster for much larger datasets

    //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    unordered_map<string, double> distances;

    //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
    priority_queue<pair<double, string>> nodes_by_distance;

    //stores the parents nodes in order to keep track of the path. Its a map from the one node to the parents
    unordered_map<string, string> parents;

    //intialize starting distance
    distances.insert({start, 0});

    //special case for first node
    nodes_by_distance.push({0, start});

    //the parent of the source is itself
    parents.insert({start, start});
    bool node_found = false;

    //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
    while (!nodes_by_distance.empty()) {

        //find the minimum distance vertex
        string min_node = nodes_by_distance.top().second;

        //remove the visited node
        nodes_by_distance.pop();
        
        //stop algorithm if the node has been found
        if (min_node == end) {

            //set this to be true 
            node_found = true;

            //end the loop
            break;
        }
            
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);

        for (Edge* e : neighbor_connections) {
            string neighbor = e->dest->id; 

            //distance to source based on addition
            double curr_distance = distances[min_node] + e->weight;
            
            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below

            //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
            if (distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) {

                //else if the new distance is shorter or new, change this
                distances[neighbor] = curr_distance;

                //do this to get the effects of a min-heap so that the sorted is reversed
                nodes_by_distance.push({curr_distance * -1, neighbor});

                //cout << "neighbor changed: " << neighbor << " to " << min_node<< endl;
                parents[neighbor] = min_node; 
            }
        }
    }

    //if the node has not been found
    if (node_found == false) {

        //if the destination does not end up being found
        cout << "the destination could not be found likely because the destination is not connected in any way to the source" << endl;
        return to_return;
    } 

    //populate the path vector iteratively until the source node is reached
    
    //insert the end node if it does not equal start
    if (end != start) {
        to_return.insert(to_return.begin(), end);
    }

    //set to the start
    string current_value = parents[end];

    while (current_value != start) {

        //insert at front
        to_return.insert(to_return.begin(), current_value);
        current_value = parents[current_value];
    }

    return to_return;
}

//returns the shortest possible distance between two nodes
double Graph::dijkstra_A_find_shortest_distance (string start, string end) {
    if (nodeMap.count(start) == 0 || nodeMap.count(end) == 0) {
        cout << "the starting or end points do not exist for this graph" <<endl;
        return -1;
    }

    //naive implementation : this implementation is faster for much larger datasets

    //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    unordered_map<string, double> distances;

    //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
    priority_queue<pair<double, string>> nodes_by_distance;

    //intialize starting distance
    distances.insert({start, 0});

    //special case for first node
    nodes_by_distance.push({0, start});

    //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
    while (!nodes_by_distance.empty()) {

        //find the minimum distance vertex
        string min_node = nodes_by_distance.top().second;

        //remove the visited node
        nodes_by_distance.pop();
        
        //stop algorithm if the node has been found
        if (min_node == end) {
            return distances[end]; 
        }
            
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);

        for (Edge* e : neighbor_connections) {
            string neighbor = e->dest->id;

            //distance to source based on addition
            double curr_distance = distances[min_node] + e->weight;

            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below

            //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
            if (distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) {

                //else if the new distance is shorter or new, change this. //this operator also inserts a new key if the key did not already exist
                distances[neighbor] = curr_distance;

                //do this to get the effects of a min-heap so that the sorted is reversed.
                nodes_by_distance.push({curr_distance * -1, neighbor});
            }
        }
    }

    //if the destination does not end up being found
    cout << "the destination could not be found likely because the destination is not connected in any way to the source" << endl;
    return -1;
}

//returns the hashmap of shortest distances to every node in a connected graph from a source, represented as pair of the node id and distance. This is the classic dijkstra's algorithm.
unordered_map<string, double> Graph::general_dijkstra(string start) { 
    if (nodeMap.count(start) == 0) {
        cout << "the starting point does not exist for this graph" << endl;
        return unordered_map<string, double>();
    }

    //naive implementation : this implementation is faster for much larger datasets

    //hashmap of distances. A node essentially has infinite distance in terms of dijkstra's if the node is not in the map yet
    unordered_map<string, double> distances;

    //stores nodes that have been assigned distances but have not been visited. This should be empty by the end of dijkstra's
    priority_queue<pair<double, string>> nodes_by_distance;

    //intialize starting distance
    distances.insert({start, 0});

    //special case for first node
    nodes_by_distance.push({0, start});

    //this is the condition since if the pq becomes empty, this means that a neighbor with less distance was unable to be found.
    while (!nodes_by_distance.empty()) {

        //find the minimum distance vertex
        string min_node = nodes_by_distance.top().second;

        //remove the visited node
        nodes_by_distance.pop();
        vector<Edge*> neighbor_connections = getEdgeNeighbors(min_node);
        
        for (Edge* e : neighbor_connections) {
            string neighbor = e->dest->id; 

            //distance to source based on addition
            double curr_distance = distances[min_node] + e->weight;

            //if the distance to source for the neighbor does not exist yet, meaning it has infinite distance, making the same situation apply as below

            //this does not cause a segmentation fault since in c++, the conditionals within an if statement are already evaluated left to right. Since this if an or statement, just one being true is
            if (distances.count(neighbor) == 0 || curr_distance < distances[neighbor]) {

                //else if the new distance is shorter or new, change this. //this operator also inserts a new key if the key did not already exist
                distances[neighbor] = curr_distance;

                //do this to get the effects of a min-heap so that the sorted is reversed.
                nodes_by_distance.push({curr_distance * -1, neighbor});
            }
        }
    }

    return distances;
}
