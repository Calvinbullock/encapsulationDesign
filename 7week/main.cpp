#include "position.h"
#include <iostream>
using namespace std;

/* ********************************************
 * Acceleration class
 *    handles acceleration in the simulator
 * ***************************************** */
class Acceleration
{

public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

   void set(double angle, double vel, double gravity = 0)
   {
      ddx = sin(angle) * vel;
      ddy = cos(angle) * vel;
   }

private:
   double ddx;
   double ddy;
};

/* ********************************************
 * CHANGE IN POSITION
 *    Calculates the change in position - inertia
 * ***************************************** */
void changeInPostion(Position *pos, Acceleration *accel, double time)
{
   pos->setMetersX((pos->getMetersX() + accel->getDDX()) * time);
   pos->setMetersY((pos->getMetersY() + accel->getDDY()) * time);

   // NOTE  this is the full distance formula - breaks the ans
   /*pos->setMetersX(pos->getMetersX() + vel * time + .5 * accel->getDDX() * (time * time));*/
   /*pos->setMetersY(pos->getMetersY() + vel * time + .5 * accel->getDDY() * (time * time));*/
}

/* ********************************************
 * TODO  main header
 * ***************************************** */
int main(int argc, char *argv[])
{
   double gravity = -9.8;

   /*double mass = 46.7;*/
   /*double force = 46.7 * 0;*/
   /*double initialAccel = computeAcceleration(force, mass);*/

   Position pos;
   double angle = 1.309; // 75 degrees
   double vel = 827.0;

   Acceleration accel = Acceleration();
   accel.set(angle, vel);

   // sim loop, 20 "frames"
   for (double i = 0; i <= 20; i++)
   {
      cout << "Distance: " << pos.getMetersX() << ", Altitude: " << pos.getMetersY() << endl;
      accel.set(angle, vel);
      changeInPostion(&pos, &accel, 1);
   };

   return 0;
}
