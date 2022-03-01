#ifndef DFS_H
#define DFS_H

#include "../graph.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

template<typename TV,typename TE>
class DFS{
public:
    Graph<TV,TE>* graph;
    string id_start;

    DFS(Graph<TV,TE>* graph, string vertex){
        this->graph = graph;
        this->id_start= vertex;
    }
    Graph<TV, TE>* apply();
};


template<typename TV, typename TE>
Graph<TV, TE>* DFS<TV, TE>::apply(){
    //DFS ALGORITHM
    Vertex<TV, TE>* curr_vert;
    Edge<TV, TE>* curr_edge;
    queue<Vertex<TV, TE> *> queue;
    list<Edge<TV,TE>*> Edgelist;
    list<string> visited;
    vector<Edge<TV, TE> *> e_result;
    // vector<Vertex<TV, TE> *> result;
    stack<Vertex<TV,TE>*> stack;
    
    curr_vert = graph->Getbegin();
    stack.push(curr_vert);
    visited.push_back(curr_vert->id);
    int n = 0;
    while(!stack.empty()){
        Vertex<TV,TE>* vert = stack.top();
        stack.pop();

        if(!contains(visited,vert->id)){
            // result.push_back(vert);
            visited.push_back(vert->id);
        }
        Edgelist = vert->edges;
        if(Edgelist.size() > 0){
            for(auto it = Edgelist.begin(); it != Edgelist.end();++it){
                curr_edge = *it;
                curr_vert = curr_edge->vertexes[1];
                if(!contains(visited,curr_vert->id)){
                    stack.push((*it)->vertexes[1]);
                    visited.push_back(curr_vert->id);
                    e_result.push_back(curr_edge);
                }

                curr_vert = curr_edge->vertexes[0];
                if(!contains(visited,curr_vert->id)){
                    stack.push((*it)->vertexes[0]);
                }
            }
        }
    }

    Graph<TV, TE>* result = new DirectedGraph<TV,TE>();
    visited.clear();
    for(auto it = e_result.begin(); it != e_result.end(); it++){
        Edge<TV,TE>* temp = *it;
        // insert vertex
        if(!contains(visited,temp->vertexes[0]->id))
            result->insertVertex(temp->vertexes[0]->id,temp->vertexes[0]->data);
        if(!contains(visited,temp->vertexes[1]->id))
            result->insertVertex(temp->vertexes[1]->id,temp->vertexes[1]->data);
        // create edge
        result->createEdge(temp->vertexes[0]->id,temp->vertexes[1]->id,temp->weight);
        // cout << temp->vertexes[0]->id << " ";
        // cout << temp->vertexes[1]->id << " ";
        // cout << endl;
    }

    return result;
}

#endif
