//Rajiv Singireddy
//p2.cpp
//Game of Life

#include <iostream>
#include <fstream>
#include "world.h"
using namespace std;
int main()
{
  World world; //creates instance of class
  cout << "****DEFAULT WORLD****" << endl;
  world.loadDefault(); //loads the default world
  bool val = true;
  while(val == true){
    string file;
    cout << "Available commands: " << endl;
    cout << "Next generation(s):       n #" << endl;
    cout << "Save world:               s filename" << endl; //Extra credit, didn't do this part
    cout << "Load world:               l filename" << endl; //Extra credit, didn't do this part
    cout << "Enter world:              e" << endl;
    cout << "Quit:                     q" << endl;
    int num;
    string answer;
    cin >> answer;
    if(answer == "n"){
      cin >> num;
      world.animate(num); //animates the world based on number of gens
    }
    if(answer == "q"){
      return 0;
    }
    else if(answer == "l") {
      string filename;
      cin >> filename;
      if(world.load(filename) == false){ //checks if file loads correctly
        cout << "Did not load. ERROR." << endl;
        return 0;
      }
      else if(world.load(filename)) { //if it does, then it will print out the gens
        int num2;
        cout << "Enter a number for generations:" << endl;
        cin >> num2;
        world.animate(num2);
      }
    }
  }
}
