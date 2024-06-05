/* ******************************************** 
 * TODO  Fill in header
 * ***************************************** */
 
#include "position.h"
#include <iostream>
using namespace std;

#define GRAVITY -9.8 // m/s^2


/* ******************************************** 
 * TODO  fill in class header
 * ***************************************** */
class Angle {

public:
   Angle() {}

private:
   double angle; // degrees
      
};


/* ******************************************** 
 * TODO  fill in class header
 * ***************************************** */
class Acceleration {

public:
   Acceleration() {}

private:
   double accel; // degrees
      
};


/* ******************************************** 
 * TODO  fill in class header
 * ***************************************** */
class Shell {

public:

private:
   Angle angle;
   Acceleration accel;
   Position pos;
};


/* ******************************************** 
 * TODO  main header
 * ***************************************** */
int main (int argc, char *argv[]) {
   cout << "pop" << endl;
   return 0;
}
