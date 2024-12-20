/**********************************************************************
 * LAB 06
 *
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Lunar Lander simulation. This is the Game class and main()
 *
 **********************************************************************/

#include "acceleration.h" // for ACCELERATION
#include "ground.h"       // for GROUND
#include "lander.h"       // for LANDER
#include "position.h"     // everything should have a point
#include "star.h"         // for STAR
#include "test.h"         // for the unit tests
#include "thrust.h"
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "uiInteract.h" // for INTERFACE
#include <cassert>      // for ASSERT
#include <cmath>        // for SQRT
#include <csignal>
#include <vector>
using namespace std;

#define GRAVITY -1.62 // gravity of the moon m/s^2

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position &posUpperRight, int starCount) : ground(posUpperRight)
   {
      makeStars(starCount);
      lander.reset(upperRightCorner);
   }

   Ground            ground;
   Position          upperRightCorner = Position(400, 400);
   Lander            lander      = Lander(upperRightCorner);
   std::vector<Star> starList    = {};

   /*************************************
   *  METHODS
   **************************************/

   void resetSimulator(const Interface *pUI)
   {
      if (pUI->isSpace())
      {
         lander.reset(upperRightCorner);
         ground.reset();
      }
   }

   void thrsutInput(const Interface *pUI, Thrust &landerThrust)
   {
      if (lander.isFlying() != PLAYING)
      {
         // get thrust direction
         landerThrust.set(pUI);
         Acceleration accel = lander.input(landerThrust, GRAVITY);
         lander.coast(accel, .1);
      }
   }

   void makeStars(int starCount)
   {
      // create X stars add them to starList
      for (int i = 0; i <= starCount; i++)
      {
         Star temp = Star(upperRightCorner);
         temp.reset(400, 400);
         starList.push_back(temp);
      }
   }

   void drawStars(ogstream &gout)
   {
      for (int i = 0; i <= starList.size(); i++)
      {
         starList[i].draw(gout);
      }
   }

   void drawLanderStats(ogstream &gout)
   {
      Position pos(10, 380);

      // display lander stats in gui window
      gout = pos;
      gout << "Fuel: " << lander.getFuel() << "\nAltitude: "
           << ground.getElevation(lander.getPosition())
           << "\nSpeed: " << lander.getSpeed();
   }

   void landerCollisionCheck(ogstream &gout)
   {
      Position centerPos(100, 200);

      // check if lander hit ground or platform safely
      if (ground.onPlatform(lander.getPosition(), lander.getWidth()) 
         && lander.getSpeed() <= lander.getMaxSpeed())
      {
         // land if lander is on platform and at right speed
         lander.land();
         gout = centerPos;
         gout << "one small step for man,\none giant leap for mankind";
      }
      else if (ground.getElevation(lander.getPosition()) < 0.0 
         || ground.hitGround(lander.getPosition(), lander.getWidth()))
      {
         // crash if lander hits the ground
         lander.crash();
         gout = centerPos;
         gout << "Houston, we have a problem";
      }
   }
};

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Simulator *pSimulator = (Simulator *)p;
   ogstream gout;
   Thrust landerThrust = Thrust();

   // reset simulator if spacebar is activated
   pSimulator->resetSimulator(pUI);

   // check if lander has hit the ground
   pSimulator->thrsutInput(pUI, landerThrust);

   // draw sim entities
   pSimulator->drawStars(gout);
   pSimulator->ground.draw(gout);
   pSimulator->drawLanderStats(gout);
   pSimulator->lander.draw(landerThrust, gout);

   // check if lander hits the ground / platform
   pSimulator->landerCollisionCheck(gout);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else  // !_WIN32
int main(int argc, char **argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class, create 50 stars to draw
   Simulator simulator(posUpperRight, 50);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
