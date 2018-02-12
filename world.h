//Rajiv Singireddy
//world.h
//Purpose: The purpose of this header file is to create the private variables
//and private functions, as well as the public functions, so that they can
//be implemented in the p2 file. The contents will be created in the world.cpp
//file.
#include <iostream>
#ifndef WORLD_H
#define WORLD_H
using namespace std;
class World
{
 private:
  int numGenerations;
  static const int DELAY = 500;
  static const char DEATH = ' ';
  static const char LIFE = '*';

  char **board;
  char **NewBoard;
  int numRows, numCols;
  void display();
  //pre: none
  //post: displays the board of the file
  void nextGeneration();
  //pre: none
  //post: goes to the next generation
 public:
  World(); //default constructor
  //pre: none
  //post:sets numRows and numCol to 0, and also sets board to nullptr
  void animate(int numGenerations);
  //pre: int numGenerations gotten from the user input
  //post: Animates the board so that it shows each generation
  void loadDefault();
  //pre: none
  //post: Loads the default file and get the size of the rows and columns,
  //while also loading the file into the areas on the 2D board
  bool load(string);
  //pre: takes in a string which is the file the user inputs
  //post: Loads the input file and get the size of the rows and columns,
  //while also loading the file into the areas on the 2D board  
  int findNeighbor(int, int);
  World(const char *str); //copy constructor
  World& operator = (const World &t); //assignment operator 
  ~World(); //destructor
  //pre: none
  //post: deconstructor
};
#endif
