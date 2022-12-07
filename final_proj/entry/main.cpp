/**
 * @file main.cpp
 * Contains code to test your recursion, stack, and queue problems.
 */

#include <unistd.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "graph.h"
#include "algo.h"
#include "ScanGraph.h"
#include "BFS.h"

using namespace std;

int main()
{

    cout <<"Test case 1: testing functions using basic graph: a cyclic 3 node graph" << endl;
    Graph::Node* node_a = new Graph::Node("a") ;
    Graph::Node* node_b = new Graph::Node("b") ;
    Graph::Node* node_c= new Graph::Node("c") ;

    //edge from a to b
    Graph::Edge* edge_a_b = new Graph::Edge(node_a, node_b, 4);

    //edge from a to c
    Graph::Edge* edge_a_c = new Graph::Edge(node_a, node_c, 3);

    //edge from b to c
    Graph::Edge* edge_b_c = new Graph::Edge(node_b, node_c, 3);



    //add values to graph
    Graph test_graph_1;
    test_graph_1.addNode(node_a);
    test_graph_1.addNode(node_b);
    test_graph_1.addNode(node_c);

    test_graph_1.addEdge(edge_a_b);
    test_graph_1.addEdge(edge_b_c);
    test_graph_1.addEdge(edge_a_c);

    cout << "testing get neighbors function" << endl;
    vector<Graph::Edge*> result_of_getNeighbors = test_graph_1.getEdgeNeighbors(node_c->id);
    for(Graph::Edge* edge : result_of_getNeighbors) {
        cout  << edge->source->name << "->" << edge->dest->name << endl;
    }

    
    //modify code
/*     Graph g;
    ScanGraph sg;
    string airport = "../data/airports_test.dat";
    string routes = "../data/routes_test.dat";
    ifstream airport_ifs(airport);
    ifstream route_ifs(routes);

    sg.scanCSV(g, airport_ifs, route_ifs);

    for (std::vector<int> output : g.getAdjMatrix()) {
        for (unsigned i = 0; i < output.size(); i++) {
            std::cout << output.at(i) << ' ';
        }
        std::cout << '\n' << std::endl;
    } */




}