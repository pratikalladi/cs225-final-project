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
        void scanCSV(Graph *g, string airport_ifs, string route_ifs);

    private:
        void scanCSV_helper(Graph *g, ifstream &airport_ifs, ifstream &route_ifs);
        bool is_number(string s);
        string TrimRight(const string & str);
        string TrimLeft(const string & str);
        string Trim(const string & str);
        int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields);
};
