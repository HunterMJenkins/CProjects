//Source for MazeSolver

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "myStack.h"
//#include "MyQ.h"
#include "MazeCell.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DONE 4
#define SUCCESS 10
#define FAILURE 20

//method headers*******************************************************

//depthFirst header
void depthFirst(MazeCell start, MazeCell end);

//global variables*****************************************************

//# rows and cols in the maze
int rows, cols;
//pointer to the grid (2-d array of ints)
int** grid;
//pointer to the maze cells (2-d array of MazeCell objects)
MazeCell** cells;

int main() {
	
	//create the Maze from the file
	ifstream fin("maze.in");	
	if(!fin){
		cout << "File not found\n";
		exit(2);
	}

	//read in the rows and cols
	fin >> rows >> cols;

	//create the maze rows
	grid = new int* [rows];
	
	//add each column
	for (int i = 0; i < rows; i++)
		grid[i] = new int[cols];

	//read in the data from the file to populate
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fin >> grid[i][j];
		}
	}

	//look at it 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 3)
				cout << "S" << " ";
			else if (grid[i][j] == 4)
				cout << "E" << " ";
			else
				cout << grid[i][j] << " ";
		}
		cout << endl;
	}

	//make a 2-d array of cells
	cells = new MazeCell * [rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new MazeCell[cols];
	}

	//all MazeCell in the cells grid has a default init
	//only update those cells that are not walls

	MazeCell start, end;
	
	//iterate over the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] != 0) {
				cells[i][j].setCoordinates(i, j);
				//look for the start and end cells
				if (grid[i][j] == 3)
					start = cells[i][j];
				if (grid[i][j] == 4) 
					end = cells[i][j];
				
			}

		}
	}
	
	//testing
	cout <<"start: "<< start << " end: " << end << endl;
	
	//solve it!
	depthFirst(start, end);


	return 0;
}


//this function should find a path through the maze
//if found, output the path from start to end
//if not path exists, output a message stating so

void depthFirst(MazeCell start, MazeCell end)
{	
  //set the rows and cols to gind the starting postion 
	int row = start.getRow();
  int col = start.getCol();
  //sets the end so we know where we need to end
  int rowEnd = end.getRow();
  int colEnd = end.getCol();
  //initalize stack and pushes data onto the stack
  MyStack<MazeCell> myStack;
  myStack.push(cells[row][col]);
  //start with master while loop this keeps our parameters in
  //bounds and checking if the
  //go right first
      //right down left up
      //unvistied, in bounds
      //NEEDED TO DO COL+1 < 6
      //RAHTER THAN USING CELLS[COL+1].getCol() > 6 fior the program to run
      //ALSO I needed to have the inbounds as the first thing checked in the if statements 
      //without this I was running into many errors when retracking
  while(cells[row][col] != cells[rowEnd][colEnd])
   {
     
       //going left
      if(col-1 > -1 && cells[row][col-1].unVisited() &&  cells[row][col-1].getRow() != -1)
      {
        cells[row][col].visit(); //mark cell as visited
        myStack.push(cells[row][col]); //push to stack
        cout << myStack.top() << endl; //print
        col--; //decrement
      }
        //go down
      else if( row+1 < 4 && cells[row+1][col].unVisited() && cells[row+1][col].getCol() != -1  )
      {
        cells[row][col].visit();
        myStack.push(cells[row][col]);
        cout << myStack.top() << endl;
        row++;
      }
        //going right
      else if(col+1 < 6 && cells[row][col+1].unVisited() &&  cells[row][col+1].getRow() != -1)
        { 
        cells[row][col].visit();
        myStack.push(cells[row][col]);
        cout << myStack.top() << endl;
        col++;
      }
        //up
       else if(row-1 > -1 && cells[row-1][col].unVisited() && cells[row-1][col].getCol() != -1)
     {
        cells[row][col].visit();     
        myStack.push(cells[row][col]);
        cout << myStack.top() << endl;     
        row--;
      }
        //i tired if statements at first but ran into errors so switch to else if
      else
      {
        //set the cells to the top of the stack, then pop the stack
        //i set col and row too because thats why I use in my code to increment
        cells[row][col] = myStack.top();
        col = cells[row][col].getCol();
        row = cells[row][col].getRow();
        myStack.pop();
      }
     
    }
  
}

