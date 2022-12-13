#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "graph.h"
#include "ScanGraph.h"
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

/*     
    std::cout << d << std::endl;
    std::cout << "\n" << std::endl;
    bool out; */
    double d = test->getDistance(start, dest);
    cout << "Distance between coordinates is " << d << " kilometers" << endl;
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
        {"4", "3", "5"},
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
    
    //test the find exact paths
    REQUIRE(test->dijkstra_A_find_shortest_path("1", "1").size() == 0);
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "4").size() == 4);
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "1").size() == 1);
    
    //testing outputs
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "1") == vector<string>{"1"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "2") == vector<string>{"1", "2"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "3") == vector<string>{"1", "2", "3"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "4") == vector<string>{"7","6","5","4"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "5") == vector<string>{"7","6","5"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "6") == vector<string>{"7","6"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "7") == vector<string>{"7"});
    REQUIRE(test->dijkstra_A_find_shortest_path("0", "8") == vector<string>{"1","2","8"});
    delete test;
}

TEST_CASE("test case 4: Dijkstra's algorithm and BFS algorithms on a doubly cyclic graph") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 4: Dijkstra's algorithm on a doubly cyclic graph" << endl;

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

    //testing BFS on to find just the neighboring nodes
    REQUIRE(test->BFS("3",1) == vector<pair<int, string>>{{1,"1"}, {1, "2"}, {1,"4"}, {1,"5"}});
    delete test;
}

TEST_CASE("test case 5: BFS algorithms on a medium complexity graph") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 5: BFS algorithms on a medium complexity graph" << endl;

    const V2D_strings adjacency_list = {
        {"0", "1", "7"},
        {"1", "0", "2", "7"},
        {"2", "1", "8", "5", "3"}, 
        {"3", "2", "5", "4"}, 
        {"4", "3", "5"},
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

/*     auto results = test->BFS("8"); //testing the basic BFS
    cout << "printing BFS result: " << endl;
    for (auto p: results) {
        cout << "(hops: " << p.first << ", id: " << p.second << "), ";
    }
    cout << endl;
 */
    
    REQUIRE(test->BFS("8") == vector<pair<int, string>>{{0,"8"}, {1, "2"}, {1,"7"}, {1,"6"}, {2,"1"}, {2,"5"}, {2,"3"}, {2,"0"}, {3,"4"}});

    //testing the BFS that only returns nodes that are n edges (hops) away from the source
    REQUIRE(test->BFS("8", 1) == vector<pair<int, string>>{{1,"2"}, {1, "7"}, {1,"6"}});
    REQUIRE(test->BFS("8", 2) == vector<pair<int, string>>{{2, "1"}, {2,"5"}, {2, "3"}, {2,"0"}});
    REQUIRE(test->BFS("8", 3) == vector<pair<int, string>>{{3, "4"}});
    REQUIRE(test->BFS("8", 4) == vector<pair<int, string>>{});

/*     results = test->BFS("8",4);
    cout << "printing BFS result: " << endl;
    for (auto p: results) {
        cout << "(hops: " << p.first << ", id: " << p.second << "), ";
    }
    cout << endl; */

    delete test;
}

TEST_CASE("test case 6: loading on a subset of dataset ") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 6: loading on a subset of dataset " << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_test.dat";
    string flights = "../data/routes_test.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    cout << "graph has: " << g->getNodeCount() << " nodes" << endl;
    cout << "graph has: " << g->getEdgeCount() << " edges" << endl;
    cout << "testing getting neighbors of GKA: " << endl;
    auto n1 = g->getEdgeNeighbors("GKA");

    for (Edge* x : n1) {
        cout << x->dest->id << "(" << x->weight << ") ";
    }
    
    cout << endl;

    //what unit would this be in
    cout << "testing shortest distance between GKA and MAG: " << g->dijkstra_A_find_shortest_distance("GKA", "MAG") << endl;
    cout << "printing the shortest path taken in terms of connection by distance between GKA and MAG: ";
    auto path = g->dijkstra_A_find_shortest_path("GKA", "MAG");
    REQUIRE(g->dijkstra_A_find_shortest_path("GKA", "MAG") == vector<string>{"MAG"});
    cout << "starting at GKA, ";

    for (string x : path) {
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
    string airport_path = "../data/airports.dat";
    string flights = "../data/routes.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    cout << "graph has: " << g->getNodeCount() << " nodes" << endl;
    cout << "graph has: " << g->getEdgeCount() << " edges" << endl;

/*     cout << "testing getting neighbors of LAX: " << endl;
    auto n1 = g.getEdgeNeighbors("LAX");
    for(Edge* x : n1) {
        cout << x->dest->id <<"("<< x->weight<<") ";
    } cout << endl; */

    //this is the shortest path taken
    REQUIRE(g->dijkstra_A_find_shortest_path("LAX", "JFK") == vector<string>{"JFK"});

    //what unit would this be in
    cout << "testing shortest distance between LAX and JFK: "<< g->dijkstra_A_find_shortest_distance("LAX", "JFK") << endl;
    cout << "printing the shortest path taken in terms of connection by distance between LAX and JFK: ";
    auto path = g->dijkstra_A_find_shortest_path("LAX", "JFK");
    cout << "starting at LAX, ";

    for (string x : path) {
        cout << "->" << x; 
    }

    cout << endl; 
    delete g;
}

TEST_CASE("test case 8: loading on the whole dataset, connecting flights ") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 8: loading on the whole dataset " << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports.dat";
    string flights = "../data/routes.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    cout << "graph has: " << g->getNodeCount() << " nodes" << endl;
    cout << "graph has: " << g->getEdgeCount() << " edges" << endl;
    cout << "testing getting neighbors of CMI: " << endl;
    auto n1 = g->getEdgeNeighbors("CMI");

    for (Edge* x : n1) {
        cout << x->dest->id <<"("<< x->weight<<") ";
    }

    cout << endl;

    //what unit would this be in
    cout << "testing shortest distance between CMI and SFO: "<< g->dijkstra_A_find_shortest_distance("CMI", "SFO") << endl;
    cout << "printing the shortest path taken in terms of connection by distance between CMI and SFO: ";
    auto path = g->dijkstra_A_find_shortest_path("CMI", "SFO");

    //this is the shortest path taken
    REQUIRE(g->dijkstra_A_find_shortest_path("CMI", "SFO") == vector<string>{"ORD","SFO"});
    cout << "starting at CMI, ";

    for (string x : path) {
        cout << "->" << x; 
    }

    cout << endl; 
    delete g;
}

TEST_CASE("test case 9: check number of pagerank airports") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 9: check number of pagerank airports" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports.dat";
    string flights = "../data/routes.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    vector<pair<string, double>> pr = g->PageRank();
    cout << "There are " << pr.size() << " airports in the pagerank database" << endl;
    int pgsize = (int) pr.size();
    int bfssize = g->getNodeMap().size();
    REQUIRE(bfssize == pgsize);
}

TEST_CASE("test case 10: check pagerank importance algorithm") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 10: check pagerank importance algorithm" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_pagerank_test.dat";
    string flights = "../data/routes_pagerank_test.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    vector<pair<string, double>> pr = g->PageRank();
    REQUIRE(pr.size() == 3);
    cout << "These are the importance of the airports in the pagerank test database" << endl;

    for (auto a : pr) {
        cout << a.first << " -> " << a.second << endl;
    }

    REQUIRE(pr[0].first == "MAG");
}

TEST_CASE("test case 11: check airport scanned successfully") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 11: check airport scanned successfully" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_test.dat";
    string flights = "../data/routes_test.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    Node* tester = g->getNode("MAG");
    REQUIRE(tester->id == "MAG");
    cout << "There exists an airport MAG in: " << tester->location_city << ", " << tester->location_country << endl;
    cout << "Airport MAG scanned into graph successfully" << endl;
}

TEST_CASE("test case 12: check flight route scanned successfully") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 12: check flight route scanned successfully" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_test.dat";
    string flights = "../data/routes_test.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    int tester = g->getEdgeCount();
    REQUIRE(tester == 1);
    cout << "There exists a route to MAG, scanned into graph successfully" << endl;
}

TEST_CASE("test case 13: check flight route validation") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 13: check flight route validation" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_test.dat";
    string flights = "../data/routes_cycle.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    int tester = g->getEdgeCount();
    REQUIRE(tester == 0);
    cout << "There are no routes to MAG, as the only one in the CSV was cyclic" << endl;
}

TEST_CASE("test case 14: check graph construction and getNeighbors()") {
    cout << "____________________________________________________________" << endl;
    cout << "test case 14: check graph construction and getNeighbors()" << endl;
    Graph* g = new Graph();
    string airport_path = "../data/airports_test.dat";
    string flights = "../data/routes_test.dat";
    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
    vector<Node*> n = g->getNodeNeighbors("GKA");
    for (Node* node : n) {
        cout << "Neighbor of GKA: " << node->id << endl;
    }

    REQUIRE(n.size() == 1);
    REQUIRE(n[0]->id == "MAG");
}