#include "ScanGraph.h"
#include "graph.h"

void ScanGraph::scanCSV(Graph* g, string airport_ifs, string route_ifs) {
    ifstream airports(airport_ifs);
    ifstream routes(route_ifs);

    scanCSV_helper(g, airports, routes);
}

<<<<<<< HEAD

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

=======
>>>>>>> 76d6068fe3d6d648e6f0fc980e1cd4b25aa9e814
//helper to determine if a string is a number
bool ScanGraph::is_number(string s){
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
    std::string line;
    int index = 0;
    if (airport_ifs.is_open()) {
        while (getline(airport_ifs, line)) {
            vector<string> vec;
            SplitString(line, ',', vec);
            //vector<string> vec = splitpart(line, ",");
            string airportName = Trim(vec[1]);
            airportName = airportName.substr(1,airportName.size()-2);
            string airportCode;
            if (vec[4] == "\\N") {
                airportCode = vec[5];
            } else {
                airportCode = vec[4];
            }
            airportCode = airportCode.substr(1, airportCode.size() - 2); //remove parentheses

            //check if string is number before assigning
            if(is_number(vec[6]) && is_number(vec[7])) {
                double latitude = std::stod(vec[6]);
                double longitude = std::stod(vec[7]);              

                //airport location 
                string city_location = vec[2].substr(1, vec[2].size() - 2);
                string country_location = vec[3].substr(1, vec[3].size() - 2);
                
                Graph::Node *n = new Graph::Node(airportCode, airportName, index, latitude, longitude, city_location, country_location);
                index++;
                g->addNode(n);
            } else {
                cout << "invalid number values: " << vec[6] << "," << vec[7] << endl;
            }
        }
    }

    if (route_ifs.is_open()) {
        while(getline(route_ifs, line)) {
            vector<string> vec;
            SplitString(line, ',', vec);
            //vector<string> vec = splitpart(line, ",");
            string start = Trim(vec[2]);
            string end = Trim(vec[4]);

            if (g->exists(start) && g->exists(end)){
                Graph::Node* sourceN = g->getNode(start);
                Graph::Node* destN = g->getNode(end);

<<<<<<< HEAD

                int airline_code = -1;
                //check if this is a number
                if(is_number(Trim(vec[1]))) {
                    airline_code = std::stoi(Trim(vec[1]));
                } 

                double distance_to_add = g->getDistance(srcNode, destNode); //modified to calculate distance
                Graph::Edge *e = new Graph::Edge(srcNode, destNode, distance_to_add, airline_code);
=======
                double route_dist = g->getDistance(sourceN, destN); //modified to calculate distance
                Graph::Edge *e = new Graph::Edge(sourceN, destN, route_dist);
>>>>>>> 76d6068fe3d6d648e6f0fc980e1cd4b25aa9e814
                g->addEdge(e);
            }
        }
    }
}

//from mp_schedule

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
