#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>      // coordinates [Lon;Lat]
#include <math.h>
#include "json.hpp"
#include "../Graph/graph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"

using namespace std;
using json = nlohmann::json;

class Parser{   
    private:
        json j;
        ifstream infile;
        vector<double> coord;
    public:
        map<string, vector<double>> mp;
        map<string,string> ID_Name;
        list<string> check;
        vector<string> AirportIDs;
        vector<string> AirportNames;
        vector<vector<string>> Destinations;
        // getters
        json getJson(){return j;}
        // setters
        void SetJson(string filename){
            infile.open(filename);
            infile >> j;
        }
        int Airports(){ return AirportIDs.size();}
        int NumDests(){ return Destinations.size();}

        void readJSON(string filename){
            cout << "Parser for "+ filename + "\n";
            SetJson(filename);
            json temp;
            string id; 
            string name;
            string ltn;
            for(auto it = j.begin(); it != j.end(); it++){
                temp = *it;
                id = temp["Airport ID"];
                name = temp["Name"];
                AirportIDs.push_back(id);
                AirportNames.push_back(name);
                check.push_back(id);
                ID_Name.insert({id,name});
                Destinations.push_back(temp["destinations"]);
                ltn = temp["Longitude"];
                coord.push_back(stod(ltn));
                ltn = temp["Latitude"];
                coord.push_back(stod(ltn));
                mp.insert({temp["Airport ID"], coord});
                coord.clear();
            }
        }

        void DisplayMap(){
            for(auto it = mp.cbegin(); it != mp.cend(); ++it){
                vector<double> temp = it->second;
                cout << it->first << " " << "Lon: "<< temp[0] << " Lat: " << temp[1] << "\n";
            }
        }

        void DisplayID_Name(){
            for(auto it = ID_Name.cbegin(); it != ID_Name.cend(); ++it){
                cout << it->first << " "  << it->second<<"\n";
            }
        }

        void clear(){ // Clears parser saved atributes
            infile.close();
            AirportIDs.clear();
            Destinations.clear();
            coord.clear();
            mp.clear();
            ID_Name.clear();
            AirportNames.clear();
            j.clear();
        }
        
        void uGraphMake(Graph<string, double>* &tempGraph){ // Adds the parsed data into the specified undirected graph
            string dest_id;
            int insertions = 0;
            double weight = 0;
            double lat1,lon1,lat2,lon2 = 0;
            vector<double> coords;
            for(int i = 0; i < AirportIDs.size(); i++){
                if(!tempGraph->findById(AirportIDs[i])){
                    if(tempGraph->insertVertex(AirportIDs[i], AirportNames[i]))
                        insertions++;
                }
                // create vertex from destinations
                // cout << "destinos: \n";
                coords = mp[AirportIDs[i]];
                lon1 = coords[0];
                lat1 = coords[1];
                for(string dest: Destinations[i]){
                    // cout << dest << " " << parser.ID_Name[dest] << " ";
                    coords = mp[dest];
                    lon2 = coords[0];
                    lat2 = coords[1]; 
                    if(!tempGraph->findById(dest)){
                        if(contains(check,dest)){
                            if(tempGraph->insertVertex(dest, ID_Name[dest]))
                                insertions++;
                        }
                    }
                    if(AirportIDs[i] != dest){
                        if(contains(check,dest)){
                            if(!tempGraph->NodesConnected(AirportIDs[i],dest)){
                                weight = distance(lat1,lon1,lat2,lon2);
                                tempGraph->createEdge(AirportIDs[i],dest,weight);
                            }
                        }
                    }
                }
            }

            cout << "\nTotal size of Airports: " << AirportIDs.size() << endl;
            cout << "Total number of succesfull insertions: " << insertions << endl;
            if(insertions > AirportIDs.size())
                cout << "Some destinations lack An Airport or Name\n";
            tempGraph->display();

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
        bool contains(list<string> &listOfElements, const string &element){
            auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
            return it != listOfElements.end();
        }
        // void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
};

