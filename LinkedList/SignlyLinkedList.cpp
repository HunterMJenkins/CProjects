				#include <iostream>
#include "SinglyLinkedList.h"

void SinglyLL::front()
{
  if(head == NULL)
  {
    cout << "head is NULL" << endl;
  }
  else{
    cout << "First Node is " << head->data << endl;
  }
}
void SinglyLL::back()
{
  struct Node* temp;
  struct Node* prev;
  temp = head;
  while(temp != NULL)
    {
      prev = temp;
      temp = temp->next;
    }
  cout << "The last Node is " << prev->data << endl;
  
}
void SinglyLL::insert( int val)
{
    Node* theNode = new Node;
    struct Node* temp;
    theNode->data=val;
    theNode->next=NULL;
      if(head ==NULL  || head->data >= theNode->data)
      {
        head=theNode;
        prev=theNode;
        temp=NULL;
      }
      else
      {	
        temp = head;
        while (temp->next != NULL && temp->next->data < theNode->data) 
        {
            temp = temp->next;
        }
        theNode->next = temp->next;
        temp->next = theNode;
      }
}
void SinglyLL::pop_front()
{
    struct Node *temp;
    temp=head;
    head=head->next;
    delete temp;
}
void SinglyLL::pop_back()
{
     struct Node* temp;
      struct Node* prev;
      prev = temp->next;
      temp = head;
      while(temp->next->next != NULL)
        {
        temp = temp->next;
        }
      temp->next = NULL;
}
bool SinglyLL::empty()
{
  if(head == NULL)
  {
    return false;
  }
  return true;
}
int SinglyLL::size()
{
    struct Node* temp;    
    temp = head;
    int size = 0;
    while (temp != NULL) 
    {   
      ++size;
      temp = temp -> next;
    }
    return size;
}
void SinglyLL::reverse()
{
  Node* temp = head;
  struct Node* prev; //'' = NULL;
  struct Node* next; // = NULL
  while(temp != NULL)
    {
    
      next = temp->next; //store value
      temp->next = prev; //reverse node
      prev = temp;
      temp = next;
    }
  head = prev;

}
void SinglyLL::merge(SinglyLL list)
{
  
    struct Node* temp;
    temp = list.head;

    while(temp != NULL)
      {
        int val = temp->data;
        insert(val);
        temp = temp->next;
      }


  
}
void SinglyLL::display() 
{              
   struct Node* temp;    
   temp = head;              
   while (temp != NULL) 
   {   
      cout <<  temp-> data  <<" ";     
      temp = temp -> next;
    }
  cout << endl;
  }