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
#include <cmath>
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

   void setComponents(double angle, double vel)
   {
      dx = sin(angle) * vel;
      dy = cos(angle) * vel;
   }

private:
   double dx;
   double dy;
};

/* ********************************************
 * CALCULATE VELOCITY
 *    Adds the acceleration due to gravity
 *    to the vertical velocity
 * ***************************************** */
void calcVelocity(Velocity *vel, double time, double ddx, double ddy)
{
   vel->setDX(vel->getDX() + (ddx * time));
   vel->setDY(vel->getDY() + (ddy * time));
}

/* ********************************************
 * CHANGE IN POSITION
 *    Calculates the change in position - inertia
 * ***************************************** */
void changeInPostion(Position *pos, Velocity *vel, double time, double ddx, double ddy)
{
   pos->setMetersX(pos->getMetersX() + vel->getDX() * time + (.5 * ddx * (time * time)));
   pos->setMetersY(pos->getMetersY() + vel->getDY() * time + (.5 * ddy) * (time * time));
   
}

/* ********************************************
 * TODO
 * ***************************************** */
double calcAcceleration(double force, double mass)
{
   return force / mass;
}
/* ********************************************
 * TODO
 * ***************************************** */
double calcAccelComponentX(double angle, double accel)
{
   return -sin(angle) * accel;
}
/* ********************************************
 * TODO
 * ***************************************** */
double calcAccelComponentY(double angle, double accel, double gravity)
{
   return gravity - cos(angle) * accel;
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
 * LINEAR SEARCH TODO 
 *    Search a list for the value before the target
 * ***************************************** */
int linearSearch(double targetValue, double list[], int listLength)
{
   for (int i = 0; i < listLength; i++)
   {
      //cout << "line, 100, " << list[i] << ", " << targetValue << endl;
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
 * LINEAR INTERPOLATION
 *    Calculates the value for x based on 
 *    the given y between two points on a
 *    slope.
 * ***************************************** */
double linearInterpalation(double xPos, double yPos, double xPos1, double yPos1, double givenYPos)
{
   return xPos + ((givenYPos - yPos )*(xPos1 - xPos))/(yPos1 - yPos);
}

/* ********************************************
 * TODO
 * ***************************************** */
double calcSurfaceArea(double radius)
{
   return M_PI * (radius * radius);
}

/* ********************************************
 * TODO
 *    d = ½ c ρ v2 a
 * ***************************************** */
double calcDragForce(double drag, double gasDensity, Velocity vel, double surArea)
{
   cout << vel.getDX() << endl;
   return .5 * drag * gasDensity * (vel.getDX() * vel.getDX()) * surArea;
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

   /*
   // x values of the tables
   double highAltitudeTable[ENVIRONMENTALLENGTH] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000};
   // y values of the tables
   double speedOfSoundTable[ENVIRONMENTALLENGTH] = {340, 336, 332, 328, 324, 320, 316, 312, 308, 303, 299, 295, 295, 295, 305, 324, 337, 319, 289, 269};
   double airDensityTable[ENVIRONMENTALLENGTH] = {1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185};
   */

   Position pos;
   double time = 0.0;                  // sec
   double initVel = 827.0;             // m/sec
   
   // temp
   double drag = -0.3;                 // drag
   double airDense = 0.6;              // kg/m^2
   double shellRadius = 0.015489 / 2.0;  // m
   double mass = 46.7;                 // kg
   double surArea =calcSurfaceArea(shellRadius);

   double timeInterval = 0.01;         // sec
   double angle = toRadians(75);       // rad

   Velocity vel = Velocity();
   vel.setComponents(angle, initVel);

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
         gravity = linearInterpalation(
            gravityTable[altitudeIndex], altitudeTable[altitudeIndex], gravityTable[altitudeIndex + 1], altitudeTable[altitudeIndex + 1], pos.getMetersY());
      }
      else
      {
         // return the gravity at ground level, if you are below 0
         gravity = -9.807;
      }

      // WARN  the drag calculations are not 100% right 
      double dragForce = calcDragForce(drag, airDense, vel, surArea);
      double dragAccel = calcAcceleration(dragForce, mass);

      double ddx = calcAccelComponentX(angle, dragAccel);
      double ddy = calcAccelComponentY(angle, dragAccel, gravity);


      // TODO make the variable order simmilerly
      calcVelocity(&vel, timeInterval, ddx, ddy);
      changeInPostion(&pos, &vel, timeInterval, ddx, ddy);

      cout << "Distance:  " << pos.getMetersX() << ",  Altitude: " << pos.getMetersY() << ", HangTime:  " << time << endl;
   }

   return 0;
}

