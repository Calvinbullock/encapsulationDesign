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

#include <cassert>
#include <cmath>
#include <iostream> // for CIN and COUT
#include <string>
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
 ***************************************************/
void testComputeDistance()
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

/**************************************************
 * TEST COMPUTE ACCELERATION
 * test the F=MA calculations are correct
 ***************************************************/
void testComputeAcceleration()
{
   double force = 400;
   double mass = 20;
   double accel = 20;

   assert(computeAcceleration(force, mass) == accel);
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
double computeVerticalComponent(double total, double angle)
{
   double y = cos(angle) * total;
   return y;
}

/***********************************************
 * TEST COMPUTE VERTICAL COMPONENT
 ***********************************************/
void testComputeVerticalComponent()
{
   double total;
   double angle;

   // sanity check
   assert(computeVerticalComponent(0, 0) == 0);

   // normal case
   total = 4.0;
   angle = 3.3;
   // This assert takes in to account rounding tolerance
   assert(computeVerticalComponent(total, angle) - (-3.94992) <= 0.00001);
}

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
double computeHorizontalComponent(double total, double angle)
{
   double x;
   x = sin(angle) * total;
   return x;
}

/***********************************************
 * TEST COMPUTE HORIZONTAL COMPONENT
 ***********************************************/
void testComputeHorizontalComponent()
{
   double totalVel;
   double angle;

   // sanity check
   assert(computeHorizontalComponent(0, 0) == 0);

   // normal case
   totalVel = 4.0;
   angle = 3.3;
   // This assert takes in to account rounding tolerance
   assert(computeHorizontalComponent(totalVel, angle) - (-0.63098) <= 0.00001);
}
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
double computeTotalComponent(double hori, double vert)
{

   double totalCmpnt = sqrt((hori * hori) + (vert * vert));

   return totalCmpnt;
}

/**************************************************
 * TEST RADIANS FROM DEGEES
 * tests the math in radians to degrees
 ***************************************************/
void testComputeTotalComponent()
{

   double totalCmpnt = 28.284271247462;
   double hori = 20;
   double vert = 20;

   assert(computeTotalComponent(hori, vert) - (totalCmpnt) <= 0.00001);
}

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

double computeDegreestoRadians(double degrees)
{
   double radians = (2 * M_PI) * (degrees / 360);

   return radians;
}

/**************************************************
 * TEST RADIANS FROM DEGEES
 * tests the math in radians to degrees
 ***************************************************/
void testComputeDegreestoRadians()
{
   double radians = 0.3490658504;
   double degrees = 20;

   assert(computeDegreestoRadians(degrees) - (radians) <= 0.00001);
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string text)
{
   double input;

   cout << text << endl;
   cin >> input;

   cin.ignore(); // clear input buffer

   return input;
}

/**************************************************
 * TEST RUNNER
 * Runs all the test functions
 **************************************************/
void testRunner()
{
   testComputeDistance();
   testComputeVelocity();
   testComputeVerticalComponent();
   testComputeHorizontalComponent();

   testComputeAcceleration();
   testComputeDegreestoRadians();
   testComputeTotalComponent();

   cout << "testing Completed\n"
        << endl;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
   testRunner();
   
   // double dx = prompt("What is your horizontal velocity (m/s)? ");
   // double dy = prompt("What is your vertical velocity (m/s)? ");
   // double y = prompt("What is your altitude (m)? ");
   // double x = prompt("What is your position (m)? ");
   // double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   // double t = prompt("What is the time interval (s)? ");

   double dx = 0.0;
   double dy = -10.3;
   double y = 58.2;
   double x = 83.0;
   double aDegrees = -45.0;
   double t = 1.5;

   double aRadians;           // Angle in radians
   double accelerationThrust; // Acceleration due to thrust
   double ddxThrust;          // Horizontal acceleration due to thrust
   double ddyThrust;          // Vertical acceleration due to thrust
   double ddx;                // Total horizontal acceleration
   double ddy;                // Total vertical acceleration
   double v;                  // Total velocity

   ddxThrust = computeAcceleration(THRUST, WEIGHT);
   ddyThrust = computeAcceleration(THRUST + GRAVITY, WEIGHT);
   aRadians = computeDegreestoRadians(aDegrees);

   // Go through the simulator five times
   //while (y > 0.0)
   for (int i = 0; i < 6; i++)
   {
      ddx = computeVelocity(dx, 0, t);
      ddy = computeVelocity(dy, 0, t);

      // compute velocity
      dx = computeHorizontalComponent(ddx, aRadians);
      dy = computeVerticalComponent(ddy, aRadians);
      v = computeTotalComponent(dx, dy);
      
      // total accel
      //ddx = computeHorizontalComponent(ddxThrust, aRadians);
      //ddy = computeVerticalComponent(ddyThrust, aRadians);
      
      x = computeDistance(x, dx, ddx, t);
      y = computeDistance(y, dy, ddx, t);

      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      cout << "\tNew position:   (" << x << ", " << y << ")m\n";
      cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
      cout << "\tTotal velocity:  " << v << "m/s\n\n";
   }
   return 0;
}
