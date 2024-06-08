#include "position.h"
#include <iostream>
using namespace std;

/* ********************************************
 * Velocity class
 *    handles velocity in the simulator
 * ***************************************** */
class Velocity
{
public:
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   double getDX() const { return dx; }
   double getDY() const { return dy; }

   void setDX(double newDX) { dx = newDX; }
   void setDY(double newDY) { dy = newDY; }

   void set(double angle, double vel)
   {
      dx = sin(angle) * vel;
      dy = cos(angle) * vel;
   }

private:
   double dx;
   double dy;
};

/*
 * TODO   header CHANGE NAME
 * */
void calcAcceleration(Velocity *vel, double grav, double time)
{
   vel->setDY(vel->getDY() + (grav * time));
}

/* ********************************************
 * CHANGE IN POSITION
 *    Calculates the change in position - inertia
 * ***************************************** */
void changeInPostion(Position *pos, Velocity *vel, double time, double grav)
{
   pos->setMetersX(pos->getMetersX() + vel->getDX() * time + (.5 * 0 * (time * time)));
   pos->setMetersY(pos->getMetersY() + vel->getDY() * time + (.5 * grav * (time * time)));
}

/* ********************************************
 * TODO  header
 * ***************************************** */
double toRadians(double degree)
{
   return (degree * M_PI) / 180;
}

/* ********************************************
 * TODO  main header
 * ***************************************** */
int main(int argc, char *argv[])
{
   Position pos;
   double time = 0.0;
   double timeInterval = 0.01;
   double gravity = -9.8;
   double angle = toRadians(75);
   double initVel = 827.0;
   Velocity vel = Velocity();

   vel.set(angle, initVel);

   while (pos.getMetersY() > -1)
   {
      time += timeInterval;
      calcAcceleration(&vel, gravity, timeInterval);
      changeInPostion(&pos, &vel, timeInterval, gravity);

      cout << "Distance:  " << pos.getMetersX() << ",  Altitude: " << pos.getMetersY() << ", HangTime:  " << time << endl;
   } 

   return 0;
}
