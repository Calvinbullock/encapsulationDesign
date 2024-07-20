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
#include <iostream>
#include <string>

#define SIMTIME .3 // mili-seconds

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
      howitzer.draw(gout, 0.0);
      shell.draw(gout);
   }
   
   std::string getStatDisplay() 
   {
      Angle elevation   = howitzer.getElevation();
      Position shellPos = shell.getPojectilePosition();
      double shellSpeed = shell.getPojectileSpeed();

      if (shell.getIsFlying())
      {
         return "Pos: (" + std::to_string(shellPos.getMetersX()) + ", " + std::to_string(shellPos.getMetersY()) + ")\nSpeed: " + std::to_string(shellSpeed);
      }
      
      return "Elevation: " + std::to_string(elevation.getDegrees());

   }

   void fireProjectile()
   {
      Position pos = howitzer.getPosition();
      Angle a = howitzer.getElevation();

      //pos.setPixelsX(pos.getPixelsX() + 5);
      //pos.setMetersY(pos.getMetersY() + .3);

      shell.fire(
         howitzer.getElevation(),
         pos,
         howitzer.getMuzzleVelocity()
      );
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
      
      std::cout << "Flying? " << shell.getIsFlying() << std::endl;
      std::cout << "x,y " << pos.getPixelsX() << ", " << pos.getPixelsY() << std::endl;
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

   bool isProjectileFlying() {return shell.getIsFlying();}

private:
   Ground ground;
   Howitzer howitzer;
   Projectile shell;
   double simTime;
};
