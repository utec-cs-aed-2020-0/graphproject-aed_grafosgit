#include <iostream>
#include "priorityqueue.h"
#include "../graph.h"
#include "prim.h"
using namespace std;

int main(){
    Vertex<string, int>* newVertex1 = new Vertex<string, int>();
    newVertex1->data = "A";
    Vertex<string, int>* newVertex2 = new Vertex<string, int>();
    newVertex2->data = "B";
    Vertex<string, int>* newVertex3 = new Vertex<string, int>();
    newVertex3->data = "C";
    Vertex<string, int>* newVertex4 = new Vertex<string, int>();
    newVertex4->data = "D";
    P_Queue<Vertex<string, int>*> queue;
    queue.Insert(newVertex4,4);
    queue.Insert(newVertex3,3);
    queue.Insert(newVertex2,2);
    queue.Insert(newVertex1,1);
    Vertex<string, int>* newVertex = queue.front();
    cout << newVertex->data;
    queue.pop_front();
    newVertex = queue.front();
    cout << newVertex->data;
    // P_Queue<int> queue2;
    // queue2.Insert(5,5);
    // queue2.Insert(4,4);
    // queue2.Insert(3,3);
    // queue2.Insert(2,2);
    // queue2.Insert(1,1);
    // queue2.Insert(6,6);
    // queue2.display();
    // queue2.pop_front();
    // queue2.pop_front();
    // queue2.pop_front();
    // queue2.pop_front();
    // queue2.pop_front();
    // queue2.pop_front();
    // queue2.pop_front();
    // cout << queue2.nodes << endl;
    // queue2.display();
    return 0;
}