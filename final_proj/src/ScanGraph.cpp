#include "ScanGraph.h"
#include "graph.h"

void ScanGraph::scanCSV(Graph* g, string airport_ifs, string route_ifs) {
    ifstream airports(airport_ifs);
    ifstream routes(route_ifs);

    scanCSV_helper(g, airports, routes);
}

vector<string> ScanGraph::splitpart(string str_, string delimiter) {
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

//helper to determine if a string is a number
bool is_number(string s){
    for(unsigned int i = 0; i < s.size(); i++) {
        char c = s.at(i);
        if(!isdigit(c) && c != '-' && c != '.') { 
            //extra quantifiers for negative numbers and decimals
            return false;
        }
    }
    return true;
}


void ScanGraph::scanCSV_helper(Graph *g, ifstream &airport_ifs, ifstream &route_ifs) {
    string line, tmp;
    int index = 0;
    if (airport_ifs.is_open()) {
        while (getline(airport_ifs, line)) {
            //vector<string> vec;
            //SplitString(line, ',', vec);
            vector<string> vec = splitpart(line, ",");
            string airportName = Trim(vec[1]);
            airportName = airportName.substr(1,airportName.size()-2);
            string airportAbbr;
            if (vec[4] == "\\N") {
                airportAbbr = vec[5];
            } else {
                airportAbbr = vec[4];
            }
            airportAbbr = airportAbbr.substr(1, airportAbbr.size() - 2); //remove parentheses

            //check if string is number before assigning
            if(is_number(vec[6]) && is_number(vec[7])) {
                double latitude = std::stod(vec[6]);
                double longitude = std::stod(vec[7]);              

                //airport location 
                string city_location = vec[2].substr(1, vec[2].size() - 2);
                string country_location = vec[3].substr(1, vec[3].size() - 2);
                
                Graph::Node *n = new Graph::Node(airportAbbr, airportName, index, latitude, longitude, city_location, country_location);
                index += 1;
                g->addNode(n);
            } else {
                cout << "invalid number values: " << vec[6] << "," << vec[7] << endl;
            }
        }
    }
    if (route_ifs.is_open()) {
        while(getline(route_ifs, line)) {
            //vector<string> vec;
            //SplitString(line, ',', vec);
            vector<string> vec = splitpart(line, ",");
            string start = Trim(vec[2]);
            string end = Trim(vec[4]);
            if (g->exists(start) && g->exists(end)){
                Graph::Node* srcNode = g->getNode(start);
                Graph::Node* destNode = g->getNode(end);

                double distance_to_add = g->getDistance(srcNode, destNode); //modified to calculate distance
                Graph::Edge *e = new Graph::Edge(srcNode, destNode, distance_to_add);
                g->addEdge(e);
            }
        }
    }
}

std::string ScanGraph::TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string ScanGraph::TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string ScanGraph::Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int ScanGraph::SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}
