#include "ScanGraph.h"
#include "graph.h"

void ScanGraph::scanCSV(Graph* g, string airport_ifs, string route_ifs) {
    ifstream airports(airport_ifs);
    ifstream routes(route_ifs);
    scanCSV_helper(g, airports, routes);
}

//helper to determine if a string is a number
bool ScanGraph::is_number(string s){
    for (unsigned int i = 0; i < s.size(); i++) {
        char c = s.at(i);

        if (!isdigit(c) && c != '-' && c != '.') {

            //extra quantifiers for negative numbers and decimals
            return false;
        }
    }
    return true;
}

void ScanGraph::scanCSV_helper(Graph *g, ifstream &airport_ifs, ifstream &route_ifs) {
    string line;
    int index = 0;
    if (airport_ifs.is_open()) {
        while (getline(airport_ifs, line)) {
            vector<string> vec;
            SplitString(line, ',', vec);
            string airportName = Trim(vec[1]);
            airportName = airportName.substr(1, airportName.size() - 2);
            string airportCode;

            if (vec[4] == "\\N") {
                airportCode = vec[5];
            } else {
                airportCode = vec[4];
            }

            //remove parentheses
            airportCode = airportCode.substr(1, airportCode.size() - 2);

            //check if string is number before assigning
            if (is_number(vec[6]) && is_number(vec[7])) {
                double latitude = stod(vec[6]);
                double longitude = stod(vec[7]);              

                //airport location 
                string city_location = vec[2].substr(1, vec[2].size() - 2);
                string country_location = vec[3].substr(1, vec[3].size() - 2);
                Node *n = new Node(airportCode, airportName, index, latitude, longitude, city_location, country_location);
                index++;
                g->addNode(n);
            } else {
                cout << "invalid number values: " << vec[6] << "," << vec[7] << endl;
            }
        }
    }

    if (route_ifs.is_open()) {
        while (getline(route_ifs, line)) {
            vector<string> vec;
            SplitString(line, ',', vec);
            string start = Trim(vec[2]);
            string end = Trim(vec[4]);

            if (g->exists(start) && g->exists(end)) {
                Node* sourceN = g->getNode(start);
                Node* destN = g->getNode(end);
                int airline_code = -1;

                //check if this is a number
                if (is_number(Trim(vec[1]))) {
                    airline_code = stoi(Trim(vec[1]));
                } 

                //modified to calculate distance
                double route_dist = g->getDistance(sourceN, destN);
                Graph::Edge *e = new Graph::Edge(sourceN, destN, route_dist, airline_code);
                g->addEdge(e);
            }
        }
    }
}

//from mp_schedule
string ScanGraph::TrimRight(const string & str) {
    string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

string ScanGraph::TrimLeft(const string & str) {
    string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

string ScanGraph::Trim(const string & str) {
    string tmp = str;
    return TrimLeft(TrimRight(str));
}

int ScanGraph::SplitString(const string & str1, char sep, vector<string> &fields) {
    string str = str1;
    string::size_type pos;

    while ((pos=str.find(sep)) != string::npos) {
        fields.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);  
    }

    fields.push_back(str);
    return fields.size();
}
