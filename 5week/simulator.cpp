/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "thrust.h"
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <iostream>
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
   Simulator(const Position & posUpperRight) : ground(posUpperRight) {}
   Ground ground;

   // pSimulator->lander 
   Position startingPos = Position(400, 400);
   Lander lander = Lander(startingPos);
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;

   ogstream gout;
   Thrust t = Thrust();
   Acceleration accel;

   // draw the ground
   pSimulator->ground.draw(gout);

   // reset pSimulator->lander if spacebar is activated
   if (pUI->isSpace()) 
   {
      pSimulator->lander.reset(pSimulator->startingPos);
   }

   // draw pSimulator->lander
   pSimulator->lander.draw(t, gout);
    
   // thrust direction
   t.set(pUI);
   accel = pSimulator->lander.input(t, GRAVITY);
   pSimulator->lander.coast(accel, .1);
    
    // draw star WARN  broken
    std::vector<Star> starList = {};
    for (int i = 0; i <= 50; i++)
    {
        Star temp = Star(pSimulator->startingPos);
        temp.draw(gout);
        starList.push_back(temp);
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
#else // !_WIN32
int main(int argc, char** argv)
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
