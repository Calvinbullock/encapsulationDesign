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
class Velocity
{

public:
   Velocity(double vel) : vel(vel) {}
   double getVel() {return vel;}

private:
   double vel;
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Acceleration
{

public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   double getDDX() const { return this->ddx; }
   double getDDY() const { return this->ddy; }

   void set(double angle, double vel)
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
Position newPos(Position currPos, Velocity vel, double time) {
   currPos.setMetersX((currPos.getMetersX() + vel.getVel()) * time);
   currPos.setMetersY((currPos.getMetersY() + vel.getVel()) * time);
   return currPos;
}

/* ********************************************
 * TODO  main header
 * ***************************************** */
int main(int argc, char *argv[])
{
   Velocity vel = Velocity(827.0);
   double angle = 1.309; // 75 in rad

   Position pos;
   Acceleration accel;

   accel.set(angle, vel.getVel());

   for (double i = 0; i <= 20; i++)
   {
      cout << "Distance: " << pos.getMetersX() << ", Altitude: " << pos.getMetersY() << endl;
      pos = newPos(pos, vel, 1);
   };

   cout << "pop" << endl;
   return 0;
}
