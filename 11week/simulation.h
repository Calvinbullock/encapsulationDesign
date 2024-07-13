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
#include "uiDraw.h"
#include <iostream>


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(), 
                                               howitzer() 
   {
      ground = Ground(posUpperRight);
      howitzer.generatePosition(posUpperRight);
      howitzer = Howitzer();
   }

   void draw(ogstream &gout) 
   {
      ground.draw(gout);
      howitzer.draw(gout, 0.0);
   }

private:
   Ground ground;
   Howitzer howitzer;

};
