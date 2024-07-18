/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Calvin, Hyrum
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "acceleration.h"
#include "velocity.h"

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Position::Position(double x, double y) : x(), y()
{
   this->x = x;
   this->y = y;
}

/******************************************
 * POINT : ADD
 * Update point based on the distance formula
 *   s = s_0 + vt + 1/2 a t^2
 *****************************************/
void Position::add(const Acceleration &a, const Velocity &v, double t)
{
   x = x + v.getDX() * t + (0.5 * a.getDDX() * (t * t));
   y = y + v.getDY() * t + (0.5 * a.getDDY() * (t * t));
}

Position &Position::operator=(const Position &rhs)
{
   if (this != &rhs)
   {
      x = rhs.x;
      y = rhs.y;
   }
   return *this;
}