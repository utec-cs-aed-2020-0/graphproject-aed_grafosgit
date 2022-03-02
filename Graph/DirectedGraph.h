#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H
#include <iostream>
#include <string>
#include "graph.h"
#include "DSets.h"
#include <exception>
using namespace std;
template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    private:
        float NumOfEdges = 0;
        float NumOfVerticies = 0;
    public:
        map<string, Vertex<TV,TE>*>  vertices;
        float GetNumOfVert(){return NumOfVerticies;}
        float GetNumOfEdge(){return NumOfEdges;}
        Vertex<TV, TE>* Getbegin(){ 
            Vertex<TV, TE>* bgn = new Vertex<TV, TE>();
            auto it = vertices.begin();
            bgn = it->second;
            return bgn;
        }
        Vertex<TV, TE>* Getend(){ 
            Vertex<TV, TE>* bgn = new Vertex<TV, TE>();
            auto it = vertices.end();
            bgn = it->second;
            return bgn;
        }
        bool insertVertex(string id, TV vertex){
            bool result = false;
            if(findById(id))
                return false;
            Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
            newVertex->data = vertex;
            newVertex->id = id;
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
            NumOfEdges++;
            return true;
        }

        bool deleteVertex(string id){
            bool result = false;
            Vertex<TV,TE>* temp = new Vertex<TV,TE>();
            for(auto it = vertices.begin(); it != vertices.end(); it++){
                temp = it->second;
                deleteEdge(id, temp->edges);
            }
            vertices.erase(id);
            NumOfVerticies--;
            return true;
        }

        bool deleteEdge(string start, string end){
            Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
            Edge<TV, TE>* edge;
            for(auto it = vertices.begin(); it != vertices.end();it++){
                if(it->first == start){
                    v_temp = it->second;
                    for(auto ite = v_temp->edges.begin(); ite != v_temp->edges.end();ite++){
                        edge = *ite;
                        if(edge->vertexes[1]->id == end){
                            v_temp->edges.erase(ite);
                            NumOfEdges--;
                            return true;
                        }
                    }
                }
            }
            cout << "No connection between vertex " << start << " and " << end  <<" returning an empty value "<< endl;
            return true;
        }

        void deleteEdge(string end, list<Edge<TV,TE>*> &listedge){
            Edge<TV, TE>* edge;
            for(auto ite = listedge.begin(); ite != listedge.end();ite++){
                edge = *ite;
                if(edge->vertexes[1]->id == end){
                    listedge.erase(ite);
                    NumOfEdges--;
                    return;
                }
            }
        }
        
        TE &operator()(string start, string end){
            Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
            list<Edge<TV, TE>*> e_temp;
            Edge<TV, TE>* edge;
            for(auto it = vertices.begin(); it != vertices.end();it++){
                if(it->first == start){
                    v_temp = it->second;
                    e_temp = v_temp->edges;
                    for(auto ite = e_temp.begin(); ite != e_temp.end();ite++){
                        edge = *ite;
                        if(edge->vertexes[1]->id == end)
                            return edge->weight;
                    }
                }
            }
          cout << "No connection between vertex " << start << " and " << end  <<" returning an empty value "<< endl;
          return edge->weight;
        }

        TE peso(Vertex<TV, TE>* start, Vertex<TV, TE>* end) {
            TE peso;
            for (auto ite_aristas_1 = start->edges.begin(); ite_aristas_1 != start->edges.end();) {
                if ( (*ite_aristas_1)->vertexes[1] == end) {
                    return (*ite_aristas_1)->weight;
                    break;
                }
                else {
                    ++ite_aristas_1;
                }
            }
            return peso;
        }


        float density(){
          float resultado = (NumOfEdges)/(NumOfVerticies*(NumOfVerticies-1));
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
            list<Edge<TV,TE>*> e_list;
            Vertex<TV,TE>* v_current;
            Edge<TV,TE>* e_current;
            list<string> st;
            int n = 0;
            int numOf_it = 0;
            for(auto it = vertices.begin(); it != vertices.end(); it++){
                e_list = it->second->edges;
                v_current = it->second;
                if(!contains(st,v_current->id)){
                    st.push_back(it->second->id);
                }
                if(e_list.size() > 0){
                    auto ite = e_list.begin();
                    e_current = *ite;
                    while (st.size() < NumOfVerticies && numOf_it < NumOfVerticies){
                        v_current = e_current->vertexes[1];
                        if(!contains(st,v_current->id))
                            st.push_back(v_current->id);
                        if(v_current->edges.size() > 0)
                            ite = v_current->edges.begin();
                        e_current = *ite;
                        numOf_it++;
                    }
                }
                if(st.size() == NumOfVerticies)
                    n++;
                st.clear();
                numOf_it = 0;
            }
            if(n == NumOfVerticies)
                return true;
            else    
                return false;
        }

        bool NodesConnected(string start, string end) {
            Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
            list<Edge<TV, TE>*> e_temp;
            Edge<TV, TE>* edge;
            for(auto it = vertices.begin(); it != vertices.end();it++){
                if(it->first == start){
                    v_temp = it->second;
                    e_temp = v_temp->edges;
                    for(auto ite = e_temp.begin(); ite != e_temp.end();ite++){
                        edge = *ite;
                        if(edge->vertexes[1]->id == end)
                            return true;
                    }
                }
            }
            return false;
        }
        map<string,Vertex<TV,TE>*> getMap(){
        return this->vertices;
    }
        template <typename T>
        bool contains(list<T> &listOfElements, const T &element){
            auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
            return it != listOfElements.end();
        }

        bool empty(){
            return (this->NumOfVerticies == 0);
        }

        void clear(){
            for(auto it = vertices.begin(); it != vertices.end(); it++) {
                Vertex<TV,TE>* del = it->second;
                delete(del);
            }
            NumOfVerticies = 0;
            NumOfEdges = 0; 
            vertices.clear();
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
                    for(auto it = e_temp.begin(); it!= e_temp.end(); it++){
                        cout << (*it)->vertexes[1]-> id << " ";
                        cout << (*it)->weight << endl;
                    }
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
            cout << "not found, returning an empty vertex";
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
          for(auto p : vertices){
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
