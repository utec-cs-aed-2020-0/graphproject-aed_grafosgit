#include <iostream>
#include <list>
#include "priorityqueue.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include "../DSets.h"
#include "../graph.h"

using namespace std;
template<typename TV, typename TE>
class Kruskal_A{
    public:
        Graph<TV,TE>* graph;
    
        Kruskal_A(Graph<TV,TE>* dir){
            graph = dir;
        };

        void Kruskal_();
        bool contains(list<string> &listOfElements, const string &element);
};

template<typename TV, typename TE>
void Kruskal_A<TV,TE>::Kruskal_(){
    DisjoinSetArray<string> ds(3500);
    Vertex<TV,TE>* curr_vert = graph->Getbegin(); 
    string s_id = curr_vert->id;
    ds.Insert(s_id);
    Edge<TV, TE>* curr_edge;
    P_Queue<Edge<TV, TE>*> queue;
    list<Edge<TV, TE>*> EdgeList;
    map<string,Vertex<TV,TE>*> grph = graph->getMap();
    for( auto it = grph.begin(); it != grph.end(); it++){
        curr_vert = it->second;
        EdgeList = curr_vert->edges;
        if(!ds.FindElement(curr_vert->id))
            ds.Insert(curr_vert->id);
        if(EdgeList.size() > 0){
            for(auto ite = EdgeList.begin(); ite != EdgeList.end(); ite++){
                curr_edge = *ite;
                curr_vert = curr_edge->vertexes[0];
                queue.Insert(curr_edge,curr_edge->weight);
            }
        }
    }
    Vertex<TV,TE>* curr_vert2;
    while(!queue.IsEmpty()){
        curr_edge = queue.front();
        curr_vert = curr_edge->vertexes[0];
        curr_vert2 = curr_edge->vertexes[1];
        if(!ds.IsConnected(curr_vert->id,curr_vert2->id)){
            cout << "{"<< curr_vert->data<<",";
            cout << curr_vert2->data<<"} ";
            // if(s_id != curr_vert->id)
            ds.UnionD(curr_vert->id,curr_vert2->id);
            // ds.UnionD(s_id,curr_vert->id);
        }
        queue.pop_front();

        
    }
}

template<typename TV, typename TE>
bool Kruskal_A<TV,TE>::contains(list<string> &listOfElements, const string &element){
    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}