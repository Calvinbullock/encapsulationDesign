/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"
#include <iterator>

/***************************************************************
 * RESET
 * Reset the lander and its position to start the game over
 ***************************************************************/
void Lander ::reset(const Position &posUpperRight)
{
   angle.setRadians(0.0);

   pos      = Position(posUpperRight.getX() * .99, random(posUpperRight.getY() * .75, posUpperRight.getY() * .95));
   velocity = Velocity(random(-10.0, -4.0), random(-2.0, 2.0));
   status   = PLAYING;
   fuel     = 5000;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander ::draw(const Thrust &thrust, ogstream &gout) const
{
   Position startPos = Position(pos.getX(), pos.getY());
   Angle a           = Angle(angle.getRadians());

   gout.drawLander      (pos, a.getDegrees());
   gout.drawLanderFlames(pos, a.getDegrees(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
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

   // check if rotating - fire rcs and use fuel
   if (fuel >= 1 && (thrust.isClock() == true || thrust.isCounter() == true))
   {
      fuel--;
      angle.add(thrust.rotation());
   }

   // use main thruster - fire main thruster and use fuel
   if (fuel >= 10 && (thrust.isMain() == true))
   {
      fuel  -= 10;
      ddx   += -1 * sin(angle.getRadians()) * thr;
      ddy   +=      cos(angle.getRadians()) * thr;
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

   // set new position
   pos.add(acceleration, velocity, time);
}
