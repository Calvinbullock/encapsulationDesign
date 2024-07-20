/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "acceleration.h"
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), 
                  radius(DEFAULT_PROJECTILE_RADIUS) {}

   Projectile(double mass, double radius) : mass(mass), 
                                            radius(radius), 
                                            flightPath(),
                                            isFlying(false)
                                          {}

   void fire(Angle angle, Position pos, double muzzleVelocity);

   // advance the round forward until the next unit of time
   void advance(double simulationTime);

   // checks if the projectile has hit the ground
   bool checkImpact(double groundY) 
   {
      PositionVelocityTime pvt = flightPath.back();
      if (groundY >= pvt.pos.getMetersY()) 
         isFlying = false;

      return isFlying;
   }

   bool getIsFlying()
   {
      return isFlying;
   }

   Position getPojectilePosition()
   {
      PositionVelocityTime pvt = flightPath.back();
      return pvt.pos;
   }
   
   double getPojectileSpeed() 
   {
      PositionVelocityTime pvt = flightPath.back();
      return pvt.v.getSpeed();
   }

   void draw(ogstream & gout)
   {
      PositionVelocityTime pvt = flightPath.back();
      double age = 0.0;
         
      for (auto it = flightPath.rbegin(); it != flightPath.rend(); ++it)
      {
         gout.drawProjectile(it->pos, age);
         age += .25;
      }
   }


private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {
         pos = Position();
         v = Velocity();
      }
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
   bool isFlying;
};
