/*************************************************************
 * 1. Name:
 *      Calvin Bullock, Hyrum Bullock
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      TODO -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      TODO -total time in hours: reading the assignment, submitting, and writing code-
 *****************************************************************/

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
double computeDistance(double s, double v, double a, double t)
{
   double newPos = s + v * t + .5 * a * (t * t);
   return newPos;
}

/***************************************************
 * TEST COMPUTE DISTANCE
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
double computeAcceleration(double f, double m)
{
   // to find acceleration we need to change the
   // formula to accel = force/mass
   double a = f / m;
   return a;
}

/**************************************************
 * TEST COMPUTE ACCELERATION
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
double computeVelocity(double v, double a, double t)
{
   double newVel = v + a * t;
   return newVel;
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
double computeVerticalComponent(double total, double a)
{
   double y = cos(a) * total;
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
double computeHorizontalComponent(double total, double a)
{
   double x;
   x = sin(a) * total;
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
double computeTotalComponent(double x, double y)
{
   double total = sqrt((x * x) + (y * y));
   return total;
}

/**************************************************
 * TEST RADIANS FROM DEGEES
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
double computeDegreestoRadians(double d)
{
   double r = (2.0 * M_PI) * (d / 360.0);
   return r;
}

/**************************************************
 * TEST RADIANS FROM DEGEES
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

   cout << text;
   cin >> input;

   cin.ignore(); // clear input buffer
   return input;
}

/**************************************************
 * PHYSICS ENGINE
 * Runs all physics calculations
 *  and outputs to the console. 
 **************************************************/
void physicsEngine(double dx, double dy, double y)
{
   //inital values
   double x = 0.0;
   double t = 1.0;

   double aDegrees;
   double aRadians;           // Angle in radians
   double accelerationThrust; // Acceleration due to thrust
   double ddxThrust;          // Horizontal acceleration due to thrust
   double ddyThrust;          // Vertical acceleration due to thrust
   double ddx;                // Total horizontal acceleration
   double ddy;                // Total vertical acceleration
   double v;                  // Total velocity

   while (y > 0.0)
   {
      cout << "What is the new angle of the LM where 0 is up (degrees)? ";
      cin  >> aDegrees;
      cout << endl;

      accelerationThrust = computeAcceleration(THRUST, WEIGHT);
      aRadians = computeDegreestoRadians(aDegrees);

      ddy = computeVerticalComponent(accelerationThrust, aRadians);
      ddx = computeHorizontalComponent(accelerationThrust, aRadians);

      ddy += GRAVITY;

      // Go through the simulator until the lander touches ground
      for (int sec = 1; sec < 6; sec++)
      {
         x = computeDistance(x, dx, ddx, t);
         y = computeDistance(y, dy, ddy, t);

         dx = computeVelocity(dx, ddx, t);
         dy = computeVelocity(dy, ddy, t);

         v = computeTotalComponent(dx, dy);
         
         // cout round too two decimals
         cout.setf(ios::fixed | ios::showpoint);
         cout.precision(2);

         // Output
         cout << sec << "s - "
                     << "x,y:(" << x << ", " << y << ")m  "
                     << "dx,dy:(" << dx << ", " << dy << ")m/s  "
                     << "speed:" << v << "m/s  angle:"
                     << aDegrees << "deg"
                     << endl;
      }
      cout << endl;
   }
   // cout << "\ntouchdown!!!" << endl;
}

/**************************************************
 * TEST PHYSICS ENGINE 
 **************************************************/
void testPhysicsEngine(){
   cout << "\n---------TEST 1 HARD LANDING---------" << endl;
   physicsEngine( 10.53, -13.959, 106.08);
   cout << "\n---------TEST 2 CRASH---------" << endl;
   physicsEngine( -35.0, -15.0, 207.77);
   cout << "\n---------TEST 3 ARMSTRONG---------" << endl;
   physicsEngine(10.0, -10.0, 62.7);
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

   //testPhysicsEngine();

   cout << "testing Completed\n"
        << endl;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
   // testRunner();
   testPhysicsEngine();
   
   // double dy = prompt("What is your vertical velocity (m/s)? ");
   // double dx = prompt("What is your horizontal velocity (m/s)? ");
   // double y = prompt("What is your altitude (m)? ");
   
   //test values
   double dx = -10.0;
   double dy = -9;
   double y = 100;
    
   //physicsEngine(dx, dy, y);
   
   return 0;
}
