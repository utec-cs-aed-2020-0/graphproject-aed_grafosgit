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
    vector<Vertex<TV, TE>*> apply();
};


template<typename TV, typename TE>
vector<Vertex<TV, TE> *> DFS<TV, TE>::apply(){
    //DFS ALGORITHM
    vector<Vertex<TV,TE>*> result;
    unordered_map<Vertex<TV,TE>*,bool> visited;
    auto it = this->graph->vertexes.begin();
    while (it != this->graph->vertexes.end()){
        visited[it->second] = false;
        it++;
    }
    stack<Vertex<TV,TE>*> stack;
    stack.push(this->graph->vertexes[this->id_start]);

    while(!stack.empty()){
        Vertex<TV,TE>* vert = stack.top();
        stack.pop();

        if(!visited[vert]){
            result.push_back(vert);
            visited[vert] = true;
        }

        for(auto it = vert->edges.begin(); it != vert->edges.end();++it){
            if(!visited[(*it)->vertexes[1]]){
                stack.push((*it)->vertexes[1]);
            }
            if(!visited[(*it)->vertexes[0]]){
                stack.push((*it)->vertexes[0]);
            }
        }
    }
    return result;
}

#endif
