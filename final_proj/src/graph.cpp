#define _USE_MATH_DEFINES

#include <cmath>
#include "Graph.h"
#include<bits/stdc++.h>
#define Earth_radius 6371e3
using namespace std;

Graph::Graph() {
    adjSize = 0;
    edgeCount = 0;
};

Graph::~Graph() {

};

void Graph::addNode(Node* n) {
    n->modifyIndex(adjSize);   
    vector<Edge *> tmp;
    adjList.push_back(tmp); 
    idNodeMap[adjSize] = n;   
    abbrNodeMap[n->abbr] = n; 
    adjSize += 1;            
    all_node.push_back(n);
}

void Graph::addEdge(Edge* e) {
    adjList[e->source->index].push_back(e);
    edgeCount ++;  
}




vector<vector<int>> Graph :: getAdjMatrix(){
    int n = adjSize;
    adjMatrix.resize(n+1,vector<int> (n+1));
    for(int i=0;i<n;i++){
        for(Edge * e : adjList[i]){
            int dist = computeDist(e->source,e->dest);
            adjMatrix[e->source->index][e->dest->index] = dist;
        }
    }
    return adjMatrix;
}





Graph::Node* Graph::abbr_to_Node(string abbr){
    try {
        return abbrNodeMap.at(abbr);
    } catch (out_of_range& e){
        cerr << e.what() << endl;
        cout << "abbr: " << abbr << endl;
    }
}





bool Graph::exists(string abbr) {
    return abbrNodeMap.count(abbr) ? true : false;
}

double Graph::computeDist(Node* src, Node* dest){
    double latSrc = (src->latitude)*M_PI/180.0; 
    double latDest = (dest->latitude)*M_PI/180.0;
    double lonSrc = (src->longitude)*M_PI / 180.0;
    double lonDest = (dest->longitude)*M_PI / 180.0;

    double lat_diff = latDest-latSrc;
    double lon_diff = lonSrc - lonDest; 
    
    double a = pow(sin(lat_diff/2.0),2) + cos(latSrc)*cos(latDest)*pow(sin(lon_diff/2.0),2); 
    double c = 2.0 * asin(sqrt(a));
    double final_distance = Earth_radius * c;
    return final_distance;
}

vector<vector<Graph::Edge *>> Graph::getAdjList() {
    return adjList;
}

void Graph::BFS(string src, string dest) {
    queue<string> q;
    unordered_set<string> visited;
    map<string, string> predecessor;
    q.push(src);
    visited.insert(src);
    while (!q.empty()) {
        string cur = q.front();  
        q.pop();
        if (cur == dest) {
            break;
        }
        Node * curAbbr = abbr_to_Node(cur);
        for (Edge* e: adjList[curAbbr->index]) {
            if (visited.count(e->dest->abbr) == 0) { // not visited
                visited.insert(e->dest->abbr);
                q.push(e->dest->abbr);
                predecessor[e->dest->abbr] = curAbbr->abbr;
            }
        }
    }
    vector<string> res;
    string cur = dest;
    res.push_back(cur);
    while (predecessor.count(cur)) {
        cur = predecessor[cur];
        res.push_back(cur);
    }
    reverse(res.begin(), res.end());

    cout << "START BFS SHORTEST PATH SEARCH" << endl;
    cout << "==========================================" << endl;        
    for (size_t i = 0; i < res.size(); i++) {
        if (i != res.size() - 1) {
            cout << res[i] << " " << ">>";
        }
        else {
            cout << res[i];
        }
    }
    cout << endl;
}



double Graph :: Win(int m,int o){
    int k = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[i][m] != INT_MAX){
            k++;
        }
    }
    int l = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[o][i] != INT_MAX){
            for(int j=0;j<adjSize;j++){
                if(adjMatrix[j][i] != INT_MAX){
                    l++;
                }
            }
        }
    }
    return (double)k/(double)l;
}


double Graph :: Wout(int m,int o){
    int k = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[0][i] != INT_MAX){
            k++;
        }
    }
    int l = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[o][i] != INT_MAX){
            for(int j=0;j<adjSize;j++){
                if(adjMatrix[i][j] != INT_MAX){
                    l++;
                }
            }
        }
    }
    return (double)k/(double)l;
}


double Graph :: PageRankofNode(int o,vector<double> &p){
    double a = 0;
    for(int i=0;i<adjSize;i++){
        if(adjMatrix[i][o] != INT_MAX){
            int k = 0;
            for(int s=0;s<adjSize;s++){
                if(adjMatrix[i][s] != INT_MAX){
                    k++;
                }
            }
            a += ((double)p[i]/k) * Win(i,o) * Wout(i,o);
        }
    }
    return a;
}
