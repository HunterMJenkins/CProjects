#include <iostream>
#include <string>

using namespace std; 

void display(int arr[15][15]);
void getN(int vertex , int arr[15][15]);
int getDistance(int start , int finish, int arr[15][15]);

int main() 
{
int arr[15][15];

  for(int i = 0; i < 15; i++)
    {
      for(int j = 0; j < 15; j++)
        {
          arr[i][j] = 0;
        }
    }
  arr[0][1] = 14;
  arr[0][11] = 14;
  arr[0][12] = 9;
  
  arr[1][0] = 14;
  arr[1][11] = 9;
  arr[1][2] = 9;
  arr[1][10] = 17;
  
  arr[2][1] = 9;
  arr[2][10] = 13;
  arr[2][9] = 20;
  arr[2][3] = 5;
  
  arr[3][2] = 5;
  arr[3][9] = 19;
  arr[3][4] = 17;

  arr[4][3] = 17;
  arr[4][9] = 4;
  arr[4][5] = 16;

  arr[5][4] = 16;
  arr[5][9] = 12;
  arr[5][6] = 8;
  arr[5][7] = 9;

  arr[6][5] = 8;
  arr[6][7] = 6;

  arr[7][6] = 6;
  arr[7][5] = 9;
  arr[7][9] = 12;
  arr[7][8] = 7;
  arr[7][14] = 10;
  arr[7][13] = 23;

  arr[8][7] = 7;
  arr[8][9] = 13;
  arr[8][10] = 5;
  arr[8][14] = 6;

  arr[9][2] = 20;
  arr[9][3] = 19;
  arr[9][4] = 4;
  arr[9][5] = 12;
  arr[9][7] = 12;
  arr[9][8] = 13;
  arr[9][10] = 7;

  arr[10][1] = 17;
  arr[10][2] = 13;
  arr[10][9] = 7;
  arr[10][8] = 5;
  arr[10][14] = 8;
  arr[10][11] = 18;

  arr[11][0] = 14;
  arr[11][1] = 9;
  arr[11][10] = 10;
  arr[11][14] = 9;
  arr[11][12] = 15;

  arr[12][0] = 9;
  arr[12][11] = 15;
  arr[12][14] = 15;
  arr[12][13] = 11;

  arr[13][12] = 11;
  arr[13][14] = 18;
  arr[13][7] = 23;

  arr[14][13] = 18;
  arr[14][12] = 15;
  arr[14][11] = 9;
  arr[14][10] = 8;
  arr[14][8] = 6;
  arr[14][7] = 10;

  display(arr);
  getN(2, arr);
  cout << endl << "Distance: " << getDistance(11,13, arr);
  
}
void display(int arr[15][15])
{
  for(int i = 0; i < 15; i++)
    {
      for(int j = 0; j < 15; j++)
        {
          cout << arr[i][j] << "\t";
        }
      cout << endl;
    }
}
void getN(int vertex, int arr[15][15])
{
  int neigh = 0; 
  cout << " Neighbors : ";
  for(int i = 0; i < 15; i++)
    {
      if(arr[vertex][i] != 0)
      {
        cout << i << " ";
        neigh++;
      }
    }
  cout << endl << "# of neighbors : " << neigh;
}
int getDistance(int start , int finish, int arr[15][15])
{
  int n = finish;
  int end = finish;
  
  int shortIndex;
  int total = 0;
  while(arr[start][finish] == 0)
    {
      int shortest = 9999;
      for(int i = 0; i < 15; i++)
        {
          if(arr[start][i] < shortest && arr[start][i] != 0)
          {
            shortest = arr[start][i];
          }
        }
      for(int i = 0; i < 15; i++)
      {
        if(arr[start][i] ==  shortest)
        {
          shortIndex = i;
        }
        if(arr[start][i] > 0 && i == end)
          {
              cout << "yo";
              total += arr[start][shortIndex];
              return total;
          }
      }
      total += arr[start][shortIndex];
      arr[start][shortIndex] = 0;
      start = shortIndex;
    }
  if(arr[start][finish] > 0)
  {
    total += arr[start][finish];
    return total;
  }
  return total;
      
}
