/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Calvin, Bullock
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"
#include <iostream>

/***************************************************************
 * RESET
 * Reset the lander and its position to start the game over
 ***************************************************************/
void Lander ::reset(const Position &posUpperRight)
{
   angle.setRadians(0.0);
   pos = Position(99.0, random(75.0, 95.0));
   velocity = Velocity(random(-10.0, -4.0), random(-2.0, 2.0));
   status = PLAYING;
   fuel = 5000;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander ::draw(const Thrust &thrust, ogstream &gout) const
{
   Position startPos = Position(300, 300);
   Angle a = Angle(0);
   gout.drawLander(pos, a.getDegrees());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander ::input(const Thrust &thrust, double gravity)
{
   double thr = thrust.mainEngineThrust();
   double ddx = 0.0;
   double ddy = 0.0;

   // check if rotating
   if (fuel >= 1 && (thrust.isClock() == true || thrust.isCounter() == true))
   {
      fuel--;
      angle.add(thrust.rotation());
   }

   // use main thruster
   if (fuel >= 10 && (thrust.isMain() == true))
   {
      fuel -= 10;
      ddx = -1 * (sin(angle.getRadians()) * (thr + velocity.getDX()));
      ddy = cos(angle.getRadians()) * (thr + velocity.getDY());
   }

   ddy += gravity;
   Acceleration accel = Acceleration(ddx, ddy);
   return accel;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 * newPos = currentPos + velocity * time + .5 * acceleration * time^2
 *******************************************************************/
void Lander ::coast(Acceleration &acceleration, double time)
{
   // calculate new velocity
   velocity.add(acceleration, time);

   // get variables
   // NOTE We decided on readability over memory efficiency
   double currentPosX = pos.getX();
   double currentPosY = pos.getY();
   double ddx = acceleration.getDDX();
   double ddy = acceleration.getDDY();
   double dx = velocity.getDX();
   double dy = velocity.getDY();

   // calculate new x/y position
   double newPosX = currentPosX + (dx * time) + (0.5 * ddx * (time * time));
   double newPosY = currentPosY + (dy * time) + (0.5 * ddy * (time * time));

   // set new position
   pos.setX(newPosX);
   pos.setY(newPosY);
}
