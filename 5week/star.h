/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h" // for POSITION
#include "uiDraw.h"   // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   Star(Position pos) : pos(pos), phase() { phase = random(1, 215); }
   void reset(double width, double height)
   {

      double randX = random(0.0, width);
      double randY = random(200.0, height);

      pos = Position(randX, randY);
   }

   void draw(ogstream &gout)
   {
      gout.drawStar(pos, phase);
      if (phase > 215)
      {
         phase = 1;
      }
      else
      {
         phase += 1;
      }
   }

private:
   Position pos;
   unsigned phase;
};
