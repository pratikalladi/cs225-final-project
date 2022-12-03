#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ScanGraph.h"


using namespace std;

class parseGraph {
    public:
       
        void parseCSV(Graph &g, ifstream &airport_ifs, ifstream &route_ifs);

    private:
           
        vector<string> delimit(string str_, string delimiter);
};