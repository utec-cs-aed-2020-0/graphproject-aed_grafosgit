#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <vector>
#include <list>
#include "../UnDirectedGraph.h"
#include "../DirectedGraph.h"
#include "../graph.h"
#include <map>
#include <unordered_map>

template<typename TV, typename TE>
struct nodo_dijkstra{
	TV data_vertice;
	TE peso_total;
	list<TV> camino;
	nodo_dijkstra(TV data, TE peso, list<TV> path ) {
		data_vertice = data;
		peso_total = peso;
		camino = path;
	}
	void display() {
		cout << "\nVERTICE=" << data_vertice;
		cout << "\nPESO TOTAL DEL CAMINO=" << peso_total;
		
		if (peso_total>=10000) {
			cout << "\nNO HAY CAMINO\n";
		}
		else {
			cout << "\nCAMINO=";
			auto ite = camino.begin();
			for (int i = 0; i < camino.size(); i++) {
				if (i != (camino.size() - 1)) {
					cout << *ite << "->";
				}
				else {
					cout << *ite << ".\n";
				}
				ite++;
			}
		}
	}
};

template<typename TV, typename TE>
vector<nodo_dijkstra<TV, TE>*> Dijkstra( Graph<TV,TE>* grafo , string id ) {

	vector<nodo_dijkstra<TV, TE>*> resultado;

	//cout << "\nid=" << id;
	unordered_map<Vertex<TV, TE>*, TE> hash_pesos;
	unordered_map<Vertex<TV, TE>*, TE> hash_visited;
	unordered_map<Vertex<TV, TE>*, Vertex<TV,TE>*> hash_parent;
	int v_visited = 1;
	TE peso = 0;
	TE peso_temp = 0;
	Vertex<TV, TE>* v_temp;
	vector<Vertex<TV, TE>*> camino;
	map<string,Vertex<TV,TE>*> grph = grafo->getMap();
	for (auto ite = grph.begin(); ite != grph.end(); ite++ ) {
		hash_pesos.insert_or_assign( ite->second , 10000 );
		hash_visited.insert_or_assign(ite->second, false);
		hash_parent.insert_or_assign(ite->second, grafo->vertices.find(id)->second);
	}

	Vertex<TV,TE>* vertex = grafo->GetVertex(id);
	// cout << "\ndata=" << vertex->data << endl;
	hash_visited.insert_or_assign(vertex, true);
	hash_pesos.insert_or_assign(vertex, 0);
	while (v_visited < grafo->GetNumOfVert()) {
		// cout << "\n\nV_VISITED=" << v_visited;
		list<Edge<TV,TE>*> Edgelist = vertex->edges;
		
		if(Edgelist.size() > 0){
			for (auto ite_a = Edgelist.begin(); ite_a != Edgelist.end(); ite_a++) {
				if ( (*ite_a)->vertexes[0]==vertex  ){
					v_temp = (*ite_a)->vertexes[1];
				}
				else {
					v_temp = (*ite_a)->vertexes[0];
				}
				
				// cout << "\nvertex->data=" << vertex->data;
				// cout << "\nv_temp->data=" << v_temp->data;
				// cout << "\npeso=" << peso;
				// // cout << "\ngrafo->peso(vertex,v_temp)=" << grafo->peso(vertex, v_temp);
				// cout << "\npeso + grafo->peso(vertex, v_temp)=" << peso + (*grafo)(vertex->id,v_temp->id);
				// cout << "\nhash_pesos.find(v_temp)->second=" << hash_pesos.find(v_temp)->second;
				
				if ((peso + (*grafo)(vertex->id,v_temp->id)) < (hash_pesos.find(v_temp)->second)) {
					//cout << "\nSE INSERTA LA ARISTA CON PESO " << peso + grafo->peso(vertex, v_temp) << " EN " << v_temp->data << endl;
					hash_pesos.insert_or_assign( v_temp, peso + (*grafo)(vertex->id,v_temp->id) );
					/*
					cout << "\nISERTANDO PARENT:";
					cout << "\nv_temp=" << v_temp->data;
					cout << "\nvertex=" << vertex->data << "\n\n";
					*/
					hash_parent.insert_or_assign(v_temp, vertex);
				}
				else {
					//cout << "\nNO SE INSERTO\n";
				}
				
				
			}
			// throw "nope";
		}
		v_temp = vertex;
		peso = 10001;
		for (auto ite_p = hash_pesos.begin(); ite_p != hash_pesos.end(); ite_p++) {
			if (hash_visited.find(ite_p->first)->second == false) {
				/*
				cout << "\nite_p->first->data=" << ite_p->first->data;
				cout << "\nhash_visited.find(ite_p->first)->second=" << hash_visited.find(ite_p->first)->second;
				cout << "\npeso=" << peso;
				cout << "\nite_p->second=" << ite_p->second;
				cout << "\n**************";
				*/
				if (ite_p->second < peso) {
					vertex = ite_p->first;
					peso = ite_p->second;
				}
			}
		}
		//cout << "\n\nSE ESCOGIO EL SIGUIENTE VERTICE=" << vertex->data;
		hash_visited.insert_or_assign(vertex, true);
		v_visited++;
		

	}
	//cout << "\nCREANDO EL RESULTADO:";
	int i = 0;
	auto ite_c = hash_parent.begin();
	Vertex<TV, TE>* vertice_temp;
	for (auto ite_f = hash_pesos.begin(); ite_f != hash_pesos.end() ; ite_f++) {
		
		// cout << "\nite_f->first->data=" << ite_f->first->data;
		// cout << "\nite_f->second(peso final)=" << ite_f->second;
		// cout << "\nite_c->first->data=" << ite_c->first->data;
		// cout << "\nite_c->second->data=" << ite_c->second->data;
		
		vertice_temp = ite_c->second;
		list<TV> vertices;
		// cout << "\nCAMINO=" << ite_c->first->data << "->";
		vertices.push_front(ite_c->first->data);
		while (vertice_temp != grph.find(id)->second) {
			// cout << vertice_temp->data << "->";
			vertices.push_front(vertice_temp->data);
			vertice_temp = hash_parent.find(vertice_temp)->second;
		}
		// cout << vertice_temp->data << ";" << "\n\n";
		vertices.push_front(vertice_temp->data);
		nodo_dijkstra<TV, TE>* nodo = new nodo_dijkstra<TV, TE>(ite_f->first->data, ite_f->second, vertices);
		resultado.push_back(nodo);
		i++;
		ite_c++;
		if(i == grafo->GetNumOfVert() - 1)
			break;
	}
	/*
	cout << "\nCREANDO EL RESULTADO(camino):";
	i = 0;

	for (auto ite_c = hash_parent.begin(); ite_c != hash_parent.end(); ite_c++) {
		

		cout << "\nite_c->first->data=" << ite_c->first->data;
		cout << "\nite_c->second->data=" << ite_c->second->data;
		cout << "\nCAMINO=" << ite_c->first->data << "->";
		while (vertice_temp != grafo->vertexes.find(id)->second ) {
			cout << vertice_temp->data << "->";
			vertice_temp = hash_parent.find(vertice_temp )->second;
		}
		cout << vertice_temp->data << ";";
	}
	*/

	return resultado;
}


// template<typename TV, typename TE>
// vector<nodo_dijkstra<TV, TE>*> Dijkstra(DirectedGraph<TV, TE>* grafo, string id) {

// 	vector<nodo_dijkstra<TV, TE>*> resultado;
// 	//cout << "\nid=" << id;
// 	unordered_map<Vertex<TV, TE>*, TE> hash_pesos;
// 	unordered_map<Vertex<TV, TE>*, TE> hash_visited;
// 	unordered_map<Vertex<TV, TE>*, Vertex<TV, TE>*> hash_parent;
// 	int v_visited = 1;
// 	TE peso = 0;
// 	//cout << "\npeso=" << peso;
// 	TE peso_temp = 0;
// 	Vertex<TV, TE>* v_temp;
// 	vector<Vertex<TV, TE>*> camino;
// 	Vertex<TV, TE>* sin_camino = new Vertex<TV, TE>();
// 	sin_camino->data = 0;

// 	for (auto ite = grafo->vertices.begin(); ite != grafo->vertices.end(); ite++) {
// 		hash_pesos.insert_or_assign(ite->second, 10000);
// 		hash_visited.insert_or_assign(ite->second, false);
// 		hash_parent.insert_or_assign(ite->second, sin_camino);
// 	}

// 	Vertex<TV, TE>* vertex = grafo->vertices.find(id)->second;
// 	//cout << "\ndata=" << vertex->data << endl;
// 	hash_visited.insert_or_assign(vertex, true);
// 	hash_pesos.insert_or_assign(vertex, 0);
// 	hash_parent.insert_or_assign(vertex, vertex);

// 	while (v_visited < grafo->vertices.size()) {
// 		//cout << "\n\nV_VISITED=" << v_visited;
// 		for (auto ite_a = vertex->edges.begin(); ite_a != vertex->edges.end(); ite_a++) {
// 			/*
// 			if ((*ite_a)->vertexes[0] == vertex) {
// 				v_temp = (*ite_a)->vertexes[1];
// 			}
// 			else {
// 				v_temp = (*ite_a)->vertexes[0];
// 			}
// 			*/
// 			v_temp = (*ite_a)->vertexes[1];
// 			//cout << "\nvertex->data=" << vertex->data;
// 			//cout << "\nv_temp->data=" << v_temp->data;
// 			//cout << "\npeso=" << peso;
// 			//cout << "\ngrafo->peso(vertex,v_temp)=" << grafo->peso(vertex, v_temp);
// 			//cout << "\npeso + grafo->peso(vertex, v_temp)=" << peso + grafo->peso(vertex, v_temp);
// 			//cout << "\nhash_pesos.find(v_temp)->second=" << hash_pesos.find(v_temp)->second;
			
// 			if ((peso + grafo->peso(vertex, v_temp)) < (hash_pesos.find(v_temp)->second)) {
// 				//cout << "\nSE INSERTA LA ARISTA CON PESO " << peso + grafo->peso(vertex, v_temp) << " EN " << v_temp->data << endl;
// 				hash_pesos.insert_or_assign(v_temp, peso + grafo->peso(vertex, v_temp));
				
// 				//cout << "\nISERTANDO PARENT:";
// 				//cout << "\nv_temp=" << v_temp->data;
// 				//cout << "\nvertex=" << vertex->data << "\n\n";
				
// 				hash_parent.insert_or_assign(v_temp, vertex);
// 			}
// 			else {
// 				//cout << "\nNO SE INSERTO\n";
// 			}


// 		}
// 		v_temp = vertex;
// 		peso = 10001;
// 		for (auto ite_p = hash_pesos.begin(); ite_p != hash_pesos.end(); ite_p++) {
// 			if (hash_visited.find(ite_p->first)->second == false) {
				
// 				//cout << "\nite_p->first->data=" << ite_p->first->data;
// 				//cout << "\nhash_visited.find(ite_p->first)->second=" << hash_visited.find(ite_p->first)->second;
// 				//cout << "\npeso=" << peso;
// 				//cout << "\nite_p->second=" << ite_p->second;
// 				//cout << "\n**************";
				
// 				if (ite_p->second < peso) {
// 					vertex = ite_p->first;
// 					peso = ite_p->second;
// 				}
// 			}
// 		}
// 		//cout << "\n\nSE ESCOGIO EL SIGUIENTE VERTICE=" << vertex->data;
// 		hash_visited.insert_or_assign(vertex, true);
// 		v_visited++;


// 	}
// 	//cout << "\nCREANDO EL RESULTADO:";
// 	int i = 0;
// 	auto ite_c = hash_parent.begin();
// 	Vertex<TV, TE>* vertice_temp;
// 	for (auto ite_f = hash_pesos.begin(); ite_f != hash_pesos.end(); ite_f++) {
		
// 		//cout << "\nite_f->first->data=" << ite_f->first->data;
// 		//cout << "\nite_f->second(peso final)=" << ite_f->second;
// 		//cout << "\nite_c->first->data=" << ite_c->first->data;
// 		//cout << "\nite_c->second->data=" << ite_c->second->data;
		
// 		vertice_temp = ite_c->second;
// 		list<TV> vertices;
// 		if ( vertice_temp == sin_camino ) {
// 			//cout << "\nNO HAY CAMINO=" << vertices.empty();
// 		}
// 		else {
// 			//cout << "\nCAMINO=" << ite_c->first->data << "->";
// 			vertices.push_front(ite_c->first->data);
// 			while (vertice_temp != grafo->vertexes.find(id)->second) {
// 				//cout << vertice_temp->data << "->";
// 				vertices.push_front(vertice_temp->data);
// 				vertice_temp = hash_parent.find(vertice_temp)->second;
// 			}
// 			//cout << vertice_temp->data << ";" << "\n\n";
// 		}
// 		vertices.push_front(vertice_temp->data);
// 		nodo_dijkstra<TV, TE>* nodo = new nodo_dijkstra<TV, TE>(ite_f->first->data, ite_f->second, vertices);
// 		resultado.push_back(nodo);
// 		i++;
// 		ite_c++;
// 	}
// 	/*
// 	cout << "\nCREANDO EL RESULTADO(camino):";
// 	i = 0;

// 	for (auto ite_c = hash_parent.begin(); ite_c != hash_parent.end(); ite_c++) {


// 		cout << "\nite_c->first->data=" << ite_c->first->data;
// 		cout << "\nite_c->second->data=" << ite_c->second->data;
// 		cout << "\nCAMINO=" << ite_c->first->data << "->";
// 		while (vertice_temp != grafo->vertexes.find(id)->second ) {
// 			cout << vertice_temp->data << "->";
// 			vertice_temp = hash_parent.find(vertice_temp )->second;
// 		}
// 		cout << vertice_temp->data << ";";
// 	}
// 	*/

// 	return resultado;
// }


# endif