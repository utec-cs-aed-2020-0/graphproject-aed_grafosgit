#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>      // coordinates [Lon;Lat]
#include <math.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Parser{   
    private:
        json j;
        ifstream infile;
        map<string, vector<string>> mp;
        vector<string> coord;
    public:
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
            for(auto it = j.begin(); it != j.end(); it++){
                json temp = *it;
                AirportIDs.push_back(temp["Airport ID"]);
                AirportNames.push_back(temp["Name"]);
                Destinations.push_back(temp["destinations"]);
                coord.push_back(temp["Longitude"]);
                coord.push_back(temp["Latitude"]);
                mp.insert({temp["Airport ID"], coord});
                coord.clear();
            }
        }

        void DisplayMap(){
            for(auto it = mp.cbegin(); it != mp.cend(); ++it){
                vector<string> temp = it->second;
                cout << it->first << " " << "Lon: "<< temp[0] << " Lat: " << temp[1] << "\n";
            }
        }

        void clear(){ // Clears parser saved atributes
            AirportIDs.clear();
            Destinations.clear();
            coord.clear();
            mp.clear();
        }
        double toRadians_d(const double degree){
            double one_deg = (M_PI) / 180;
            return one_deg * degree;
        }
        double distance(double lat1, double lon1, double lat2, double lon2){
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
        // void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

        // void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
};

