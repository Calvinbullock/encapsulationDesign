/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Calvin, Hyrum
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <cassert>
#include <math.h> // for floor()
using namespace std;

/************************************
 * ANGLE : CONVERT TO DEGREES
 ************************************/
double Angle::convertToDegrees(double r) const
{
   double d = r * (180.0 / M_PI);
   return d;
}

/************************************
 * ANGLE : CONVERT TO RADIANS
 ************************************/
double Angle::convertToRadians(double d) const
{
   double r = (2.0 * M_PI) * (d / 360.0);
   return r;
}

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
      radians = fmod(radians, TWO_PI);
   return radians;
}
