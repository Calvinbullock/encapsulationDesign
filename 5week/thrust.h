/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Calvin, Bullock
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h" // for Interface

#define THRUST 45000.00; // thrust in newtons
#define WEIGHT 15103.00; // weight in kg

class TestLander;
class TestThrust;

/*****************************************************
 * THRUST
 * Represents activation of thrusters
 *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;

 public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      return clockwise ? (counterClockwise ? 0.0 : 0.1)
                       : (counterClockwise ? -0.1 : 0.0);
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const { return 45000.00 / 15103.00 / 1.0; }
   // BUG  this const are troughing errors
   // double mainEngineThrust() const { return THRUST / WEIGHT / 1.0; }

   // reflect what is firing
   bool isMain() const { return mainEngine; }
   bool isClock() const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface *pUI)
   {
      mainEngine = pUI->isDown() ? true : false;
      clockwise = pUI->isLeft() ? true : false;
      counterClockwise = pUI->isRight() ? true : false;
   }

 private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
