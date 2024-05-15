/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   this->dx = dx + acceleration.getDDX()*time;
   this->dy = dy + acceleration.getDDY()*time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
   return this->dx + this->dy;
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
   this->dx = magnitude * cos(angle.getDegrees());
   this->dy = magnitude * sin(angle.getDegrees());
}
