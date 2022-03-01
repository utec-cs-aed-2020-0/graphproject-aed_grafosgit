#ifndef PRIM_A
#define PRIM_A

#include <iostream>
#include <list>
#include <string>
#include "priorityqueue.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include "../DSets.h"
#include "../graph.h"

using namespace std;
template<typename TV, typename TE>
class Prim{
    public:
        string id;
        Graph<TV,TE>* graph;
        
        Prim(Graph<TV,TE>* dir , string id_){
            graph = dir;
            id = id_;
        };

        void prim();

};

template<typename TV, typename TE>
void Prim<TV,TE>::prim(){
    int n = 0; // 0. We need to check if we hit every vertex
    int i = 0;
    DisjoinSetArray<string> ds(5000);
    Vertex<TV,TE>* curr_vert = graph->GetVertex(id); // 1. we start by a vertex and get the list of edges
    Edge<TV, TE>* curr_edge;
    list<Edge<TV, TE>*> result;
    P_Queue<Edge<TV, TE>*> queue;
    list<Edge<TV, TE>*> EdgeList = curr_vert->edges;
    for(auto it = EdgeList.begin(); it != EdgeList.end(); it++){
        curr_edge = *it;
        queue.Insert(curr_edge,curr_edge->weight); // 2. from those edges we push them into our priority queue
    }
    Edge<TV,TE>* nxt_edge = queue.front();
    result.push_back(nxt_edge);
    curr_vert = nxt_edge->vertexes[0];
    ds.Insert(curr_vert->id);
    string u1 = curr_vert->id;
    curr_vert = nxt_edge->vertexes[1];
    ds.Insert(curr_vert->id);
    string u2 = curr_vert->id;
    queue.pop_front();
    ds.UnionD(u1,u2);
    while(n < (graph->GetNumOfVert()-2) || !queue.IsEmpty() ){
        EdgeList = curr_vert->edges;
        if(EdgeList.size() > 0){
            for(auto it = EdgeList.begin(); it != EdgeList.end(); it++){
                curr_edge = *it;
                Vertex<TV,TE>* start  = curr_edge->vertexes[0];
                Vertex<TV,TE>* end =  curr_edge->vertexes[1];
                if(!ds.FindElement(end->id)){
                    queue.Insert(curr_edge,curr_edge->weight);
                    
                }
            }
        }
        nxt_edge = queue.front();
        curr_vert = nxt_edge->vertexes[1];
        if(!ds.FindElement(curr_vert->id)){
            result.push_back(nxt_edge);
            n +=1 ;
            ds.Insert(curr_vert->id);
        }
        queue.pop_front();
    }
    for(auto it = result.begin(); it != result.end(); it++){
        curr_edge = *it;
        curr_vert = curr_edge->vertexes[0];
        cout << "{"<< curr_vert->data<<",";
        curr_vert = curr_edge->vertexes[1];
        cout << curr_vert->data<<"} ";
    }
    cout << endl;
}

#endif