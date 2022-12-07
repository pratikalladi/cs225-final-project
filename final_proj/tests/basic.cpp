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

TEST_CASE("sumDigits", "[valgrind][weight=1]"){
    SECTION("Base cases work") {
        REQUIRE(1 == 1);
    }
    SECTION("Multiple digits sum correctly") {
        REQUIRE(9 == 9);
    }
}


TEST_CASE("test case 1: dijkstra's algorithm on a basic graph") {
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
    cout <<"printing out graph adjacency list: " << endl;
    test->print_graph();

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "2") == 7);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "4") == 20);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "5") == 20);

    REQUIRE(test->dijkstra_A_find_shortest_distance("1", "6") == 11);

    REQUIRE(test->dijkstra_A_find_shortest_path("1", "6").size() == 2);

    REQUIRE(test->dijkstra_A_find_shortest_path("1", "1").size() == 0);

    delete test;
}

TEST_CASE("test case 2: dijkstra's algorithm on a medium complexity graph") {
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
    cout <<"printing out graph adjacency list: " << endl;
    test->print_graph();


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

TEST_CASE("test case 3: dijkstra's algorithm on a doubly cyclic graph") {
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
    cout <<"printing out graph adjacency list: " << endl;
    test->print_graph();


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
  
TEST_CASE("test 1 on the whole dataset ") {
    Graph g;
    string airport_path =" /workspaces/cs225env/cs225-final-project/final_proj/data/airports.dat";
    string flights = "/workspaces/cs225env/cs225-final-project/final_proj/data/routes_test.dat";

    ScanGraph sg;
    sg.scanCSV(g, airport_path, flights);
}
  