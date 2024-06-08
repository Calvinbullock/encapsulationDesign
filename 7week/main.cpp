/*************************************************************
 * 1. Name:
 *      Calvin, Hyrum Bullock
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      TODO
 * 5. How long did it take for you to complete the assignment?
 *      TODO
 *****************************************************************/

#include "position.h"
#include <cassert>
#include <iostream>
using namespace std;

#define ENVIRONMENTALLENGTH 20 // density and speed of sound table length.
#define GRAVITYTABLELENGTH 14  // gravity table length.
#define MACHTABLELENGTH 20     // Mach speed table length.

/* ********************************************
 * Velocity class
 *    handles velocity in the simulator
 *    gives direction to speed
 * ***************************************** */
class Velocity
{
public:
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   double getDX() const { return dx; }
   double getDY() const { return dy; }

   void setDX(double newDX) { dx = newDX; }
   void setDY(double newDY) { dy = newDY; }

   void set(double angle, double vel)
   {
      dx = sin(angle) * vel;
      dy = cos(angle) * vel;
   }

private:
   double dx;
   double dy;
};

// WARN  this might not be needed
/*// Function to calculate slope*/
/*double calculateSlope(double x1, double y1, double x2, double y2) {*/
/*   // Check for division by zero (avoid if x2 - x1 is 0)*/
/*   if (x2 - x1 == 0) {*/
/*      cout << "Error: Cannot calculate slope. Division by zero." << endl;*/
/*      return numeric_limits<double>::infinity(); // Return infinity as an error indicator*/
/*   }*/
/**/
/*   // Calculate slope using the formula (y2 - y1) / (x2 - x1)*/
/*   double slope = (y2 - y1) / (x2 - x1);*/
/*   return slope;*/
/*}*/

/* ********************************************
 * CALCULATE VELOCITY
 *    Adds the acceleration due to gravity
 *    to the vertical velocity
 * ***************************************** */
void calcVelocity(Velocity *vel, double grav, double time)
{
   vel->setDY(vel->getDY() + (grav * time));
}

/* ********************************************
 * CHANGE IN POSITION
 *    Calculates the change in position - inertia
 * ***************************************** */
void changeInPostion(Position *pos, Velocity *vel, double time, double grav)
{
   pos->setMetersX(pos->getMetersX() + vel->getDX() * time + (.5 * 0 * (time * time)));
   pos->setMetersY(pos->getMetersY() + vel->getDY() * time + (.5 * grav * (time * time)));
}

/* ********************************************
 * DEGREES TO RADIANS
 *    converts degrees to radians
 * ***************************************** */
double toRadians(double degree)
{
   return (degree * M_PI) / 180;
}

/* ********************************************
 * TODO
 *    the return +1 gives the next value
 * ***************************************** */
int linearSearch(double targetValue, double list[], int listLength)
{
   for (int i = 0; i < listLength; i++)
   {
      cout << "line, 100, " << list[i] << ", " << targetValue << endl;
      if (targetValue >= list[i] && targetValue <= list[i + 1])
      {
         return i;
      }
   }

   // assert will fire if target not in list.
   assert(false);
   return -1;
}

/* ********************************************
 * TODO
 * ***************************************** */
double gravatinalInterpalation(double xPos, double yPos, double xPos1, double yPos1)
{
   double ans = yPos + ((yPos1 - yPos) * (xPos - xPos1)) / (xPos1 - xPos);
   return ans;
}

/* ********************************************
 * MAIN
 *    this is the main man
 * ***************************************** */
int main(int argc, char *argv[])
{
   // gravity table altitude = x, gravity = y
   double altitudeTable[GRAVITYTABLELENGTH] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000};
   double gravityTable[GRAVITYTABLELENGTH] = {-9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785, -9.782, -9.779, -9.776, -9.761, -9.745, -9.730};

   // x values of the tables
   double highAltitudeTable[ENVIRONMENTALLENGTH] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000};
   // y values of the tables
   double speedOfSoundTable[ENVIRONMENTALLENGTH] = {340, 336, 332, 328, 324, 320, 316, 312, 308, 303, 299, 295, 295, 295, 305, 324, 337, 319, 289, 269};
   double airDensityTable[ENVIRONMENTALLENGTH] = {1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185};

   Position pos;
   double time = 0.0;
   double timeInterval = 0.01;
   double angle = toRadians(75);
   double initVel = 827.0;
   Velocity vel = Velocity();

   vel.set(angle, initVel);

   // loop until we hit the ground
   while (pos.getMetersY() > -1)
   {
      double gravity;
      int altitudeIndex;
      time += timeInterval;

      // Check if we hit the ground
      if (pos.getMetersY() >= 0)
      {
         // determine the gravity according to the altitude
         altitudeIndex = linearSearch(pos.getMetersY(), altitudeTable, GRAVITYTABLELENGTH);
         gravity = gravatinalInterpalation(
            altitudeTable[altitudeIndex], gravityTable[altitudeIndex], altitudeTable[altitudeIndex + 1], gravityTable[altitudeIndex + 1]);
      }
      else
      {
         // return the gravity at ground level, if you are below 0
         gravity = -9.807;
      }
      calcVelocity(&vel, gravity, timeInterval);
      changeInPostion(&pos, &vel, timeInterval, gravity);

      cout << "Distance:  " << pos.getMetersX() << ",  Altitude: " << pos.getMetersY() << ", HangTime:  " << time << endl;
   }

   return 0;
}
