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
    Graph::Node* node_a = new Graph::Node(0, 0.001, 0.001, "airport a", "aa") ;
    Graph::Node* node_b = new Graph::Node(1, 0.001, 0.001, "airport b", "bb") ;
    Graph::Node* node_c= new Graph::Node(2, 0.001, 0.001, "airport c", "cc") ;

    //edge from a to b
    Graph::Edge* edge_a_b = new Graph::Edge(node_a, node_b);

    //edge from a to c
    Graph::Edge* edge_a_c = new Graph::Edge(node_a, node_c);

    //edge from b to c
    Graph::Edge* edge_b_c = new Graph::Edge(node_b, node_c);



    //add values to graph
    Graph test_graph_1;
    test_graph_1.addNode(node_a);
    test_graph_1.addNode(node_b);
    test_graph_1.addNode(node_c);

    test_graph_1.addEdge(edge_a_b);
    test_graph_1.addEdge(edge_b_c);
    test_graph_1.addEdge(edge_a_c);

    cout << "testing get neighbors function" << endl;
    vector<Graph::Edge*> result_of_getNeighbors = test_graph_1.getNeighbors(node_c);
    for(Graph::Edge* edge : result_of_getNeighbors) {
        cout  << edge->source->name << "->" << edge->dest->name << endl;
    }



}