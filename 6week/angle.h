/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Calvin, Hyrum
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#include <cmath>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h> // for M_PI which is 3.14159
//
#define TWO_PI (2.0 * M_PI)

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
   Angle() : radians(0.0) {}
   Angle(const Angle &rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians()
   {
      this->radians = normalize(convertToRadians(degrees));
   }

   // Getters
   double getDegrees() const { return convertToDegrees(this->radians); }
   double getRadians() const { return this->radians; }

   // Setters
   void setDegrees(double degrees)
   {
      this->radians = normalize(convertToRadians(degrees));
   }
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp()
   {
      this->radians = normalize(convertToRadians(0.0));
   }
   void setDown()
   {
      this->radians = normalize(convertToRadians(180.0));
   }
   void setRight()
   {
      this->radians = normalize(convertToRadians(90.0));
   }
   void setLeft()
   {
      this->radians = normalize(convertToRadians(270.0));
   }
   void reverse()
   {
      this->radians = TWO_PI - fmod(this->radians, TWO_PI);
   }
   Angle &add(double delta)
   {
      this->radians = normalize(this->radians + delta);
      return *this;
   }

 private:
   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;
   double normalize(double radians) const;

   double radians; // 360 degrees equals 2 PI radians
};
