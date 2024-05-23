/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Calvin, Bullock
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
    void reset(double width, double height)
    {
        pos = Position(width, height);
    }

    void draw(ogstream gout)
    {
        gout.drawStar(pos, phase);
        if (phase > 215)
        {
            phase = 0;
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
