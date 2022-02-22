#ifndef DSARRAY_H
#define DSARRAY_H

#include <map>
template <typename T>
class DisjoinSetArray {
    private:
        vector<vector<T>> vec;
        int *rank, *parent;
        int n = 0;
        int elements  = 0;
        int capacity = 0;
        int size = 0;
    public:
        map<int, T> mp;
        DisjoinSetArray(int capacity_){
            capacity = capacity_;
            rank = new int[capacity_];
            parent = new int[capacity_];
        }
        DisjoinSetArray(vector<T> vec_){
            SetsFromVec(vec_);
        }
        void Insert(T data){
            elements++;
            if(elements > capacity){
                resize_p();
                resize_r();
            }
            mp.insert({elements-1,data});
            parent[elements-1] = elements-1;
            n++;
        }
        void resize_p(){
            size_t newSize = capacity * 2;
            int* newArr = new int[newSize];
            memcpy( newArr, parent, capacity * sizeof(T) );
            size = newSize;
            delete [] parent;
            parent = newArr;
        }
        void resize_r(){
            size_t newSize = capacity * 2;
            int* newArr = new int[newSize];
            memcpy( newArr, rank, capacity * sizeof(T) );
            size = newSize;
            delete [] rank;
            rank = newArr;
        }
        void SetsFromVec(vector<T> vec_){
            n = vec_.size();
            rank = new T[n];
            parent = new T[n];
            for(int i = 0; i < n;i++){
                mp.insert({i,vec_[i]});
                parent[i] = i;
            }  
            elements = n;
        }
        // ~DisjoinSetArray();

        void MakeSet(int x){
            for(int i = 0; i < x; i++){
                parent[i] = i;
            }
        }

        int Find(int x){
            if(parent[x] != x){
                parent[x] = Find(parent[x]);
            }
            return parent[x];
        }
        bool FindElement(T data){
            if(GetIndexfromMap(data) == -1)
                return false;
            else
                return true;
        }

        int FindPathCompression(int x){
            return 0;
        }
        void UnionD(T x_, T y_){
            int x = GetIndexfromMap(x_);
            int y = GetIndexfromMap(y_);
            if( x == -1 || y == -1){
                throw("Items not found");
                return;
            }
            Union(x,y);
        } 
        void Union(int x, int y){
            n -= 1; 
            int x_set = Find(x);
            int y_set = Find(y);
            if(x_set == y_set)
                return;
            if(rank[x_set] < rank[y_set]){
                parent[x_set] = y_set;
            }
            else if(rank[x_set] > rank[y_set])
                parent[y_set] = x_set;
            else{
                parent[y_set] = x_set;
                rank[x_set] = rank[x_set] + 1; 
            }
        }
        bool isConnected(int x, int y){
            bool result = false;
            if(Find(x) == Find(y))
                result = true;
            return result;
        }
        
        int Size_(int x){
            vector<T> result = getElementsSet(x);
            return result.size();
        }
        vector<T> getElementsSet(int x){
            vector<T> result;
            for(int i = 0; i < elements; i++){
                if(isConnected(x,i) == true)
                    result.push_back(GetfromMap(i));
            }
            return result;
        }

        void display(){
            for(int i = 0; i < vec.size(); i++){
                for(int j = 0; j < vec[i].size(); j++){
                    cout << vec[i][j] << " ";
                }
                cout << endl;
            }
        }
        void displayMP(){
            for(auto it = mp.cbegin(); it != mp.cend(); ++it){
                cout << it->first << " " << it->second << "\n";
            }
        }
        T GetfromMap(int x){
            T a;
            for(auto it = mp.cbegin(); it != mp.cend(); ++it){
                if(it->first == x){
                    a = it->second; // element in the first vector
                    break;
                }
            }
            return a;
        }
        int GetIndexfromMap(T data){
            int index = -1;
            bool notfound = true;
            for(auto it = mp.cbegin(); it != mp.cend(); ++it){
                if(it->second == data){
                    index = it->first;
                    notfound = false;
                    break;
                }
            }
            if(notfound)
                return -1;
            else
                return index;
        }
};


#endif