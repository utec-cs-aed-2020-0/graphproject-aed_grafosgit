#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <iostream>
#include <string>
#include "graph.h"
#include "DSets.h"
#include <exception>
#include <list> 
#include <stack>

using namespace std;

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE> {
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
    bool insertVertex(string id, TV vertex) {
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

    bool createEdge(string id1, string id2, TE w) {
        if(!findById(id1) || !findById(id2)){
            throw invalid_argument("IDs not found.");
            return false;
        }
        if(id1 == id2){
          throw invalid_argument("IDs are same");
          return false;
        }
        // There must be at least 2 vertices
        if(vertices.size() < 2)
            return false;
        // Check if there's room for more
        if((vertices.size()*(vertices.size()-1)/2) == NumOfEdges ) // full of edges
            return false;
        // look for the vertices in the map and assign them to the list
        if(NodesConnected(id1,id2))
            return false;
        Edge<TV, TE>* newEdge1 = new Edge<TV, TE>(); // create newEdge
        Edge<TV, TE>* newEdge2 = new Edge<TV, TE>(); // create newEdge
        Vertex<TV, TE>* v_temp1 = new Vertex<TV, TE>();
        Vertex<TV, TE>* v_temp2 = new Vertex<TV, TE>();
        newEdge1->weight = w;
        newEdge2->weight = w;
        for(auto it = vertices.begin(); it != vertices.end(); ++it){
            if(it->first == id1){ // find start vertex
                v_temp1 = it-> second;
                newEdge1->vertexes[0] = it->second; // add vertex to edge
                newEdge2->vertexes[1] = it->second; // add vertex to edge
            }
            if(it->first == id2){ // find end vertex
                v_temp2 = it->second;
                newEdge1->vertexes[1] = it->second; // add vertex to edge
                newEdge2->vertexes[0] = it->second; // add vertex to edge
            }
        }
        v_temp1->edges.push_back(newEdge1);
        v_temp2->edges.push_back(newEdge2);
        NumOfEdges++;
        return true;
    }
    bool deleteVertex(string id) {
        bool result = false;
            Vertex<TV,TE>* temp = new Vertex<TV,TE>();
            for(auto it = vertices.begin(); it != vertices.end(); it++){
                temp = it->second;
                if(temp->edges.size() > 0)
                    deleteEdge(id, temp->edges);
                
            }
            vertices.erase(id);
            NumOfVerticies--;
            return true;
        return true;
    }

    Vertex<TV,TE>* GetVertex(string id) {
        Vertex<TV,TE>* temp = new Vertex<TV,TE>();
        for(auto it = vertices.begin(); it != vertices.end(); it++){
            if(it->first == id)
                temp = it->second;
        }
        return temp;
    }

    bool deleteEdge(string start, string end){
        Vertex<TV,TE>* v_temp = new Vertex<TV,TE>();
        Edge<TV, TE>* edge;
        for(auto it = vertices.begin(); it != vertices.end();it++){
            if(it->first == start){
                v_temp = it->second;
                if(v_temp->edges.size() > 0){
                    for(auto ite = v_temp->edges.begin(); ite != v_temp->edges.end();ite++){
                        edge = *ite;
                        if(edge->vertexes[1]->id == end){
                            v_temp->edges.erase(ite);
                        }
                    }
                }
            }
            if(it->first == end){
                v_temp = it->second;
                if(v_temp->edges.size() > 0){
                    for(auto ite = v_temp->edges.begin(); ite != v_temp->edges.end();ite++){
                        edge = *ite;
                        if(edge->vertexes[0]->id == end){
                            v_temp->edges.erase(ite);
                        }
                    }
                }
            }
        }
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

    TE& operator()(string start, string end) {
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

    TE peso(Vertex<TV,TE>* start, Vertex<TV, TE>* end) {
        TE peso;
        for (auto ite_aristas_1 = start->edges.begin(); ite_aristas_1 != start->edges.end();) {
            if ( ( (*ite_aristas_1)->vertexes[0] == end) | ( (*ite_aristas_1)->vertexes[1] ==end) ) {
                return (*ite_aristas_1)->weight;
                break;
            }
            else {
                ++ite_aristas_1;
            }
        }
        return peso;
    }


    float density() {
        float resultado = (2*NumOfEdges)/(NumOfVerticies*(NumOfVerticies-1));
        return resultado;
    }
    bool isDense(float threshold = 0.5) {
        return density() >= threshold;
    }
    
    bool isConnected() {

        unordered_map<Vertex<TV,TE>*, bool> hash_data_visited;
        for (auto ite_vertices = this->vertices.begin(); ite_vertices != this->vertices.end(); ite_vertices++) {
            hash_data_visited.insert_or_assign(ite_vertices->second, false);
        }

        stack<Vertex<TV, TE>*> stack_vertices;
        stack< int > stack_iterators;
        int ite_num = 0;
        int vertices_encontrados=1;
        Vertex<TV, TE>* vertice = this->vertices.begin()->second;
        auto ite_arista = vertice->edges.begin();
        bool arista_encontrada = false;
        

        
        //cout << "\n*******n_vertices=" << n_vertices << endl;
        while ( vertices_encontrados != NumOfVerticies ) {
            /*
            cout << "\nVERTICE_VISITADO=" << vertice->data;
            cout << "\nvertices_visitados.size()=" << vertices_encontrados;
            if (ite_arista != vertice->edges.end()) {
                cout << "\nARISTA=(" << (*ite_arista)->vertexes[0]->data << "," << (*ite_arista)->vertexes[1]->data << "," << "peso=" << (*ite_arista)->weight << ")";
            }
            if (stack_vertices.size() > 0) {
                cout << "\nSTACK - VERTICES(TOP)=" << stack_vertices.top()->data;
            }
            */

            if ( ite_arista != vertice->edges.end() ) {
                //cout << "\nARISTA ENCONTRADA";
                if ( ( hash_data_visited[(*ite_arista)->vertexes[0]] == true ) | ( hash_data_visited[(*ite_arista)->vertexes[1]] == true ) ) {
                    ite_arista++;
                    ite_num++;
                    /*
                    if (ite_arista == vertice->edges.end()) {
                        cout << "\nSIGUIENTE ELEMENTO NULO";
                    }
                    cout << "\nCASO-ARISTA NO VALIDA" << endl;
                    */
                }

                else {
                    stack_vertices.push(vertice);
                    hash_data_visited.insert_or_assign(vertice, true);
                    if ((*ite_arista)->vertexes[0] == vertice) {
                        vertice = (*ite_arista)->vertexes[1];
                    }
                    else {
                        vertice = (*ite_arista)->vertexes[0];
                    }
                    ite_arista++;
                    ite_num++;
                    stack_iterators.push(ite_num);
                    ite_arista = vertice->edges.begin();
                    ite_num = 0;
                    vertices_encontrados++;
                    //cout << "\nCASO-ARISTA ENCONTRADA" << endl;
                }
            }

            else {
                //cout << "\nNO HAY ARISTAS";
                if (stack_vertices.empty() == true) {
                    //cout << "\nCASO - NO SE ENCONTRO ARISTA NI OTRO VERTICE EN EL STACK" << endl;
                    return false;
                }
                else {
                    //cout << "\nCASO - NO SE ENCONTRO ARISTA PERO SI UN VERTICE EN EL STACK" << endl;
                    hash_data_visited.insert_or_assign(vertice, true);
                    vertice = stack_vertices.top();
                    stack_vertices.pop();
                    ite_num = stack_iterators.top();
                    stack_iterators.pop();
                    ite_arista = vertice->edges.begin();
                    advance( ite_arista , ite_num );
                    hash_data_visited.insert_or_assign(vertice, false);
                }   
            }
        }
        return true;
    }


    bool isStronglyConnected() {
        throw("NO SE IMPLEMENTA PARA GRAFOS NO DIRIGIDOS");
        return false;
    }
    bool empty() {
        return (NumOfVerticies == 0);
    }
    void clear() {
        for(auto it = vertices.begin(); it != vertices.end(); it++) {
            Vertex<TV,TE>* del = it->second;
            delete(del);
        }
        NumOfVerticies = 0;
        NumOfEdges = 0; 
        vertices.clear();
    }

    void displayVertex(string id) {
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
    bool findById(string id) {
        for(auto it = vertices.begin(); it != vertices.cend();it++){
            if(it->first == id){
                return true;
            }
        }
        return false;
    }
    void display() {
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


};

#endif
