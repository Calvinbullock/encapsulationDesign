/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiDraw.h"
#include <iostream>
#include "uiInteract.h" // for INTERFACE


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(), 
                                               howitzer(), 
                                               shell(),
                                               simTime(0.0)
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

   bool advanceProjectile()
   {
      simTime += .1;
      if (shell.getIsFlying()); 
         shell.advance(simTime);
   }

   void howizerControls(const Interface* pUI)
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

void fireProjectile(){
   
   shell.fire(howitzer.getElevation(), 
              howitzer.getPosition(), 
              howitzer.getMuzzleVelocity());

}

private:
   Ground ground;
   Howitzer howitzer;
   Projectile shell;
   double simTime;

};
