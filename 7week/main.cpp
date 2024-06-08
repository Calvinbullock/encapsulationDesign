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

#define ENVIRONMENTALTABLELENGTH 20 // density and speed of sound table length.
#define GRAVITYTABLELENGTH 14       // gravity table length.
#define MACHTABLELENGTH 20          // Mach speed table length.

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

// TODO  move this into velocity class
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
 * CALCULATE ACCELERATION
 *    gets acceleration using newtons 2nd law
 * ***************************************** */
double calcAcceleration(double force, double mass)
{
   return force / mass;
}

/* ********************************************
 * CALCULATE ACCELERATION COMPONENT X
 *    Calculate horizontal component of
 *    acceleration
 * ***************************************** */
double calcAccelComponentX(double angle, double accel)
{
   return -sin(angle) * accel;
}
/* ********************************************
 * CALCULATE ACCELERATION COMPONENT Y
 *    Calculate vertical component of
 *    acceleration
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
 * LINEAR SEARCH
 *    Search a list for the value before the target
 *
 *    returns the index of the value, add one to get
 *    the other pair
 * ***************************************** */
int linearSearch(double targetValue, double list[], int listLength)
{
   for (int i = 0; i < listLength; i++)
   {
      // cout << "line, 100, " << list[i] << ", " << targetValue << endl;
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
double linearInterpolation(double xPos, double yPos, double xPos1, double yPos1, double givenYPos)
{
   return xPos + ((givenYPos - yPos) * (xPos1 - xPos)) / (yPos1 - yPos);
}

/* ********************************************
 * CALCULATE SURFACE AREA
 *    Calculates and returns the surface area
 * ***************************************** */
double calcSurfaceArea(double radius)
{
   return M_PI * (radius * radius);
}

/* ********************************************
 * CALCULATE DRAG FORCE
 *    Calculates the drag force
 *    d = ½ c ρ v2 a
 * ***************************************** */
double calcDragForce(double drag, double gasDensity, Velocity *vel, double surArea)
{
   return .5 * drag * gasDensity * (vel->getDX() * vel->getDX()) * surArea;
}

/* ********************************************
 * PYTHAGOREAN THEOREM
 *    Calculates the Pythagorean theorem
 *    and returns the result
 * ***************************************** */
double pythagoreanTheorem(double dx, double dy)
{
   return sqrt((dx * dx) + (dy * dy));
}

/* ********************************************
 * LINEAR INTERPOLATION LIST WRAPPER
 *    Wraps the code to plug lists into
 *    linear interpolation function
 *
 *    returns the interpolated x value 
 *
 * ***************************************** */
double linearInterpolationListWrapper(double listX[], double listY[], int listLength, double yTarget)
{
   int index = linearSearch(yTarget, listY, listLength);
   return linearInterpolation(listX[index], listY[index], listX[index + 1], listY[index + 1], yTarget);
}

/* ********************************************
 * MAIN
 *    this is the main man
 * ***************************************** */
int main(int argc, char *argv[])
{
   // gravity table - altitude = x, gravity = y
   double altitudeTable[GRAVITYTABLELENGTH] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000};
   double gravityTable[GRAVITYTABLELENGTH] = {-9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785, -9.782, -9.779, -9.776, -9.761, -9.745, -9.730};

   // mach to drag coefficient table - mach = x, drag = y
   double machTable[MACHTABLELENGTH] = {0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000};
   double dragCoefficentTable[MACHTABLELENGTH] = {0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656};

   // x values of the tables
   double highAltitudeTable[ENVIRONMENTALTABLELENGTH] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000};
   // y values of the tables
   double speedOfSoundTable[ENVIRONMENTALTABLELENGTH] = {340, 336, 332, 328, 324, 320, 316, 312, 308, 303, 299, 295, 295, 295, 305, 324, 337, 319, 289, 269};
   double airDensityTable[ENVIRONMENTALTABLELENGTH] = {1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185};

   // Shell stats - const
   double mass = 46.7;                  // kg
   double shellRadius = 0.015489 / 2.0; // m
   double surArea = calcSurfaceArea(shellRadius);

   // initial shell stats
   Position pos;
   double angle = toRadians(75); // rad
   double initVel = 827.0;       // m/sec
   Velocity vel = Velocity();
   vel.setComponents(angle, initVel);

   double time = 0.0;          // sec
   double timeInterval = 0.01; // sec

   // the 2nd last time and altitude variables
   double prevAltiude;
   double prevTime;
   double timeOfImpact;

   // loop until we hit the ground
   while (pos.getMetersY() > -1)
   {
      prevAltiude = pos.getMetersY();
      prevTime = time;

      // variables that are set by the loop
      double dragCoefficient = -0.3;      // drag
      double airDensity = 0.6; // kg/m^2
      double gravity;
      double speedOfSound;
      time += timeInterval;

      // Check if we hit the ground
      if (pos.getMetersY() >= 0)
      {
         // determine the gravity according to the altitude
         gravity = linearInterpolationListWrapper(gravityTable, altitudeTable, GRAVITYTABLELENGTH, pos.getMetersY());

         // determine the air density according to the altitude
         airDensity = linearInterpolationListWrapper(airDensityTable, highAltitudeTable, ENVIRONMENTALTABLELENGTH, pos.getMetersY());

         // determine the speed of sound according to the altitude
         speedOfSound = linearInterpolationListWrapper(speedOfSoundTable, highAltitudeTable, ENVIRONMENTALTABLELENGTH, pos.getMetersY());

         // determine mach
         double totalVel = pythagoreanTheorem(vel.getDX(), vel.getDY());
         double mach = totalVel / speedOfSound;

         // determine the drag coefficient according to the altitude
         dragCoefficient = linearInterpolationListWrapper(dragCoefficentTable, machTable, MACHTABLELENGTH, mach);
      }
      else
      {
         // return the gravity at ground level, if you are below 0
         gravity = -9.807;
      }

      // WARN  the drag calculations are not 100% right
      double dragForce = calcDragForce(dragCoefficient, airDensity, &vel, surArea);
      double dragAccel = calcAcceleration(dragForce, mass);

      double ddx = calcAccelComponentX(angle, dragAccel);
      double ddy = calcAccelComponentY(angle, dragAccel, gravity);

      calcVelocity(&vel, timeInterval, ddx, ddy);
      changeInPostion(&pos, &vel, timeInterval, ddx, ddy);
   
      timeOfImpact = linearInterpolation(prevTime, prevAltiude, time, pos.getMetersY(), 0);
   
      // TODO remove this 
      cout << "Distance:  " << pos.getMetersX() << ",  Altitude: " << pos.getMetersY() << ", HangTime:  " << time << endl;
   }

   cout << "Distance:  " << pos.getMetersX() << ", HangTime:  " << timeOfImpact << endl;

   return 0;
}
