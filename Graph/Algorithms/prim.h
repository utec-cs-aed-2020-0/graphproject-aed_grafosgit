#include <iostream>
#include <list>
#include "priorityqueue.h"
#include "../DirectedGraph.h"
#include "../DSets.h"
#include "../graph.h"
template<typename TV, typename TE>
class Prim_A{
    public:
        template<typename T>
        void prim(DirectedGraph<TV, TE>  Graph, T id){
            int n = 0; // 0. We need to check if we hit every vertex
            int i = 0;
            DisjoinSetArray<string> ds(100);
            Vertex<TV,TE>* curr_vert = Graph.GetVertex(id); // 1. we start by a vertex and get the list of edges
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
            ds.Insert(curr_vert->data);
            curr_vert = nxt_edge->vertexes[1];
            ds.Insert(curr_vert->data);
            queue.pop_front();
            ds.UnionD("A","D");
            while(n < (Graph.GetNumOfVert()-2) || queue.IsEmpty() ){
                EdgeList = curr_vert->edges;
                if(EdgeList.size() > 0){
                    if(i == 3)
                        throw "nope";
                    for(auto it = EdgeList.begin(); it != EdgeList.end(); it++){
                        curr_edge = *it;
                        Vertex<TV,TE>* start  = curr_edge->vertexes[0];
                        Vertex<TV,TE>* end =  curr_edge->vertexes[1];
                        if(!ds.FindElement(end->data)){
                            queue.Insert(curr_edge,curr_edge->weight);
                        }
                    }
                }
                nxt_edge = queue.front();
                curr_vert = nxt_edge->vertexes[1];
                if(!ds.FindElement(curr_vert->data)){
                    result.push_back(nxt_edge);
                    n +=1 ;
                    ds.Insert(curr_vert->data);
                    cout << n << "\n";
                }
                queue.pop_front();
                i++;

            }
            for(auto it = result.begin(); it != result.end(); it++){
                curr_edge = *it;
                curr_vert = curr_edge->vertexes[0];
                cout << "{"<< curr_vert->data<<",";
                curr_vert = curr_edge->vertexes[1];
                cout << curr_vert->data<<"} ";
            }
        }
};