#ifndef BFS_H
#define BFS_H

#include "../graph.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

template<typename TV,typename TE>
class BFS{
public:
    Graph<TV, TE>* graph;
    string start_id;

    BFS(Graph<TV, TE> *graph, string vertex){
        this->graph = graph;
        this->start_id = vertex;
    }
    vector<Vertex<TV , TE>*> apply();
};

template<typename TV,typename TE>
vector<Vertex<TV, TE> *> BFS<TV, TE>::apply() {
    //BFS ALGORITHM
    vector<Vertex<TV, TE> *> result;
    unordered_map<Vertex<TV, TE>* , bool> visited;

    auto it = this->graph->vertexes.begin();
    while (it != this->graph->vertexes.end()) {
        visited[it->second] = false;
        it++;
    }

    queue<Vertex<TV, TE> *> queue;
    visited[this->graph->vertexes[this->start_id]] = true;

    queue.push(this->graph->vertexes[this->start_id]);

    while(!queue.empty()){
        Vertex<TV , TE>* temp = queue.front();
        result.push_back(temp);
        queue.pop();

        for(auto it = temp->edges.begin() ; it != temp->edges.end() ; ++it){
            if(!visited[(*it)->vertexes[0]]){
                visited[(*it)->vertexes[0]] = true;
                queue.push((*it)->vertexes[0]);
            }

            if(!visited[(*it)->vertexes[1]]){
                visited[(*it)->vertexes[1]] = true;
                queue.push((*it)->vertexes[1]);
            }
        }
    }

    return result;

}

#endif
