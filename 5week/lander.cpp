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

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   status = DEAD;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   pos.setX(-99.9);
   return Acceleration();
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
   double dx  = velocity.getDX();
   double dy  = velocity.getDY();

   // calculate new x/y position
   double newPosX = currentPosX + (dx * time) + (0.5 * ddx * (time * time));
   double newPosY = currentPosY + (dy * time) + (0.5 * ddy * (time * time));

   // set new position
   this->pos.setX(newPosX);
   this->pos.setY(newPosY);
}
