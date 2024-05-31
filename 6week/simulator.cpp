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
   Simulator(const Position &posUpperRight) : ground(posUpperRight)
   {
      // TODO  maybe add a diffrent way to add X stars
      // create 50 stars add them to starList
      for (int i = 0; i <= 50; i++)
      {
         Star temp = Star(startingPos);
         temp.reset(400, 400);
         starList.push_back(temp);
      }
      lander.reset(startingPos);
   }

   Ground            ground;
   Position          startingPos = Position(400, 400); // TODO rename?
   Lander            lander      = Lander(startingPos);
   std::vector<Star> starList    = {};

   /*************************************
   *  METHODS
   **************************************/

   void resetSimulator()
   {
      lander.reset(startingPos);
      ground.reset();
   }

   void drawStars(ogstream &gout)
   {
      for (int i = 0; i <= 50; i++) // TODO make this length more configurable
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
      Position centerPos(100, 200); // BUG  not completly centered

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
   Thrust t = Thrust(); // TODO  rename??

   // TODO  should this spce key ceck be in the resest func??/
   // reset simulator if spacebar is activated
   if (pUI->isSpace())
   {
      pSimulator->resetSimulator();
   }

   // TODO  make this a member func **thrustDirection()**
   // check if lander has hit the ground
   if (pSimulator->lander.isFlying() != PLAYING)
   {
      // get thrust direction
      t.set(pUI);
      Acceleration accel = pSimulator->lander.input(t, GRAVITY);
      pSimulator->lander.coast(accel, .1);
   }

   // draw sim entities
   pSimulator->drawStars(gout);
   pSimulator->ground.draw(gout); // BUG  this needs to be after the stars that should not be
   pSimulator->drawLanderStats(gout);
   pSimulator->lander.draw(t, gout);

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

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
