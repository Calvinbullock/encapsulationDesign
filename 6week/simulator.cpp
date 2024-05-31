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
      // create 50 stars add them to star list
      for (int i = 0; i <= 50; i++)
      {
         Star temp = Star(startingPos);
         temp.reset(400, 400);
         starList.push_back(temp);
      }
      lander.reset(startingPos);
   }

   Ground ground;

   // pSimulator->lander
   Position startingPos = Position(400, 400);
   Lander lander = Lander(startingPos);

   // star list
   std::vector<Star> starList = {};
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
   Position pos(10, 380);

   // declerations
   ogstream gout;
   Thrust t = Thrust();
   Acceleration accel;

   // reset lander if spacebar is activated
   if (pUI->isSpace())
   {
      pSimulator->lander.reset(pSimulator->startingPos);
      pSimulator->ground.reset();
   }

   // check if lander has hit the ground
   if (pSimulator->lander.isFlying() != PLAYING)
   {
      // get thrust direction
      t.set(pUI);
      accel = pSimulator->lander.input(t, GRAVITY);
      pSimulator->lander.coast(accel, .1);
   }

   // draw 50 stars
   for (int i = 0; i <= 50; i++)
   {
      pSimulator->starList[i].draw(gout);
   }

   // draw the ground
   pSimulator->ground.draw(gout);

   // get reused lander variables after lander movement update
   Position landerPos = pSimulator->lander.getPosition();
   int landerWidth = pSimulator->lander.getWidth();

   // display lander stats in gui window
   gout = pos;
   gout << "Fuel: " << pSimulator->lander.getFuel()
        << "\nAltitude: " 
         << pSimulator->ground.getElevation(landerPos)
        << "\nSpeed: " << pSimulator->lander.getSpeed();

   // draw lander
   pSimulator->lander.draw(t, gout);

   // check if lander hit ground or platform safely
   if (pSimulator->ground.onPlatform(landerPos, landerWidth)
      && pSimulator->lander.getSpeed() <= pSimulator->lander.getMaxSpeed())
   {
      // land if lander is on platform and at right speed
      pSimulator->lander.land();
   }
   else if (pSimulator->ground.getElevation(landerPos) < 0.0 
      || pSimulator->ground.hitGround(landerPos, landerWidth))
   {
      // crash if lander hits the ground
      pSimulator->lander.crash();
   }
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
