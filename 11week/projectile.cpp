/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
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
   PositionVelocityTime currPvt = flightPath.back();

   double airDensity = densityFromAltitude(currPvt.pos.getMetersY());
   double totalVel = pythagoreanTheorem(currPvt.pos.getMetersX(), currPvt.pos.getMetersY());
   double grav = gravityFromAltitude(currPvt.pos.getMetersY());

   // find drag
   double speedOfSound = speedSoundFromAltitude(currPvt.pos.getMetersY());
   double mach = totalVel / speedOfSound;
   double drag = dragFromMach(mach);

   // find accel magnitude
   double force = forceFromDrag(airDensity, drag, DEFAULT_PROJECTILE_RADIUS, totalVel);
   double accelMangnitude = accelerationFromForce(force, DEFAULT_PROJECTILE_WEIGHT);

   // get angle
   Angle angle = Angle();
   angle.setDxDy(currPvt.v.getDX(), currPvt.v.getDY());

   // calc ddx, ddy
   // BUG  the ddx, ddy is wrong
   Acceleration accel = Acceleration();
   accel.set(angle, accelMangnitude);
   accel.setDDY(accel.getDDY() - grav);

   PositionVelocityTime pvt = PositionVelocityTime();
   pvt.pos.add(accel, currPvt.v, simulationTime);
   pvt.v.add(accel, simulationTime);
   pvt.t = simulationTime;

   flightPath.push_back(pvt);
}
