#include <catch2/catch_test_macros.hpp>


#include <iostream>
#include <sstream>
#include <string>

#include "graph.h"
#include "ScanGraph.h"
#include "algo.h"

#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;

TEST_CASE("test case 1: test distance function"){
    cout << "____________________________________________________________" << endl;
    cout << "test case 1: test distance function" << endl;


    Graph* test = new Graph();
    Node* start = new Node("start");
    Node* dest = new Node("end");
    start->latitude = 36.12;
    start->longitude = -86.67;
    dest->latitude = 33.94;
    dest->longitude = -118.40;
    test->addNode(start);
    test->addNode(dest);

    double d = test->getDistance(start, dest);
    std::cout << d << std::endl;
    std::cout << "\n" << std::endl;
    bool out;
    REQUIRE(abs((d - 2886)) < 1);

    //delete test graph
    delete test;
}


TEST_CASE("test case 2: dijkstra's algorithm on a basic graph") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 2: dijkstra's algorithm on a basic graph" << endl;

    const V2D_strings adjacency_list = {
        {"1", "6", "3", "2"},
        {"2", "1", "3", "4"}, 
        {"3", "1", "2", "4", "6"}, 
        {"4", "2", "3", "5"}, 
        {"5", "4", "6"}, 
        {"6", "1", "3", "5"}
    };
    

    const V2D_numbers num_weights = {
        {0.0, 14.0, 9.0, 7.0},\
        {0.0, 7.0, 10.0, 15.0}, \
        {0.0, 9.0, 10.0, 11.0, 2.0}, \
        {0.0, 15.0, 11.0, 6.0}, \
        {0.0, 6.0, 9.0}, \
        {0.0, 14.0, 2.0, 9.0}
    };

    Graph* test = new Graph();
    test->construct_basic_graph(adjacency_list, num_weights);
    //cout <<"printing out graph adjacency list: " << endl;
    //test->print_graph();

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "2") == 7);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "4") == 20);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "5") == 20);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "6") == 11);

    REQUIRE(test->dijkstra_A_find_shortest_path("1", "6").size() == 2);

    REQUIRE(test->dijkstra_A_find_shortest_path("1", "1").size() == 0);

    delete test;
}

TEST_CASE("test case 3: dijkstra's algorithm on a medium complexity graph") {
     cout << "____________________________________________________________" << endl;
    cout << "test case 3: dijkstra's algorithm on a medium complexity graph" << endl;

    const V2D_strings adjacency_list = {
        {"0", "1", "7"},
        {"1", "0", "2", "7"},
        {"2", "1", "8", "5", "3"}, 
        {"3", "2", "5", "4"}, 
        {"4", "3", "5"}, ///////////////////
        {"5", "3", "4", "2", "6"}, 
        {"6", "5", "7", "8"}, 
        {"7", "0", "1", "8", "6"}, 
        {"8", "2", "7", "6"} 
    };

    const V2D_numbers num_weights = {
        {0.0, 4.0, 8.0},
        {1.0, 4.0, 8.0, 11.0},
        {2.0, 8.0, 2.0, 4.0, 7.0}, 
        {3.0, 7.0, 4.0, 9.0}, 
        {4.0, 9.0, 10.0}, 
        {5.0, 14.0, 10.0, 4.0, 2.0}, 
        {6.0, 2.0 , 1.0, 6.0},
        {7.0, 8.0, 11.0, 7.0, 1.0},
        {8.0, 2.0, 7.0, 6.0}
    };
    Graph* test = new Graph();
    test->construct_basic_graph(adjacency_list, num_weights);
    //cout <<"printing out graph adjacency list: " << endl;
    //test->print_graph();


    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "1") == 0);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "1") == 4);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "2") == 12);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "3") == 19);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "4") == 21);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "5") == 11);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "6") == 9);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "7") == 8);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "8") == 14);
    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "6") == 12);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "fuck") == -1); //testing invalid inputs
    
    //test the find exact paths
    REQUIRE(test->dijkstra_A_find_shortest_path("1", "1").size() == 0);
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "4").size() == 4);
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "1").size() == 1);
    
    //testing outputs
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "1") == vector<string>{"1"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "2") == vector<string>{"1", "2"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "3") == vector<string>{"1", "2", "3"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "4") == vector<string>{"7","6","5","4"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "5") == vector<string>{"7","6","5"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "6") == vector<string>{"7","6"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "7") == vector<string>{"7"}); // the 
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "8") == vector<string>{"1","2","8"}); // the 

    auto start = high_resolution_clock::now();
    int n = 5000;
    for(int i = 0; i < n; i++) { //run the longest path n times and the shortest path n times as well
        test->dijkstra_A_find_shortest_distance("0", "1");
        test->dijkstra_A_find_shortest_distance("1", "5");
        test->dijkstra_A_find_shortest_distance("1", "6");
    }
    auto stop = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<microseconds>(stop - start);

    double runtime = duration.count();
    double average_runtime = runtime / ((double) n);
    cout << endl << "average dijkstra's algorithm runtime for test case 2: " << average_runtime << " microseconds" << endl << endl;


    delete test;
}

TEST_CASE("test case 4: dijkstra's algorithm on a doubly cyclic graph") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 4: dijkstra's algorithm on a doubly cyclic graph" << endl;


    const V2D_strings adjacency_list = {
        {"0", "1", "2"},
        {"1", "0", "3"},
        {"2", "0", "3"}, 
        {"3", "1", "2", "4", "5"}, 
        {"4", "3", "5", "6"}, 
        {"5", "3", "4", "6"}, 
        {"6", "4", "5"},
        {"7"} //unconnected part
    };


    const V2D_numbers num_weights = {
        {0.0, 2.0, 6.0},
        {1.0, 2.0, 5.0},
        {2.0, 6.0, 8.0}, 
        {3.0, 5.0, 8.0, 10.0, 15.0}, 
        {4.0, 10.0, 6.0, 2.0}, 
        {5.0, 15.0, 6.0, 6.0}, 
        {6.0, 2.0, 6.0},
        {7.0} //unconnected part
    };

    Graph* test = new Graph();
    test->construct_basic_graph(adjacency_list, num_weights);
    //cout <<"printing out graph adjacency list: " << endl;
    //test->print_graph();


    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "0") == 0);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "1") == 2);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "2") == 6);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "3") == 7);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "4") == 17);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "5") == 22);
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "6") == 19);
    //testing for a completely unconnected component
    REQUIRE(test->dijkstra_A_find_shortest_distance("0", "7") == -1);

    delete test;
}

TEST_CASE("test case 5: BFS algorithm on a medium complexity graph") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 5: BFS algorithm on a medium complexity graph" << endl;

    const V2D_strings adjacency_list = {
        {"0", "1", "7"},
        {"1", "0", "2", "7"},
        {"2", "1", "8", "5", "3"}, 
        {"3", "2", "5", "4"}, 
        {"4", "3", "5"}, ///////////////////
        {"5", "3", "4", "2", "6"}, 
        {"6", "5", "7", "8"}, 
        {"7", "0", "1", "8", "6"}, 
        {"8", "2", "7", "6"} 
    };

    const V2D_numbers num_weights = {
        {0.0, 4.0, 8.0},
        {1.0, 4.0, 8.0, 11.0},
        {2.0, 8.0, 2.0, 4.0, 7.0}, 
        {3.0, 7.0, 4.0, 9.0}, 
        {4.0, 9.0, 10.0}, 
        {5.0, 14.0, 10.0, 4.0, 2.0}, 
        {6.0, 2.0 , 1.0, 6.0},
        {7.0, 8.0, 11.0, 7.0, 1.0},
        {8.0, 2.0, 7.0, 6.0}
    };
    Graph* test = new Graph();
    test->construct_basic_graph(adjacency_list, num_weights);
    //cout <<"printing out graph adjacency list: " << endl;
    //test->print_graph();

    auto results = test->BFS("8");

    cout << "printing BFS result: " << endl;
    for (auto p: results) {
        cout << "id: " << p.first << ", hops: " << p.second << "; ";
    }
    cout << endl;

    delete test;
}

TEST_CASE("test case 6: loading on a subset of dataset ") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 6: loading on a subset of dataset " << endl;

    Graph* g = new Graph();
    string airport_path ="../data/airports_test.dat";
    string flights = "../data/routes_test.dat";

    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);

    cout <<"graph has: " << g->getNodeCount() << " nodes" << endl;
    cout <<"graph has: " << g->getEdgeCount() << " edges" << endl;

    cout << "testing getting neighbors of GKA: " << endl;
    auto n1 = g->getEdgeNeighbors("GKA");
    for(Edge* x : n1) {
        cout << x->dest->id <<"("<< x->weight<<") ";
    } cout << endl;
    
    cout << "testing shortest distance between GKA and MAG: "<< g->dijkstra_A_find_shortest_distance("GKA", "MAG") << endl; //what unit would this be in
    cout << "printing the shortest path taken in terms of connection by distance between GKA and MAG: ";
    auto path = g->dijkstra_A_find_shortest_path("GKA", "MAG");
    cout << "starting at GKA, ";
    for(string x : path) {
        cout << "->" << x; 
    }
    cout << endl;
    cout << endl;
    delete g;
}



TEST_CASE("test case 7: loading on the whole dataset ") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 7: loading on the whole dataset " << endl;

    Graph* g = new Graph();
    string airport_path ="../data/airports.dat";
    string flights = "../data/routes.dat";

    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);

    cout <<"graph has: " << g->getNodeCount() << " nodes" << endl;
    cout <<"graph has: " << g->getEdgeCount() << " edges" << endl;

/*     cout << "testing getting neighbors of LAX: " << endl;
    auto n1 = g.getEdgeNeighbors("LAX");
    for(Edge* x : n1) {
        cout << x->dest->id <<"("<< x->weight<<") ";
    } cout << endl; */
    
    cout << "testing shortest distance between LAX and JFK: "<< g->dijkstra_A_find_shortest_distance("LAX", "JFK") << endl; //what unit would this be in
    cout << "printing the shortest path taken in terms of connection by distance between LAX and JFK: ";
    auto path = g->dijkstra_A_find_shortest_path("LAX", "JFK");
    cout << "starting at LAX, ";
    for(string x : path) {
        cout << "->" << x; 
    }
    cout << endl; 

    delete g;
}



TEST_CASE("test case 8: loading on the whole dataset, connecting flights ") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 8: loading on the whole dataset " << endl;

    Graph* g = new Graph();
    string airport_path ="../data/airports.dat";
    string flights = "../data/routes.dat";

    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);

    cout <<"graph has: " << g->getNodeCount() << " nodes" << endl;
    cout <<"graph has: " << g->getEdgeCount() << " edges" << endl;

    cout << "testing getting neighbors of CMI: " << endl;
    auto n1 = g->getEdgeNeighbors("CMI");
    for(Edge* x : n1) {
        cout << x->dest->id <<"("<< x->weight<<") ";
    } cout << endl;
    
    cout << "testing shortest distance between CMI and SFO: "<< g->dijkstra_A_find_shortest_distance("CMI", "SFO") << endl; //what unit would this be in
    cout << "printing the shortest path taken in terms of connection by distance between CMI and SFO: ";
    auto path = g->dijkstra_A_find_shortest_path("CMI", "SFO");
    REQUIRE(g->dijkstra_A_find_shortest_path("CMI", "SFO") == vector<string>{"ORD","SFO"}); //this is the shortest path taken
    cout << "starting at CMI, ";
    for(string x : path) {
        cout << "->" << x; 
    }
    cout << endl; 
    delete g;
}
  