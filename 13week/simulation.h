/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "ground.h"
#include "howitzer.h"
#include "position.h"
#include "projectile.h"
#include "uiDraw.h"
#include "uiInteract.h" // for INTERFACE
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#define SIMTIME .2 // mili-seconds

/*********************************************
 * Simulation
 * Execute one simulation of a projectile being fired.
 *********************************************/
class Simulator
{
public:
   Simulator(const Position &posUpperRight)
       : ground(), howitzer(), shell(), simTime(0.0)
   {
      ground = Ground(posUpperRight);
      ground.reset(howitzer.getPosition());

      howitzer.generatePosition(posUpperRight);
      Position howitzerPos;
      howitzerPos.setPixelsX(howitzer.getPosition().getPixelsX());
      howitzerPos.setMetersY(ground.getElevationMeters(howitzer.getPosition()));
      howitzer.setPosition(howitzerPos);
   }

   void draw(ogstream &gout)
   {
      ground.draw(gout);
      howitzer.draw(gout, 3);
      shell.draw(gout);
   }

   void reset() 
   { 
      shell.reset(); 
      simTime = 0;
   }

   std::string getStatDisplay()
   {
      Angle elevation = howitzer.getElevation();
      Position shellPos = shell.getPojectilePosition();
      double shellSpeed = shell.getPojectileSpeed();

      if (shell.getIsFlying())
      {
         return "Distance: " + truncateString(shellPos.getMetersX(), 1) +
                " m/sec\nHeight:    " +
                truncateString(shellPos.getMetersY(), 1) +
                " m/sec\nSpeed:    " + truncateString(shellSpeed, 1) + " m/sec";
      }

      return "Elevation: " + truncateString(elevation.getDegrees(), 1) +
             " degrees";
   }

   void fireProjectile(ogstream &gout)
   {
      Position pos = howitzer.getPosition();
      Angle a = howitzer.getElevation();

      // pos.setPixelsX(pos.getPixelsX() + 5);
      // pos.setMetersY(pos.getMetersY() + .3);
      for (double age = 0; age <= 3; age += .1)
      {
         howitzer.draw(gout, age);
      }

      shell.fire(howitzer.getElevation(), pos, howitzer.getMuzzleVelocity());
   }

   void advanceProjectile()
   {
      simTime += SIMTIME;
      if (shell.getIsFlying())
         shell.advance(simTime);

      // check if shell has impacted ground
      Position pos = shell.getPojectilePosition();
      double groundY = ground.getElevationMeters(pos);
      shell.checkImpact(groundY);
   }

   void howizerControls(const Interface *pUI)
   {
      if (pUI->isRight())
         howitzer.rotate(0.04);

      if (pUI->isLeft())
         howitzer.rotate(-0.04);

      if (pUI->isDown())
         howitzer.raise(-0.01);

      if (pUI->isUp())
         howitzer.raise(0.01);
   }

   bool isProjectileFlying() { return shell.getIsFlying(); }

private:
   std::string truncateString(double value, int precision)
   {
      std::string num = std::to_string(value);

      for (int i = 0; i < num.length(); i++)
      {
         if (num[i] == '.')
         {
            i += precision + 1;
            return num.erase(i);
         }
      }

      return num;
   }

   Ground ground;
   Howitzer howitzer;
   Projectile shell;
   double simTime;
};
