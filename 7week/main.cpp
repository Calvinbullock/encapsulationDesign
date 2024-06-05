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
   double getVel() { return vel; }

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

   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

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
 * TODO
 * ***************************************** */
double computeAcceleration(double force, double mass) {
   return force / mass;
}

/* ********************************************
 * CHANGE IN POSITION
 *    Calculates the change in position - inertia
 * ***************************************** */
void changeInPostion(Position *currPos, Acceleration *accel, double time)
{
   currPos->setMetersX((currPos->getMetersX() + accel->getDDX()) * time);
   currPos->setMetersY((currPos->getMetersY() + accel->getDDY()) * time);
}

/* ********************************************
 * TODO  main header
 * ***************************************** */
int main(int argc, char *argv[])
{

   /*double mass = 46.7;*/
   /*double force = 46.7 * 0;*/
   /*double initialAccel = computeAcceleration(force, mass);*/

   Velocity vel = Velocity(827.0);
   Position pos;

   double angle = 1.309; // 75 in rad
   Acceleration accel = Acceleration();

   accel.set(angle, vel.getVel());

   for (double i = 0; i <= 20; i++)
   {
      cout << "Distance: " << pos.getMetersX() << ", Altitude: " << pos.getMetersY() << endl;
      accel.set(angle, vel.getVel());
      changeInPostion(&pos, &accel, 1);
   };
   return 0;
}
