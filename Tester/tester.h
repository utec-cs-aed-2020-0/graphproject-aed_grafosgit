#include <iostream>
#include <string>
#include "../Parser/parser.h"
#include "../Graph/DirectedGraph.h"
#include "../Graph/graph.h"
#include "../Graph/Algorithms/prim.h"
using namespace std;

class Tester{
    public:
        static void executeExamples(){
            cout << "this marks the start of our test \n";
            DirectedGraph<string, int>  testGraph;
            Prim_A<string, int> prim;
            cout << "1. Insertion was successfull: " << testGraph.insertVertex("A","A") << "\n";
            cout << "2. Insertion was successfull: " << testGraph.insertVertex("B","B") << "\n";
            cout << "3. Insertion was successfull: " << testGraph.insertVertex("C","C") << "\n";
            cout << "4. Insertion was successfull: " << testGraph.insertVertex("D","D") << "\n";
            cout << "5. Insertion was successfull: " << testGraph.insertVertex("E","E") << "\n";
            
            testGraph.createEdge("A", "B", 5);
            testGraph.createEdge("A", "E", 5);
            testGraph.createEdge("A", "D", 1);
            testGraph.createEdge("B", "C", 3);
            testGraph.createEdge("D", "B", 3);
            testGraph.createEdge("D", "C", 2);
            testGraph.createEdge("E", "3", 3);
            prim.prim(testGraph,"A");
            // testGraph.display_edges("0001");
            
        };
        static void executeParser(){
            cout << "Executing parser \n";
            Parser parser;
            parser.readJSON("airports.txt");
        };

        static double toRadians_d(const double degree){
            double one_deg = (M_PI) / 180;
            return one_deg * degree;
        }
        static double distance(double lat1, double lon1, double lat2, double lon2){
            lat1 = toRadians_d(lat1);
            lon1 = toRadians_d(lon1);
            lat2 = toRadians_d(lat2);
            lon2 = toRadians_d(lon2);
            double d_lon = lon2 - lon1;
            double d_lat  = lat2 - lat1;
            double ans = pow(sin(d_lat/2),2) + 
                         cos(lat1) * cos(lat2) * 
                         pow(sin(d_lon/2),2);
            ans = 2 * asin(sqrt(ans)); 
            ans = ans * 6371;
            return ans; 
        }
};
