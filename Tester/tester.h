#include <iostream>
#include <string>
#include <vector>
#include "../Parser/parser.h"
#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/graph.h"
#include "../Graph/Algorithms/prim.h"
#include "../Graph/Algorithms/kruskal.h"
#include "../Graph/Algorithms/bfs.h"
#include "../Graph/Algorithms/dfs.h"
#include "../Graph/Algorithms/dijkstra.h"

using namespace std;

class Tester{
    public:
        static void executeExamples(){
            cout << "--------- this marks the start of our test ---------\n";
            
            cout << "###### EJEMPLO #1 DIRECTED GRAPH ######\n";
            // DirectedGraph<string, int>  testGraph1;
            Graph<string,int>* testGraph1 = new DirectedGraph<string,int>();
            cout << "1. Insertion was successfull: " << testGraph1->insertVertex("A","A") << "\n";
            cout << "2. Insertion was successfull: " << testGraph1->insertVertex("B","B") << "\n";
            cout << "3. Insertion was successfull: " << testGraph1->insertVertex("C","C") << "\n";
            cout << "4. Insertion was successfull: " << testGraph1->insertVertex("D","D") << "\n";
            cout << "5. Insertion was successfull: " << testGraph1->insertVertex("E","E") << "\n\n";
            
            testGraph1->createEdge("A", "B", 5);
            testGraph1->createEdge("A", "E", 5);
            testGraph1->createEdge("D", "A", 1);
            testGraph1->createEdge("B", "C", 3);
            testGraph1->createEdge("D", "B", 3);
            testGraph1->createEdge("D", "C", 2);
            testGraph1->createEdge("E", "D", 3);
            // Display the Graph
            testGraph1->display();
            // Properties:

            // testing operator()
            cout << "testing operator(A,B) " << "Weight should be 5: " << (*testGraph1)("A","B")<< endl; 

            cout << "Density of the graph: "<< testGraph1->density()<< endl; // density
            cout << "Is it dense ?(threshold = 0.5): ";
            if(testGraph1->isDense())
                cout << "true\n\n";
            else 
                cout<< "false\n\n"; 
            
            // conectivity
            cout << "Is graph connected?  " << testGraph1->isConnected();

            cout << "\n Is graph strongly connected ? ";
            if(testGraph1->isStronglyConnected())
                cout << "true\n\n";
            else 
                cout<< "false\n\n";

            Prim<string, int> prim(testGraph1,"A");
            cout << "Prim Algorithim from vertex A: ";
            prim.prim();
            cout << endl;
            
            Kruskal_A<string, int> krskal(testGraph1);
            cout << "Kruskal Algorithim ";
            krskal.Kruskal_();
            cout << endl << endl;

            cout << "BFS Algorithim \n";
            BFS<string, int> bfs(testGraph1,"A");
            Graph<string,int>* BFS_Result = bfs.apply();
            
            BFS_Result->display();
            
            cout << "DFS Algorithim \n";
            DFS<string, int> dfs(testGraph1,"A");
            Graph<string,int>* DFS_Result = dfs.apply();
            
            DFS_Result->display();


            //Graph that is strongly connected
            DirectedGraph<string, int>  testGraph12;
            cout << "1. Insertion was successfull: " << testGraph12.insertVertex("A","A") << "\n";
            cout << "2. Insertion was successfull: " << testGraph12.insertVertex("B","B") << "\n";
            cout << "3. Insertion was successfull: " << testGraph12.insertVertex("C","C") << "\n";
            cout << "4. Insertion was successfull: " << testGraph12.insertVertex("D","D") << "\n";
            cout << "5. Insertion was successfull: " << testGraph12.insertVertex("E","E") << "\n\n";
            
            testGraph12.createEdge("A", "C", 1);
            testGraph12.createEdge("C", "E", 2);
            testGraph12.createEdge("E", "B", 3);
            testGraph12.createEdge("B", "D", 4);
            testGraph12.createEdge("D", "A", 5);

            testGraph12.display();

            cout << "\n Is graph strongly connected ? ";
            if(testGraph12.isStronglyConnected())
                cout << "true\n\n";
            else 
                cout<< "false\n\n";

            // testGraph1.deleteEdge("D","A");
            cout << "---Deleting vertex A---\n\n";
            testGraph1->deleteVertex("A");
            testGraph1->display();

            // clear the graph;
            testGraph1->clear();
            testGraph1->display();  
            
            Graph<string,int>* testGraph3 = new UnDirectedGraph<string,int>();
            
            cout << "1. Insertion was successfull: " << testGraph3->insertVertex("A","A") << "\n";
            cout << "2. Insertion was successfull: " << testGraph3->insertVertex("B","B") << "\n";
            cout << "3. Insertion was successfull: " << testGraph3->insertVertex("C","C") << "\n";
            cout << "4. Insertion was successfull: " << testGraph3->insertVertex("D","D") << "\n";
            cout << "5. Insertion was successfull: " << testGraph3->insertVertex("E","E") << "\n";
            cout << "6. Insertion was successfull: " << testGraph3->insertVertex("F","F") << "\n";
            cout << "7. Insertion was successfull: " << testGraph3->insertVertex("G","G") << "\n";
            cout << "8. Insertion was successfull: " << testGraph3->insertVertex("H","H") << "\n";
            cout << "9. Insertion was successfull: " << testGraph3->insertVertex("I","I") << "\n\n";
            
            testGraph3->createEdge("A", "B", 2);
            testGraph3->createEdge("A", "G", 3);
            testGraph3->createEdge("A", "F", 7);
            testGraph3->createEdge("B", "C", 4);
            testGraph3->createEdge("C", "D", 1);
            testGraph3->createEdge("D", "H", 1);
            testGraph3->createEdge("D", "E", 1);
            testGraph3->createEdge("E", "I", 2);
            testGraph3->createEdge("I", "G", 1);
            testGraph3->createEdge("I", "F", 5);
            testGraph3->createEdge("I", "H", 4);
            testGraph3->createEdge("H", "C", 2);
            testGraph3->createEdge("F", "E", 6);
            testGraph3->createEdge("G", "B", 1);
            testGraph3->createEdge("G", "H", 1);    

            testGraph3->display();

            // Properties:
            cout << "Density of the graph: "<< testGraph3->density()<< endl; // density
            cout << "Is it dense ?(threshold = 0.5): ";
            
            if(testGraph3->isDense())
                cout << "true\n\n";
            else 
                cout<< "false\n\n"; 

            // connectivity
            
            if(testGraph3->isConnected())
                cout << "true\n\n";
            else   
                cout << "false\n\n";

            cout << "Prim Algorithim from vertex A: ";
            Prim<string, int> prim_u(testGraph3,"A");
            prim_u.prim();

            Kruskal_A<string, int> krskal_u(testGraph3);
            cout << "Kruskal Algorithim ";
            krskal_u.Kruskal_();
            cout << endl << endl;

            cout << "BFS Algorithim \n";
            BFS<string, int> bfs_u(testGraph3,"A");
            Graph<string,int>* BFS_Result_u = bfs_u.apply();
            
            BFS_Result_u->display();
            
            cout << "DFS Algorithim \n";
            DFS<string, int> dfs_u(testGraph3,"A");
            Graph<string,int>* DFS_Result_u = dfs_u.apply();
            
            DFS_Result_u->display();


            cout << "---Deleting vertex A---\n\n";
            testGraph3->deleteVertex("A");
            testGraph3->display();

            cout << "clearing graph\n";
            testGraph3->clear();
            testGraph3->display();

        };


        static void executeParser(){
            cout << "\n----- Executing parser -----\n";
            Parser parser;
            cout << "Aeropuertos en Perú \n";
            parser.readJSON("pe.txt");

            Graph<string,double>* N_Airports = new UnDirectedGraph<string,double>();
            parser.uGraphMake(N_Airports);
            parser.clear();

            parser.readJSON("airports.txt");
            Graph<string,double>* I_Airports = new UnDirectedGraph<string,double>();
            parser.uGraphMake(I_Airports);
        }
};
