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
   double speed      = pvt.v.getSpeed();
   double altitude   = pvt.pos.getMetersY();
   double interval   = simulationTime - pvt.t;

   // BUG  the DRAG is off
   // Find acceleration due to wind resistance. 
   double airDensity    = densityFromAltitude(altitude);
   double speedOfSound  = speedSoundFromAltitude(altitude);
   double mach          = speed / speedOfSound;
   double drag          = dragFromMach(mach);
   double windRes       = forceFromDrag(airDensity, drag, DEFAULT_PROJECTILE_RADIUS, speed);
   double accelMangnitude = accelerationFromForce(windRes, DEFAULT_PROJECTILE_WEIGHT);
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


