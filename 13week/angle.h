/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#include <algorithm>
#include <cmath>
#include <math.h>   // for M_PI which is 3.14159
#define _USE_MATH_DEFINES
#define TWO_PI (2.0 * M_PI)

#include <iostream>

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle()                  : radians(0.0), dx(0.0), dy(0.0)               {}
   Angle(const Angle &rhs)  : radians(rhs.radians), dx(rhs.dx), dy(rhs.dy) {}
   Angle(double degrees)    : radians(), dx(), dy()          
   {
      radians = normalize(convertToRadians(degrees));
   }

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dx = sin a
   // dy = cos a
   double getDx() { return dx = sin(radians); }
   double getDy() { return dy = cos(radians); }
   bool   isRight()  const { return (radians >= convertToRadians(180.0) &&
                                     radians <= 2*M_PI); }

   bool   isLeft()   const { return (radians >= convertToRadians(0.0  ) && 
                                     radians <= convertToRadians(180.0)); }

   // Setters
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setDegrees(double degrees) 
   { 
      radians = normalize(convertToRadians(degrees));
   }

   void setUp() { radians = normalize(convertToRadians(0.0)); }
   void setDown() { radians = normalize(convertToRadians(180.0)); }
   void setRight() { radians = normalize(convertToRadians(90.0)); }
   void setLeft() { radians = normalize(convertToRadians(270.0)); }

   void reverse() { radians = TWO_PI - fmod(radians, TWO_PI); }
   Angle &add(double delta)
   {
      radians = normalize(radians + delta);
      return *this;
   }

   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy); 
   Angle operator+(double degrees) const { return Angle(); }

private:
   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;
   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
   double dx;
   double dy;
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}
