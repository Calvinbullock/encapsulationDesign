/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "angle.h"      // angle of the lander
#include "ground.h"     // for GROUND
#include "position.h"   // everything should have a point
#include "test.h"       // for the unit tests
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "uiInteract.h" // for INTERFACE
#include <cassert>      // for ASSERT
#include <cmath>        // for SQRT
using namespace std;

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
 public:
   // set up the simulator
   Simulator(const Position &posUpperRight) : ground(posUpperRight) {}

   // display stuff on the screen
   void display();

   unsigned char phase;
   Angle a;
   Ground ground;
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()
{
   ogstream gout;
   Position posLander = Position(200, 350);
   Position posStar = Position(250, 250);
   phase = 0;

   // draw the ground
   ground.draw(gout);

   // draw the lander
   gout.drawLander(posLander, a.getRadians());

   // twinkle the star
   phase = random(0, 210);
   gout.drawStar(posStar, phase);
}

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Simulator *pSimulator = (Simulator *)p;

   // draw the game
   pSimulator->display();

   // handle input
   if (pUI->isRight())
      pSimulator->a.add(.5); // rotate right here

   if (pUI->isLeft())
      pSimulator->a.add(-.5); // rotate left here
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

   /* WARN  lander is disabled*/
   /*// Initialize OpenGL*/
   /*Position posUpperRight(400, 400);*/
   /*Interface ui("Lunar Lander", posUpperRight);*/
   /**/
   /*// Initialize the game class*/
   /*Simulator simulator(posUpperRight);*/
   /**/
   /*// set everything into action*/
   /*ui.run(callBack, (void *)&simulator);*/

   return 0;
}
