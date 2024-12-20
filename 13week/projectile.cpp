/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#include "projectile.h"
#include "acceleration.h"
#include "angle.h"
using namespace std;

/*********************************************
 * FIRE
 * sets the projectile to its inital Positions
 *    after leaving the barrel. Stores it in
 *    flight path.
 *********************************************/
void Projectile::fire(Angle angle, Position pos, double muzzleVelocity)
{
   isFlying = true;

   double timeInterval = 1.0;
   Acceleration accel = Acceleration();
   PositionVelocityTime pvt = PositionVelocityTime();

   // set velocity
   accel.set(angle, muzzleVelocity);
   pvt.v.add(accel, timeInterval);

   // set position
   pvt.pos.setPixelsX(pos.getPixelsX());
   pvt.pos.setPixelsY(pos.getPixelsY());

   pvt.t = timeInterval;
   flightPath.push_back(pvt);
}

/*********************************************
 * ADVANCE
 * Calculates the next position of the projectile
 *    and stores it in flightPath
 *********************************************/
void Projectile::advance(double simulationTime)
{
   // get the last point, speed and time interval
   PositionVelocityTime pvt = flightPath.back();
   double speed = pvt.v.getSpeed();
   double altitude = pvt.pos.getMetersY();
   double interval = simulationTime - pvt.t;

   // BUG  the DRAG is off
   // Find acceleration due to wind resistance.
   double airDensity = densityFromAltitude(altitude);
   double speedOfSound = speedSoundFromAltitude(altitude);
   double mach = speed / speedOfSound;
   double drag = dragFromMach(mach);
   double windRes =
      forceFromDrag(airDensity, drag, DEFAULT_PROJECTILE_RADIUS, speed);
   double accelMangnitude =
      accelerationFromForce(windRes, DEFAULT_PROJECTILE_WEIGHT);
   Acceleration windAccel;
   windAccel.set(-pvt.v.getAngle(), accelMangnitude);

   // Find acceleration due to gravity
   double grav = gravityFromAltitude(altitude);
   Angle gravAngle;
   gravAngle.setDown();
   Acceleration gravAccel;
   gravAccel.set(gravAngle, grav);

   Acceleration totalAccel = gravAccel + windAccel;

   // update pvt
   pvt.pos.add(totalAccel, pvt.v, interval);
   pvt.v.add(totalAccel, interval);
   pvt.t = simulationTime;

   flightPath.push_back(pvt);
}

/*********************************************
 * CHECK IMPACT
 * Checks if the projectile hits the ground
 *********************************************/
bool Projectile::checkImpact(double groundY)
{
   PositionVelocityTime pvt = flightPath.back();
   if (groundY >= pvt.pos.getMetersY() && pvt.t > 1)
      isFlying = false;

   return isFlying;
}

/*********************************************
 * CHECK TARGET IMPACT
 * Checks if the target has been hit.
 *********************************************/
bool Projectile::checkTargetImpact(Position targetPos)
{
   PositionVelocityTime pvt = flightPath.back();
   if (targetPos.getMetersX() >= pvt.pos.getMetersX() &&
       targetPos.getMetersX() + 10 <= pvt.pos.getMetersX() && !isFlying)
      return true;

   return false;
}

/*********************************************
 * DRAW
 * Draws the projectile and tail
 *********************************************/
void Projectile::draw(ogstream &gout)
{
   PositionVelocityTime pvt = flightPath.back();
   double age = 0.0;

   for (auto it = flightPath.rbegin(); it != flightPath.rend(); ++it)
   {
      gout.drawProjectile(it->pos, age);
      age += .25;
   }
}
