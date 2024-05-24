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
   status = PLAYING;
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
 *  a = f / m
 ***************************************************************/
Acceleration Lander ::input(const Thrust &thrust, double gravity)
{
   double thr = thrust.mainEngineThrust();
    std::cout << "th " << thr << std::endl;
   double deg = angle.getDegrees();
   double ddx;
   double ddy;

   if (fuel > 0 && (thrust.isMain() == true || thrust.isClock() == true || thrust.isCounter() == true))
   {
      fuel--;
      angle.add(thrust.rotation());

      if (deg == 0 || deg == 180)
      {
         // y thrust
         ddx = sin(angle.getRadians()) * (velocity.getDX());
         ddy = cos(angle.getRadians()) * (thr + velocity.getDY() + gravity);
      }
      else if (deg > 90 || deg > 270)
      {
         // x thrust
         ddx = sin(angle.getRadians()) * (thr + velocity.getDX());
         ddy = cos(angle.getRadians()) * velocity.getDY() + gravity;
    std::cout << ddx << std::endl;
    std::cout << ddy << std::endl;
      }
      else if ((deg > 0 && deg < 90) || (deg > 180 && deg < 270))
      {
         // (x,y)+ || (x,y)-
         ddx = sin(angle.getRadians()) * (thr + velocity.getDX());
         ddy = cos(angle.getRadians()) * (thr + velocity.getDY() + gravity);
      }
      else if ((deg > 90 && deg < 180) || (deg > 270 && deg < 360))
      {
         // x+,y- || x-,y+
         ddy = cos(angle.getRadians()) * (thr + velocity.getDY() + gravity);
         ddx = sin(angle.getRadians()) * (thr + velocity.getDX());
      }
   }
   else
   {
      ddx = sin(angle.getRadians()) * velocity.getDX();
      ddy = cos(angle.getRadians()) * velocity.getDY() + gravity;
   }

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
