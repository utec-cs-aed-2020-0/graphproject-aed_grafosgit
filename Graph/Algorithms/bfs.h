#ifndef BFS_H
#define BFS_H

#include "../graph.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <list>
template<typename TV,typename TE>
class BFS{
public:
    Graph<TV, TE>* graph;
    string start_id;

    BFS(Graph<TV, TE> *graph, string vertex){
        this->graph = graph;
        this->start_id = vertex;
    }
    Graph<TV, TE>* apply();
};

bool contains(list<string> &listOfElements, const string &element){
    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

template<typename TV,typename TE>
Graph<TV, TE>* BFS<TV, TE>::apply() {
    //BFS ALGORITHM
    DisjoinSetArray<string> ds(3500);
    Vertex<TV, TE>* curr_vert;
    Edge<TV, TE>* curr_edge;
    queue<Vertex<TV, TE> *> queue;
    list<Edge<TV,TE>*> Edgelist;
    list<string> visited;
    vector<Edge<TV, TE> *> e_result;
    

    curr_vert = graph->Getbegin();
    queue.push(curr_vert);
    visited.push_back(curr_vert->id);
    ds.Insert(curr_vert->id);
    int n = 0;
    map<string,Vertex<TV,TE>*> grph = graph->getMap();
    for( auto it = grph.begin(); it != grph.end(); it++){
        curr_vert = queue.front();
        // result.push_back(curr_vert);
        if(!ds.FindElement(curr_vert->id))
            ds.Insert(it->second->id);
        Edgelist = curr_vert->edges;
        if(Edgelist.size() > 0){
            for( auto ite = Edgelist.begin(); ite != Edgelist.end(); ite++){
                // throw "nope";
                curr_edge = *ite;
                
                curr_vert = curr_edge->vertexes[1];
                if(!ds.FindElement(curr_vert->id))
                    ds.Insert(curr_vert->id);
                if(!contains(visited,curr_vert->id)){
                    queue.push(curr_vert);
                    e_result.push_back(curr_edge);
                    n++;
                }
                // ++ite;
            }
        }
        queue.pop();
    }
    Graph<TV, TE>* result = new DirectedGraph<TV,TE>();
    visited.clear();
    for(auto it = e_result.begin(); it != e_result.end(); it++){
        Edge<TV,TE>* temp = *it;
        
        if(!ds.IsConnected(temp->vertexes[0]->id,temp->vertexes[1]->id)){
            // cout << temp->vertexes[0]->id << " ";
            // cout << temp->vertexes[1]->id << " ";
            result->insertVertex(temp->vertexes[0]->id,temp->vertexes[0]->data);
            result->insertVertex(temp->vertexes[1]->id,temp->vertexes[1]->data);
            result->createEdge(temp->vertexes[0]->id,temp->vertexes[1]->id,temp->weight);
            ds.UnionD(temp->vertexes[0]->id,temp->vertexes[1]->id);
        }
    }

    return result;

}

#endif
