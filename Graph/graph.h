#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <map>

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

    Vertex(TV value, const string& id){
        data = value;
        this->id = id;
    }
};

template<typename TV, typename TE>
class Graph{
/*private:
    map<string, Vertex<TV, TE>*>  vertexes;
*/
// public:
    // bool insertVertex(string id, TV vertex) = 0;
    // bool createEdge(string id1, string id2, TE w) = 0;
    // bool deleteVertex(string id) = 0;
    // bool deleteEdge(string id) = 0;
    // TE &operator()(string start, string end)= 0;
    // float density() = 0;
    // bool isDense(float threshold = 0.5) = 0;
    // bool isConnected()= 0;
    // bool isStronglyConnected() throw();
    // bool empty();
    // void clear()= 0;

    // void displayVertex(string id)= 0;
    // bool findById(string id) = 0;
    // void display() = 0;
public:
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;

public:
    virtual bool insertVertex(string id, TV vertex) = 0;
    virtual bool createEdge(string id1, string id2, TE w) = 0;
    virtual bool deleteVertex(string id) = 0;
    virtual bool deleteEdge(string id) = 0;
    virtual TE &operator()(string start, string end)= 0;
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected()= 0;
    virtual bool isStronglyConnected() = 0;
    virtual bool empty();
    virtual void clear()= 0;

    virtual void displayVertex(string id)= 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;
};

#endif
