#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <unordered_map>
#include <list>
#include <vector>
#include <stack>

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE> {
private:
    float n_vertices;
    float n_aristas;

public:

    UnDirectedGraph() {
        n_vertices = 0;
        n_aristas = 0;
    }

    bool insertVertex(string id, TV vertex) {

      if(!findById(id)){
          Vertex<TV, TE>* vertex_created = new Vertex<TV, TE>(vertex);
          this->vertexes.insert_or_assign(id, vertex_created);
          n_vertices++;
          return true;
      }
      return false;
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
        Edge<TV, TE>* edge_created = new Edge<TV, TE>(w);
        auto vertex_id1 = this->vertexes.find(id1)->second;
        auto vertex_id2 = this->vertexes.find(id2)->second;
        edge_created->vertexes[0] = vertex_id1;
        edge_created->vertexes[1] = vertex_id2;
        vertex_id1->edges.push_back(edge_created);
        vertex_id2->edges.push_back(edge_created);
        n_aristas++;
        return true;
    }
    bool deleteVertex(string id) {
        unordered_map<TV, string> hash_data_id;

        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            hash_data_id.insert_or_assign( ite_vertices->second->data , ite_vertices->first );
        }

        auto ite_eliminar = this->vertexes.find(id)->second->edges.begin();

        for (auto ite_aristas = this->vertexes.find(id)->second->edges.begin(); ite_aristas != this->vertexes.find(id)->second->edges.end();) {
            if ((*ite_aristas)->vertexes[0] == this->vertexes.find(id)->second) {
                ite_eliminar = ite_aristas;
                ite_aristas++;
                deleteEdge( id, hash_data_id[ (*ite_eliminar)->vertexes[1]->data ] );
            }
            else if ((*ite_aristas)->vertexes[0] == this->vertexes.find(id)->second) {
                ite_eliminar = ite_aristas;
                ite_aristas++;
                deleteEdge( id, hash_data_id[ (*ite_aristas)->vertexes[0]->data ] );
            }
            else {
                ite_aristas++;
            }
        }

        this->vertexes.erase(this->vertexes.find(id));
        n_vertices--;

        return true;
    }
    bool deleteEdge(string id_start,string id_end){
        list<Edge<TV, TE>*>* lista_aristas;

        lista_aristas = &this->vertexes.find(id_start)->second->edges;

        for (auto ite_aristas_1 = lista_aristas->begin(); ite_aristas_1 != lista_aristas->end();) {
            if ( ((*ite_aristas_1)->vertexes[0] == this->vertexes.find(id_end)->second) | ((*ite_aristas_1)->vertexes[1] == this->vertexes.find(id_end)->second) ) {
                lista_aristas->erase(ite_aristas_1);
                break;
            }
            else {
                ++ite_aristas_1;
            }
        }

        lista_aristas = &this->vertexes.find(id_end)->second->edges;

        for (auto ite_aristas_2 = lista_aristas->begin(); ite_aristas_2 != lista_aristas->end();) {
            if (((*ite_aristas_2)->vertexes[0] == this->vertexes.find(id_end)->second) | ((*ite_aristas_2)->vertexes[1] == this->vertexes.find(id_end)->second)) {
                lista_aristas->erase(ite_aristas_2);
                break;
            }
            else {
                ++ite_aristas_2;
            }
        }

        n_aristas--;

        return true;
    }
    TE& operator()(string start, string end) {
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
    float density() {
        float resultado = (2*n_aristas)/(n_vertices*(n_vertices-1));
        return resultado;
    }
    bool isDense(float threshold = 0.5) {
        if (density() > threshold) {
            return true;
        }
        return false;
    }
    bool isConnected() {

        unordered_map<Vertex<TV,TE>*, bool> hash_data_visited;
        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            hash_data_visited.insert_or_assign(ite_vertices->second, false);
        }

        stack<Vertex<TV, TE>*> stack_vertices;
        stack< list<Edge<TV,TE>*>::iterator > stack_iterators;
        int vertices_encontrados=1;
        Vertex<TV, TE>* vertice = this->vertexes.begin()->second;
        auto ite_arista = vertice->edges.begin();
        bool arista_encontrada = false;



        //cout << "\n*******n_vertices=" << n_vertices << endl;
        while ( vertices_encontrados != n_vertices ) {
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
                    /*
                    if (ite_arista == vertice->edges.end()) {
                        cout << "\nSIGUIENTE ELEMENTO NULO";
                    }
                    */
                    //cout << "\nCASO-ARISTA NO VALIDA" << endl;
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
                    stack_iterators.push(ite_arista);
                    ite_arista = vertice->edges.begin();
                    vertices_encontrados++;
                    //cout << "\nCASO-ARISTA ENCONTRADA" << endl;
                }
            }

            else {
                if (stack_vertices.empty() == true) {
                    //cout << "\nCASO - NO SE ENCONTRO ARISTA NI OTRO VERTICE EN EL STACK" << endl;
                    return false;
                }
                else {
                    hash_data_visited.insert_or_assign(vertice, true);
                    vertice = stack_vertices.top();
                    stack_vertices.pop();
                    ite_arista = stack_iterators.top();
                    stack_iterators.pop();
                    hash_data_visited.insert_or_assign(vertice, false);
                    //cout << "\nCASO - NO SE ENCONTRO ARISTA PERO SI UN VERTICE EN EL STACK" << endl;
                }

            }

        }

        return true;

    }
    bool isStronglyConnected() {
        throw("NO SE IMPLEMENTA PARA GRAFOS NO DIRIGIDOS");
    }
    bool empty() {
        return this->vertexes.empty();
    }
    void clear() {
        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            deleteVertex( ite_vertices->first );
        }
    }

    void displayVertex(string id) {
        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            cout << "\nVERTICE:" << ite_vertices->first << "=" << ite_vertices->second->data << endl;
        }
    }
    bool findById(string id) {
        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            if (ite_vertices == id) {
                return true;
            }
        }
        return false;
    }
    void display() {
        cout << "\nDISPLAY:\n";
        for (auto ite_vertices = this->vertexes.begin(); ite_vertices != this->vertexes.end(); ite_vertices++) {
            cout << "\nVERTICE:" << ite_vertices->first << "=" << ite_vertices->second->data << endl;
            cout << "ARISTAS:[";
            auto ite_aristas = ite_vertices->second->edges.begin();
            if (ite_vertices->second->edges.begin() == ite_vertices->second->edges.end()) {
                cout << "NO HAY ARISTAS ASOCIADAS";
            }
            for (auto ite_aristas = ite_vertices->second->edges.begin(); ite_aristas != ite_vertices->second->edges.end(); ite_aristas++) {
                cout << "(" << (*ite_aristas)->vertexes[0]->data << "," << (*ite_aristas)->vertexes[1]->data << "," << "peso=" << (*ite_aristas)->weight << ")";
            }
            cout << "]\n";
        }
        cout << "\n";
    }


};

#endif
