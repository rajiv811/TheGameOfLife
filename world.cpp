//Rajiv Singireddy
//world.cpp

//Purpose: The purpose of the world.cpp file is to create the contents of
//all the functions that are created in the header file, while also initializing
//the private variables. It will also create the functions that will make the
//game run in the p2 file.

//Input: The user will be inputing the number of generations and the
//their own file, but other than that, there will be no other inputs.

//Processing: In p2, the processing will go as such: First, the object will
//be created, and by doing so, numRows and numCols will be set to 0 and
//the board 2D array will be set to nullptr. After that, the function will
//load the loadDefault function which will load the default "random.w" file.
//Then a screen appear asking the user to either upload a different file or
//input a number to go by generations. If they upload a new file, then the
//load function will be called and it will return a bool value to check if
//the file opens correctly or not, while also creating the 2D array for the
//file. Finally, animate will be called once the number of generations is entered
//which will call upon display, nextGeneration, sleepSeconds and clearConsole
//which will all contribute to the animation of the Game of Life.

//Output: This code outputs the display of the file while also showing the
//progression of each generation of the game of life. When the game is run,
//every function will be called in order to make the transition from frame
//to frame look smooth and nice.


//Example:
/*
****DEFAULT WORLD****

***

*

**              **

*  *             ** **

**                  **** **

*    * ** **

**       *   *   *    *

* *       *    ** *   *

*       *  *   *  **

*     ** **





**    ***         **

**    * *        ** **    *

***     *  **      * *

**  **     ** *

*      *

* * **

Available commands:
Next generation(s):       n #
Save world:               s filename
Load world:               l filename
Enter world:              e
Quit:                     q
n 2
Generation 0

***

*

**              **

*  *             ** **

**                  **** **

*    * ** **

**       *   *   *    *

* *       *    ** *   *

*       *  *   *  **

*     ** **
**    ***         **

**    * *        ** **    *

***     *  **      * *

**  **     ** *

*      *

* * **


Generation 1

*
**
*  *
**              *
*  *            ***  ****
**             *** *** * ***
**
**       **   *    * *
* *      **   * * *   *
*         *    **  *
** **

*
***   ***         ***
* **   *   *      *   *      *
**      ***     *     *   ** *
*      ** ***     ** *
**  * ** *
* *


Generation 2
**
***
*
**             ** *   **
*  *            *  ***  *   *
**            *  ***     * *
*  *  **     *
**       **    *  ** *
* *      * *    * ****
*        *    **   * *
*****

*    ***          *
* *   * *         ***
*      *   *      *****     **
***     * *     * *   *   *  *
***     ** *  *  *    *
*  ** *** *
* * *


Available commands:
Next generation(s):       n #
Save world:               s filename
Load world:               l filename
Enter world:              e
Quit:                     q
q


*/
//include statements
#include "world.h"
#include <iostream>
#include <thread>
#include <string>
#include <fstream>

//function that separates each generation by some milliseconds
void sleepSeconds(int n)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(n));
}

//function that clears the console so program looks nice
void clearConsole()
{
  std::cout << "\x1B[2J\x1B[H";
}

//Default constructor
World::World()
{
  board = nullptr;
  numRows = 0;
  numCols = 0;
}

//deconstructor
World:: ~World()
{
  for(int row = 0; row < numRows; row++){
    delete[] board[row];
  }
  delete[] board;
}

//display function that shows the board
void World::display()
{
  for(int r = 0; r < numRows; r++){
    for(int c = 0; c < numCols; c++){
      cout << board[r][c];
    }
    cout<<endl;
  }
}

//function that goes to the next generation until done
void World::nextGeneration()
{
  char **NewBoard = new char*[numRows];
  for(int i = 0; i < numRows; ++i) {
    NewBoard[i] = new char[numCols];
  }
  
  for (int r=0; r< numRows; r++){
    for (int c=0; c< numCols; c++){
      int x = findNeighbor(r,c);

      //previous code that didn't work
      /*int count = 0;
          if (c > 0 && r > 0 && board[r-1][c-1]==LIFE){
              count++;
          }
          if (r > 0 && board[r-1][c]==LIFE){
             count++;
          }
          if ((c < numCols-1) && r > 0 && board[r-1][c+1]==LIFE){
              count++;
          }
          if (c > 0 && board[r][c-1]==LIFE){
              count++;
          }
          if ((c < numCols-1) && board[r][c+1]==LIFE){
              count++;
          }
          if ((r < numRows-1) && c > 0 && board[r+1][c-1]==LIFE){
              count++;
          }
          if ((r < numRows-1) && (c < numCols-1) && board[r+1][c+1]==LIFE){
              count++;
          }
  */
          NewBoard[r][c] = DEATH;
          if (board[r][c] == LIFE && x < 2){
            NewBoard[r][c]=DEATH;
          }
          else if (board[r][c]==LIFE && (x==2 || x==3)) {
            NewBoard[r][c]=LIFE;
          }
          else if (board[r][c]==LIFE && x>3 ) {
            NewBoard[r][c]=DEATH;
          }
          else if (board[r][c]==DEATH && x==3) {
            NewBoard[r][c]=LIFE;
          }
      }
  }
  board = NewBoard;
}
//function that displays the generations
void World::animate(int numGenerations)
{
  for(int i = 0; i <= numGenerations; i++){
    cout << "Generation " << i << endl;
    display();
    nextGeneration();
    clearConsole();
    sleepSeconds(DELAY);
  }
}

//loads the default file and finds the rows and cols, while allocating that to a 2D array
void World::loadDefault()
{
  const int MAX_ROWS = 40;
  const int MAX_COLS = 100;
  ifstream worldFile;
  worldFile.open("/home/fac/lundeenk/submit/18wq1430/files/random.w");
  numRows = numCols = 0;
  string line;
  while (numRows < MAX_ROWS && getline(worldFile, line)) {
    numRows++;
    int length = static_cast<int>(line.length());
    if (length > numCols) {
      if (length > MAX_COLS)
        numCols = MAX_COLS;
      else
        numCols = length;
    }
  }
  worldFile.close();
  worldFile.open("/home/fac/lundeenk/submit/18wq1430/files/random.w");
  board = new char*[numRows];
  for (int row = 0; row < numRows; row++){
    board[row] = new char[numCols];
  }
  for (int r = 0; r < numRows; r++){
    for (int c = 0; c < numCols; c++){
      worldFile.get(board[r][c]);
    }
  }
  display();
  worldFile.close();
}
//loads the user file and finds the rows and cols, while allocating that to a 2D array
bool World::load(string filename)
{
  ifstream worldFile2;
  worldFile2.open(filename);
  if(worldFile2.fail()){
    return false;
  }
  const int MAX_ROWS2 = 40;
  const int MAX_COLS2 = 100;
  numRows = numCols = 0;
  string line;
  while (numRows < MAX_ROWS2 && getline(worldFile2, line)) {
    numRows++;
    int length = static_cast<int>(line.length());
    if (length > numCols) {
      if (length > MAX_COLS2){
        numCols = MAX_COLS2;
      }
      else{
        numCols = length;
      }
    }
  }
  worldFile2.close();
  worldFile2.open(filename);
  board = new char*[numRows];
  for (int row = 0; row < numRows; row++){
    board[row] = new char[numCols];
  }
  for (int r = 0; r < numRows; r++){
    for (int c = 0; c < numCols; c++){
      worldFile2.get(board[r][c]);
    }
  }
  worldFile2.close();
  return true;
}

//function that finds the neighbor of each cell
int World::findNeighbor(int rows, int cols)
{
  int numOfneighbors = 8;
  if ((rows - 1) >= 0){
      if (board[rows-1][cols] == DEATH){
        numOfneighbors--;
      }
    }
    else{
      numOfneighbors--;
    }
    if ((rows - 1) >= 0 && (cols - 1) >= 0){
      if (board[rows-1][cols-1] == DEATH){
        numOfneighbors--;
      }
    }
    else{
      numOfneighbors--;
    }

    if ((rows - 1) >= 0 && (cols + 1) < numCols){
      if (board[rows-1][cols+1] == DEATH){
        numOfneighbors--;
      }
    }

    else{
      numOfneighbors--;
    }

    if ((cols - 1) >= 0){
      if (board[rows][cols-1] == DEATH){
        numOfneighbors--;
      }
    }

    else{
      numOfneighbors--;
    }

    if ((cols + 1) < numCols){
      if (board[rows][cols+1] == DEATH){
        numOfneighbors--;
      }
    }

    else {
      numOfneighbors--;
    }

    if ((rows + 1) < numRows){
      if (board[rows+1][cols] == DEATH){
        numOfneighbors--;
      }
    }     

    else{
      numOfneighbors--;
    }

    if ((rows + 1) < numRows && (cols - 1) >= 0){
      if (board[rows+1][cols-1] == DEATH){
        numOfneighbors--;
      }
    }

    else{
      numOfneighbors--;
    }

    if ((rows + 1) < numRows && (cols + 1) < numCols){
      if (board[rows+1][cols+1] == DEATH){
        numOfneighbors--;
      }
    }

    else{
      numOfneighbors--;
    }
    return numOfneighbors;
}
//proffessor said we don't need to use
//all of the big four, but he wanted us
//to write them (not implement them)
World:: World(const char *str)
{

}
