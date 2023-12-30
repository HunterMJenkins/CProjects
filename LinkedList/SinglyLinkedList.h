#ifndef SinglyLinkedList_h
#define SinglyLinkedList_h
#include "iostream"
using namespace std;
//template <class t>

class SinglyLL
{
  public:

    struct Node
    {
    int data;
    struct Node* next;
    
    };
    struct Node* prev = NULL;
    struct Node* head = NULL;
    void front();
    void back();
    void insert( int val);
    void pop_front();
    void pop_back();
    bool empty();
    int size();
    void reverse();
    void merge(SinglyLL aList);
    void display();
};
#endif

