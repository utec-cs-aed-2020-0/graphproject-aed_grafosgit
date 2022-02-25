#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include "DSets.h"
#include <exception>
using namespace std;
template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    private:
        int NumOfEdges = 0;
        int NumOfVerticies = 0;
    public:
        map<string, Vertex<TV,TE>*>  vertices;
        int GetNumOfVert(){return NumOfVerticies;}

        bool insertVertex(string id, TV vertex){
            bool result = false;
            Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
            newVertex->data = vertex;
            try{
                vertices.insert(pair<string, Vertex<TV,TE>*>(id , newVertex));
                NumOfVerticies++;
                result = true;
            }
            catch (...){
                cout << "Could not insert: "<< endl;
            }
            return result;
        }
        bool createEdge(string id1, string id2, TE w){
            // There must be at least 2 vertices
            if(vertices.size() < 2)
                return false;
            // Check if there's room for more
            if((vertices.size()*(vertices.size()-1)/2) == NumOfEdges ) // full of edges
                return false;
            // look for the vertices in the map and assign them to the list
            Edge<TV, TE>* newEdge = new Edge<TV, TE>(); // create newEdge
            newEdge->weight = w;
            for(auto it = vertices.begin(); it != vertices.end(); ++it){
                if(it->first == id1){ // find start vertex
                    newEdge->vertexes[0] = it->second; // add vertex to edge
                    it->second->edges.push_back(newEdge); // add edge to vertex
                }
                if(it->first == id2){ // find end vertex
                    newEdge->vertexes[1] = it->second; // add vertex to edge
                    // this edge is not added to the end vertex because it's a directed graph
                }
            }
            return true;
        }

        bool deleteVertex(string id){
            return false;
        }

        bool deleteEdge(string id){
            return false;
        }

        TE &operator()(string start, string end){
          TE peso = 0;
          TE* p_peso = &peso;
          for (auto ite_aristas_1 = this->vertexes.find(start)->second->edges.begin(); ite_aristas_1 != this->vertexes.find(start)->second->edges.end();) {
              if (((*ite_aristas_1)->vertexes[0] == this->vertexes.find(end)->second) | ((*ite_aristas_1)->vertexes[1] == this->vertexes.find(end)->second)) {
                  return (*ite_aristas_1)->weight;
                  break;
              }
              else {
                  ++ite_aristas_1;
              }
          }
          return *p_peso;
        }

        float density(){
          float resultado = (2*NumOfEdges)/(NumOfVerticies*(NumOfVerticies-1));
          return resultado;
        }

        bool isDense(float threshold = 0.5){
            return density() >= threshold;
        }

        bool isConnected(){
          cout << "\n--- ERROR: This is directed graph\n";
          return false;
        }

        // TO DO
        bool isStronglyConnected(){
            return false;
        }

        bool empty(){
            return (this->vertexes.size() == 0);
        }

        void clear(){
          for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
              deleteVertex( ite_vertices->first );
          }
        }

        void displayVertex(string id){
            Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
            list<Edge<TV, TE>*> e_temp;
            for(auto it = vertices.begin(); it != vertices.cend();it++){
                if(it->first == id){
                    cout << it->first << "\n";
                    v_temp = it->second;
                    e_temp = v_temp->edges;
                    cout << v_temp->data << "\n";
                    cout << "Edges: \n";
                    break;
                }
            }
        }

        Vertex<TV,TE>* GetVertex(string id){
            Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
            for(auto it = vertices.begin(); it != vertices.end();it++){
                if(it->first == id)
                    return it->second;
            }
            cout << "not found returning an empty vertex";
            return v_temp;
        }

        bool findById(string id){
            for(auto it = vertices.begin(); it != vertices.cend();it++){
                if(it->first == id){
                    return true;
                }
            }
            return false;
        }

        void display(){
          if(empty()){
            cout << "Empty Graph\n";
            return;
          }
          for(auto p : this->vertexes){
              cout << "ID: " << p.first << " | Vertex: (" << p.second->data << ") | Number of Edges: <" << p.second->edges.size() << ">:\n";
              for(auto it = begin(p.second->edges); it != end(p.second->edges); ++it)
                  cout << "\t" << "Vertex " << (*it)->vertexes[1]->data << " ---> Weight (" << (*it)->weight << ")\n";
              cout << "\n";
          }
        }

        void display_edges(string id){
            list<Edge<TV, TE>*> ListOfEdges;
            for(auto it = vertices.begin(); it != vertices.end();it++){
                if(it->first == id){
                    ListOfEdges = it->second->edges;
                    break;
                }
            }
            Edge<TV, TE>* temp = new Edge<TV, TE>();
            Vertex<TV,TE>* v1_temp = new Vertex<TV,TE>();
            Vertex<TV,TE>* v2_temp = new Vertex<TV,TE>();
            for(auto it = ListOfEdges.begin(); it != ListOfEdges.end(); it++){
                temp = *it;
                v1_temp = temp->vertexes[0];
                v2_temp = temp->vertexes[1];
                cout << "Start: "<<v1_temp->data << " End: "<< v2_temp->data<< "\n";
                cout << "Weigth of Edge: " << temp->weight << "\n";

            }
        }

};

#endif
