//Hunter Jenkins
//BST
//my own work
#include "Bst.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() 
{
  Bst BST;
  ifstream thefile("text.in");
  //thefile.open("text.in");
  string temp;

  if(!thefile)
  {
    cout << "File not Found";
  }
  while(thefile >> temp)
  {
      BST.newInsert(temp);
  }
  thefile.close();

  BST.display();
  cout << endl << endl;
  BST.deleteNode("dog");
  cout << endl;
  BST.display();
  cout << endl << endl;;
  BST.search("yellow");
  return 0;
}
