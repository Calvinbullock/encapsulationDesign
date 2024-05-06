/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h> // for floor()
#include <cassert>
using namespace std;

class Angle
{
private:
   double radian;

public:
   // Angle() {}
   // + Angle(degrees : Double)
   // + Angle(rhs : Angle)
   double getDegrees()
   {
      return convertToDegrees(radian);
   }

   double getRadians()
   {
      return radian;
   }

   double setDegrees(double new_degree)
   {
      radian = convertToRadians(new_degree);
   }

   double setRadians(double new_radian)
   {
      radian = new_radian;
   }
   // + setUp()
   // + setDown()
   // + setLeft()
   // + setRight()
   // + reverse()
   // + addOnto(delta : Double)

private:
   double convertToDegrees(double r) const
   {
      double d = r * (180.0 / M_PI);
      return d;
   }
   double convertToRadians(double d) const
   {
      double r = (2 * M_PI) * (d / 360);
      return r;
   }

   /************************************
    * ANGLE : NORMALIZE
    ************************************/
   double Angle::normalize(double radians) const
   {
      
      return -99.9;
   }
};