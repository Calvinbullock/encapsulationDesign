/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <cassert>
#include <math.h> // for sqrt()

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration &acceleration, double time)
{
   this->dx = dx + acceleration.getDDX() * time;
   this->dy = dy + acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed or magnitude
 *     | a /
 *     |  /
 *     | /
 *            _____________
 *  speed = \/ dx^2 + dy^2
 *********************************************/
double Velocity::getSpeed() const { return sqrt((dx * dx) + (dy * dy)); }

/*********************************************
 * VELOCITY : SET
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed or magnitude
 *     | a /
 *     |  /
 *     | /
 * dy = speed cos(a)
 * dx = speed sin(a)
 *********************************************/
void Velocity::set(const Angle &angle, double magnitude)
{
   this->dx = magnitude * sin(angle.getRadians());
   this->dy = magnitude * cos(angle.getRadians());
}

/************************************************
 * Velocity :: GET ANGLE
 * Determine the direction things are going
 * where 0 is up. This returns angle (clockwise) in radians
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    / speed
 *     | a /
 *     |  /
 *     | /
 *
 *  a = atan2(dx, dy)
 *  dx = cos(a) x speed
 *  dy = sin(a) x speed
 ************************************************/
Angle Velocity::getAngle() const
{
   // a = atan2(dx, dy);
   // dx = cos(a) * getSpeed();
   // dy = sin(a) * getSpeed();

   return Angle();
}
