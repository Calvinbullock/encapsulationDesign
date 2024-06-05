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
class Angle
{

public:
   Angle()
   {
   }

private:
   double angle; // degrees
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Acceleration
{

public:
   Acceleration(double angle, double vel)
   {
      ddx = sin(angle) * vel;
      ddy = cos(angle) * vel;
   }

private:
   double ddx;
   double ddy;
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Shell
{

public:
private:
   Angle angle;
   Acceleration accel;
   Position pos;
};

/* ********************************************
 * TODO  main header
 * ***************************************** */
int main(int argc, char *argv[])
{
   double vel = 827.0;   // speed of shell when leaving barrel
   double angle = 1.309; // 75 in rad

   Position pos;
   Acceleration accel();

   for (double i = 0; i <= 20; i++)
   {
      cout << "Distance: " << pos.getMetersX() << "Altitude: " << pos.getMetersY() << endl;
   };

   cout << "pop" << endl;
   return 0;
}
