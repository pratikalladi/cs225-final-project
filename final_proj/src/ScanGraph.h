#pragma once
#include "graph.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ScanGraph.h"


using namespace std;

class ScanGraph {
    public:
       
        void scanCSV(Graph &g, ifstream &airport_ifs, ifstream &route_ifs);

    private:
           
        vector<string> splitpart(string str_, string delimiter);
};