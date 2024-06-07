#include "position.h"
#include <iostream>
using namespace std;

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
