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
       : ground(), howitzer(), shell(), simTime(0.0),
         posUpperRight(posUpperRight)
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
      shell.draw(gout);
      ground.draw(gout);
      howitzer.draw(gout, 3);
   }

   void resetProjectile()
   {
      shell.reset();
      simTime = 0;
   }

   void resetSim();

   std::string getStatDisplay();

   void fireProjectile(ogstream &gout);

   void advanceProjectile();

   bool isTargetHit() { return shell.checkTargetImpact(ground.getTarget()); }

   void howizerControls(const Interface *pUI);

   bool isProjectileFlying() { return shell.getIsFlying(); }

private:
   std::string truncateString(double value, int precision);

   Position posUpperRight;
   Ground ground;
   Howitzer howitzer;
   Projectile shell;
   double simTime;
};
