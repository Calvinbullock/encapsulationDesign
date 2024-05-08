/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle()                 : radians(-99.9)  {}
   Angle(const Angle& rhs) : radians(-99.9)  {}
   Angle(double degrees)   : radians(-99.9)  {}

   // Getters
   double getDegrees() const { return convertToDegrees(this -> radians); }
   double getRadians() const { return this -> radians; }

   // Setters
   void setDegrees(double degrees) {this -> radians = convertToRadians(degrees); }
   void setRadians(double radians) {this -> radians; }
   void setUp()                    {this -> radians = convertToRadians(0.0); }
   void setDown()                  {this -> radians =  convertToRadians(180.0); }
   void setRight()                 {this -> radians =  convertToRadians(90.0); }
   void setLeft()                  {this -> radians =  convertToRadians(270.0); }
   void reverse()                  { }
   Angle& add(double delta) { radians = -99.9; return *this; }

private:
   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;
   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
};

