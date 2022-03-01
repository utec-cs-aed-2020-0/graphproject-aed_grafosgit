#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
    Edge(){
        weight = 0;
    }
    Edge(TE peso){
        weight = peso;
    }
    Edge(Vertex<TV, TE>* v1, Vertex<TV, TE>* v2, TE weight) {
        this->vertexes[0] = v1;
        this->vertexes[1] = v2;
        this->weight = weight;
    }
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    string id;
    std::list<Edge<TV, TE>*> edges;
};

template<typename TV, typename TE>
class Graph{
public:
    map<string, Vertex<TV, TE>*>  vertices;
    virtual Vertex<TV, TE>* Getbegin() = 0;
    virtual Vertex<TV, TE>* Getend() = 0;
    virtual bool insertVertex(string id, TV vertex) = 0; // done
    virtual bool createEdge(string id1, string id2, TE w) = 0; // done
    virtual bool deleteVertex(string id) = 0; // done
    virtual bool deleteEdge(string start,string end) = 0; // done
    virtual TE &operator()(string start, string end)= 0; // done
    virtual float density() = 0; // done 
    virtual bool isDense(float threshold = 0.5) = 0; // done 
    virtual bool isConnected()= 0; // done 
    virtual bool isStronglyConnected() = 0; // done
    virtual bool empty() = 0; // done 
    virtual void clear()= 0; // done 

    virtual void displayVertex(string id)= 0; // done
    virtual bool findById(string id) = 0; // done 
    virtual void display() = 0; // done 
    virtual Vertex<TV,TE>* GetVertex(string id) = 0;
    virtual float GetNumOfVert() = 0;
    virtual float GetNumOfEdge() = 0;
    virtual TE peso(Vertex<TV, TE>* start, Vertex<TV, TE>* end) = 0;
};

#endif
