#include "position.h"
#include <iostream>
#include <numeric>
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

   void add(Acceleration &accel)
   {
      ddx += accel.getDDX();
      ddy += accel.getDDY();
      cout << "acel add " << ddx << endl;
      cout << "acel add " << ddy << "\n" << endl;
   }

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
void changeInPostion(Position *pos, Acceleration *accel, double time, Acceleration *grav)
{
   /*pos->setMetersX(pos->getMetersX() + (accel->getDDX() * time));*/
   /*pos->setMetersY(pos->getMetersY() + (accel->getDDY() * time));*/

   // NOTE  this is the full distance formula - breaks the ans
   pos->setMetersX(pos->getMetersX() + accel->getDDX() * time + .5 * 0 * (time * time));
   pos->setMetersY(pos->getMetersY() + accel->getDDY() * time + .5 * grav->getDDY() * (time * time));
}

/* ********************************************
 * TODO  header
 * ***************************************** */
double toRadians(double degree)
{
   return (degree * M_PI) / 180;
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
   double angle = toRadians(75);
   double vel = 827.0;
   Acceleration grav = Acceleration(0, gravity);
   Acceleration accel = Acceleration();

   accel.set(angle, vel);

   // sim loop, 20 "frames"
   for (double i = 0; i <= 20; i++)
   {
      cout << i << ", Distance: " << pos.getMetersX() << ", Altitude: " << pos.getMetersY() << endl;

      accel.add(grav);
      changeInPostion(&pos, &accel, 1, &grav);
   };

   return 0;
}
