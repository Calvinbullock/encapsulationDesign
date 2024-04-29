/*************************************************************
 * 1. Name:
 *      Calvin Bullock, Hyrum Bullock
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      TODO -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      TODO -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#include <iostream> // for CIN and COUT
#include <string>
#include <cassert>
using namespace std;

#define WEIGHT 15103.000 // Weight in KG
#define GRAVITY -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST 45000.000 // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double startPos, double velocity, double aceel, double time) 
{
   double endPos;
   endPos = startPos + velocity * time + .5 * aceel * (time * time);
   return endPos;
}

/***************************************************
 * TEST COMPUTE DISTANCE
 * Tests compute distance
 *
 * OUTPUT
 *      returns 0 if pass
***************************************************/
int testComputeDistance() 
{
   double stP;
   double vel;
   double accel;
   double time;
   
   // sanity check
   assert(computeDistance(0, 0, 0, 0) == 0);

   // normal case 
   stP = 2.3;
   vel = 2.3;
   accel = 3.3;
   time = 4.0;
   assert(computeDistance(stP, vel, accel, time) == 37.9);

   return 0;
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
// your function goes here
double computeAcceleration(double force, double mass)
{
   // to find acceleration we need to change the
   // formula to accel = force/mass
   double accel = force / mass;
   return accel;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double vel, double accel, double time) 
{
   double endVel;
   endVel = vel + accel * time;
   return endVel;
}


/***********************************************
 * TEST COMPUTE VELOCITY
 * 
 * OUTPUT
 *      returns 0 if pass
***********************************************/
void testComputeVelocity() 
{
   double vel;
   double accel;
   double time;

   // Sanity check  
   assert(computeVelocity(0, 0, 0) == 0);

   // 
   vel = 2.3;
   accel = 3.3;
   time = 4.0;
   assert(computeVelocity(vel, accel, time) == 15.5);
}

/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
// your function goes here

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
// your function goes here

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
// your function goes here

/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
// your function goes here

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
// your function goes here
double prompt(string text)
{
   cout << text << endl;
   
   return 0;
}

/**************************************************
 * TEST RUNNER
 *
 * runs all the test functions
**************************************************/
void testRunner() 
{
   testComputeDistance();
   testComputeVelocity();
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{ 
   testRunner();

   double dx = prompt("What is your horizontal velocity (m/s)? ");
   double dy = prompt("What is your vertical velocity (m/s)? ");
   double y = prompt("What is your altitude (m)? ");
   double x = prompt("What is your position (m)? ");
   double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   double t = prompt("What is the time interval (s)? ");
   double aRadians;           // Angle in radians
   double accelerationThrust; // Acceleration due to thrust
   double ddxThrust;          // Horizontal acceleration due to thrust
   double ddyThrust;          // Vertical acceleration due to thrust
   double ddx;                // Total horizontal acceleration
   double ddy;                // Total vertical acceleration
   double v;                  // Total velocity

   // Go through the simulator five times
   // your code goes here

   // Output
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(2);
   cout << "\tNew position:   (" << x << ", " << y << ")m\n";
   cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
   cout << "\tTotal velocity:  " << v << "m/s\n\n";

   return 0;
}
