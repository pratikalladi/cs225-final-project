#include "ScanGraph.h"


vector<string> parseGraph::delimit(string str_, string delimiter) {
    vector<string> res;
    size_t pos_start = 0;
    size_t pos_end = delimiter.length();
    string token;

    while ((pos_end = str_.find(delimiter, pos_start)) != string::npos) {
        if (pos_start > 0 && isalpha(str_.at(pos_start - 2)) && str_.at(pos_start) == ' ') {
            pos_start = pos_end + delimiter.length();
            continue;
        } else {
            token = str_.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delimiter.length();
            res.push_back(token);
        }
    }
    res.push_back(str_.substr(pos_start));
    return res;
}

void parseGraph::parseCSV(Graph &g, ifstream &airport_ifs, ifstream &route_ifs) {
    string line, tmp;
    int index = 0;
    if (airport_ifs.is_open()) {
        while (getline(airport_ifs, line)) {
            vector<string> vec = delimit(line, ",");
            string airportName = vec[1];
            airportName = airportName.substr(1,airportName.size()-2);
            string airportAbbr;
            if (vec[4] == "\\N") {
                airportAbbr = vec[5];
            } else {
                airportAbbr = vec[4];
            }
            airportAbbr = airportAbbr.substr(1, airportAbbr.size() - 2);
            double latitude = stod(vec[6]);
            double longitude = stod(vec[7]);               
            
            Graph::Node *n = new Graph::Node(index, latitude, longitude, airportName, airportAbbr);
            index += 1;
            g.addNode(n);
        }
    }
    if (route_ifs.is_open()) {
        while(getline(route_ifs, line)) {
            vector<string> vec = delimit(line, ",");
            string source = vec[2];
            string dest = vec[4];
            if (g.exists(source) && g.exists(dest)){
                Graph::Node* srcNode = g.abbr_to_Node(source);
                Graph::Node* destNode = g.abbr_to_Node(dest);
                Graph::Edge *e = new Graph::Edge(srcNode, destNode);
                g.addEdge(e);
            }
       
        }
    }
}