#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include <exception>
using namespace std;

template<typename T>
struct Node {
    T data = 0;
    int priority = 0;
    Node<T>* next = NULL;
    Node<T>* prev = NULL;
};


template<typename T>
class P_Queue{
    private: 
        Node<T>* head;
        Node<T>* tail;
    public: 
        int nodes = 0;
        P_Queue(){
            Node<T>* first = new Node<T>();
            first->next = NULL;
            first->prev = NULL;
            head = first;
        }
        
        void Insert(T data, int priority){
            Node<T>* newNode = new Node<T>();
            Node<T>* current = head;
            Node<T>* last = head;
            newNode->data = data;
            newNode->priority = priority;
            newNode->next = NULL;
            newNode->prev = NULL;
            if(head->next == NULL){
                head->next = newNode;
                newNode->prev = head;
                nodes++;
                return;
            }
            while(current != NULL){
                if(current->priority >= priority){
                    current->prev->next = newNode;
                    newNode->prev = current->prev;
                    newNode->next = current;
                    current->prev = newNode;
                    nodes++;
                    return;
                }
                if(current->priority < priority){
                    if(last->next == NULL){
                        newNode->prev = current;
                        current->next = newNode;
                        nodes++;
                    }
                }
                last = last->next;
                current = current->next;
            }
            
        }
        T front(){
            return head->next->data;            
        }
        
        void pop_front(){
            if(nodes == 0){
                cout << "\nempty\n";
                return;
            }
            else if(nodes == 1){
                head->next = NULL;
                nodes--;
                return;
            }
            else{
                Node<T>* current = head->next;
                head->next = current->next;
                current->next->prev = head;
                delete(current);
                nodes--;
            }
        }

        bool IsEmpty(){
            if(nodes == 0)
                return true;
            else    
                return false;
        }

        void display(){
            if(nodes == 0 ){
                cout << "\n--empty--\n";
                return;
            }
            Node<T>* temp = head->next;
            while(temp != NULL){
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << "\n";
        }
};

#endif