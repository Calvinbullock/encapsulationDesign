/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
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
   // double normalizedRadians;

   // check if radians needs to be normalized
   if (radians > TWO_PI)
   {
      radians = fmod(radians, TWO_PI);
   }

   while(radians < 0)
   {
      radians = radians + TWO_PI;
   }

   
   return radians;
}



