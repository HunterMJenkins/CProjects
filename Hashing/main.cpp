#include <iostream>
#include <string>
#include <fstream>
//This is all my own work
//Hunter Jenkins
//hahsing table
using namespace std;

void insert(string input);
void display();
bool find(string key);
struct node
{
  string data;
  node* next = NULL;
};

struct node* bucketArray[27];

int main()
{
  ifstream thefile("text.txt");
  string temp;
  if(!thefile)
  {
    cout << "File not Found";
  }
  while(thefile >> temp)
  {
      insert(temp);
  }
  thefile.close();
  display();
  cout << "find" << find("it");
  
}
void insert(string input)
{
  node* temp = new node;
  temp->data=input;
  int value = 0;
  for(int i = 0; i < input.length(); i++)
    {
      //cout << value << " ";
      value = value + int(input[i]);
    }
  int hashNumber = value % 27;
  //cout << hashNumber << " ";
  temp->next = bucketArray[hashNumber];
  bucketArray[hashNumber] = temp;
}
void display()
{
  struct node* temp;
  for(int i = 0; i < 27; i++)
    {
      temp = bucketArray[i];
      while(temp != NULL)
        {
          cout << temp->data << " ";
          temp = temp->next;
        }
    }
}
bool find(string key)
{
  struct node* temp;
  int value = 0;
  for(int i = 0; i < key.length(); i++)
    {
      //cout << value << " ";
      value = value + int(key[i]);
    }
  int hashNum = value % 27;
  if(bucketArray[hashNum] == NULL){return false;}
  if(key == bucketArray[hashNum]->data){return true;}
  temp = bucketArray[hashNum];
    while(temp != NULL)
    {
      if(key == temp->data)
      {
        return true;
      }
      temp = temp->next;
    }
  return false;
    
}