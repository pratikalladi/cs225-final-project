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


    //Graph::Edge* opposite_edge = new Graph::Edge(e->dest, e->source); //this code only should be uncommented if the intended graph is not directed since this effectively adds an edge back to the source
    //adjList[opposite_edge->source->index].push_back(opposite_edge); //this code only should be uncommented if the intended graph is not directed since this effectively adds an edge back to the source
    
    edgeCount ++;  
}

vector<vector<int>> Graph :: getAdjMatrix(){
    int n = adjSize;
    adjMatrix.resize(n+1, vector<int>(n+1));
    for(int i=0; i < n; i++){
        for(Edge * e : adjList[i]){
            int dist = distance(e->source,e->dest);
            adjMatrix[e->source->index][e->dest->index] = dist;
        }
    }
    return adjMatrix;
}

bool Graph::exists(string abbr) {
    return abbrNodeMap.count(abbr) ? true : false;
}

double Graph::distance(Node* src, Node* dest){
    double source_lat = (src->latitude)*M_PI/180.0; 
    double dest_lat = (dest->latitude)*M_PI/180.0;
    double source_long = (src->longitude)*M_PI / 180.0;
    double dest_long = (dest->longitude)*M_PI / 180.0;
    
    double a = pow(sin((dest_lat-source_lat)/2.0),2) + cos(source_lat)*cos(dest_lat)*pow(sin((source_long - dest_long)/2.0),2); 
    double finaldist = Earth_radius * asin(sqrt(a)) * 2.0;
    return finaldist;
}

vector<vector<Graph::Edge *>> Graph::getAdjList() {
    return adjList;
}

void Graph::BFS(string src, string dest) {

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

//function to get a list of all neighbors
vector<Graph::Edge*> Graph::getNeighbors(Graph::Node* source) {

    int list_index = source->index;

    return adjList[list_index];
}