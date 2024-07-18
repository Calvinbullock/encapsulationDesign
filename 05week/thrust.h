/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h" // for Interface

#define THRUST 2.9795404 // thrust in newtons / weight in kg

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
   double mainEngineThrust() const { return THRUST; }

   // reflect what is firing
   bool isMain   () const { return mainEngine;       }
   bool isClock  () const { return clockwise;        }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface *pUI)
   {
      mainEngine       = pUI->isDown()  ? true : false;
      clockwise        = pUI->isLeft()  ? true : false;
      counterClockwise = pUI->isRight() ? true : false;
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};