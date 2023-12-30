#ifndef Bst_h
#define Bst_h
#include <iostream>
#include <string>
using namespace std;

struct node
{
    string data;
    struct node* left;
    struct node* right; 
};

struct node* head;

class Bst
{
public:

void newInsert(string input)
{
  head = insert(head , input);
}
node* insert(struct node* node , string data)
{
  if(node == NULL)
  {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
      return node;
  }
    if(data < node->data)
    {
      node->left = insert(node->left,data);
    }
    else if(data > node->data)
    {
      node->right = insert(node->right , data);
    }
    return node;
}
void display()
{
  actualDisplay(head);
}
void actualDisplay(node* node)
{
  if(node != NULL)
  {
     //LPR
    actualDisplay(node->left); //left
    cout << node->data << " ";
    actualDisplay(node->right);
    return;
  }
}
void search(string find)
  {
    head = actualSearch(head , find);
    if(head == NULL)
      {
        cout << find << " was not found" << endl;
      }
    else
      {
        cout << find << " was found" << endl;
      }
  }
node* actualSearch(node* node , string find)
{
  if(node == NULL || node->data == find)
  {
      return node;
  }
  if(find < node->data)
    {
       return actualSearch(node->left,find);
    }
  else
  {
    return actualSearch(node->right,find);
  }
}
void deleteNode(string del)
{
      head = actualDelete(head , del);
  }
node* actualDelete(node* node, string del)
  {
    if(node == NULL){return node;}
    if(del < node->data)
    {
      node->left = actualDelete(node->left , del);
    }
    else if(del > node->data)
    {
      node->right = actualDelete(node->right , del);
    }
    else
    {
      if(node->left == NULL)
      {
        struct node* temp = node->right;
        delete(node);
        return temp;
      }
      else if(node->right == NULL)
      {
        struct node* temp = node->left;
        delete(node);
        return temp;
      }
      struct node* temp = minVal(node-> right);
      node-> data = temp->data;
      node-> right = actualDelete(node->right, del);
    }
    return node;
  }
node* minVal(struct node* node)
  {
    struct node* findmin = node;
    while(findmin && findmin->left != NULL)
      {
        findmin = findmin->left;
      }
    return findmin;
  }

};
#endif