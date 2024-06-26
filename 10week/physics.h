/***********************************************************************
 * Header File:
 *    PHYSICS
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/

#pragma once

#include <cmath>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <cassert>  // for ASSERT 

 /*******************************************************
  * AREA FROM RADIUS
  * Compute the area of a circle from the radius
  *    area = pi * radius ^ 2
  ********************************************************/
inline double areaFromRadius(double radius)
{
   return M_PI * (radius * radius);
}

/**********************************************************
 * FORCE FROM DRAG
 * Determine the drag on a shell based on several things:
 *    density  : The density of the air ?
 *    drag     : The drag coefficient of the shell (no units)
 *    radius   : the radius of the shell (m)
 *    velocity : the velocity of the shell (m/s)
 * This force is determined by
 *    force = 1/2 density drag area velocity ^ 2
 ************************************************************/
inline double forceFromDrag(double density, double drag, 
                            double radius, double velocity)
{
   return 0.5 * density * drag * areaFromRadius(radius) * (velocity * velocity);
}

/**********************************************************
 * ACCELERATION FROM FORCE
 * How much acceleration can we expect from a given force
 *    force        : N
 *    mass         : kg
 *    acceleration : m / s^2
 * Equation:
 *    f = m a
 ************************************************************/
inline double accelerationFromForce(double force, double mass)
{
   return force / mass;
}

/***********************************************************
 * VELOCITY FROM ACCELERATION
 * Determine how much velocity will be imparted in a given amount of time
 * from a given acceleration
 *    acceleration : m / s^2
 *    time         : s
 * Equation:
 *    v = a t
 ************************************************************/
inline double velocityFromAcceleration(double acceleration, double time)
{
   return acceleration * time;
}

/*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *
 *    |        *(d1,r1)
 *    |       /
 *    |      *(d,r)
 *   r|     /
 *    |    *(d0,r0)
 *    |
 *    +-------------
 *           d
 * equation:
 *   (r - r0) / (d - d0) = (r1 - r0) / (d1 - d0)
 * Thus:
 *   r  = r0 + (r1 - r0) (d - d0) / (d1 - d0)
 *********************************************************/
inline double linearInterpolation(double d0, double r0,
                                  double d1, double r1,
                                  double d)
{
   return r0 + (r1 - r0) * (d - d0) / (d1 - d0);
}

/*********************************************************
 * MAPPING
 * A simple structure to represent the domain and the range.
 * We use this for linear interpolation
 *********************************************************/
struct Mapping
{
   double domain;
   double range;
};

/*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain);


/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude);

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude);

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 ********************************************************/
double speedSoundFromAltitude(double altitude);

/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient as a function of the speed of sound
 *********************************************************/
double dragFromMach(double speedMach);



  Mapping dragFromMachMap[14] = {
    {0.0, 9.807},
    {1000.0, 9.804},
    {2000.0, 9.801},
    {3000.0, 9.797},
    {4000.0, 9.794},
    {5000.0, 9.791},
    {6000.0, 9.788},
    {7000.0, 9.785},
    {8000.0, 9.782},
    {9000.0, 9.779},
    {10000.0, 9.776},
    {15000.0, 9.761},
    {20000.0, 9.745},
    {25000.0, 9.730}
  };

  Mapping gravityFromAltitudeMap[16] = {
    {0.300, 0.1629},
    {0.500, 0.1659},
    {0.700, 0.2031},
    {0.890, 0.2597},
    {0.920, 0.3010},
    {0.960, 0.3287},
    {0.980, 0.4002},
    {1.000, 0.4258},
    {1.020, 0.4335},
    {1.060, 0.4483},
    {1.240, 0.4064},
    {1.530, 0.3663},
    {1.990, 0.2897},
    {2.870, 0.2297},
    {2.890, 0.2306},
    {5.000, 0.2656}
  };