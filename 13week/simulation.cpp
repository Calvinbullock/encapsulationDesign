/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h" // for SIMULATION

/*********************************************
 * RESET SIM
 * Resets the sim
 *********************************************/
void Simulator::resetSim()
{
   shell.reset();
   simTime = 0;
   ground.reset(howitzer.getPosition());

   howitzer.generatePosition(posUpperRight);
   howitzer.setPosition(howitzer.getPosition());
}

/*********************************************
 * GET STAT DISPLAY
 * Display projectile and howitzer stats
 *********************************************/
std::string Simulator::getStatDisplay()
{
   Angle elevation = howitzer.getElevation();
   Position shellPos = shell.getPojectilePosition();
   double shellSpeed = shell.getPojectileSpeed();

   if (shell.getIsFlying())
   {
      return "Distance: " + truncateString(shellPos.getMetersX(), 1) +
             " m/sec\nHeight:    " + truncateString(shellPos.getMetersY(), 1) +
             " m/sec\nSpeed:    " + truncateString(shellSpeed, 1) + " m/sec";
   }
   return "Elevation: " + truncateString(elevation.getDegrees(), 1) +
          " degrees";
}

/*********************************************
 * FIRE PROJECTILE
 * creates then sets initial projectile values
 *********************************************/
void Simulator::fireProjectile(ogstream &gout)
{
   Position pos = howitzer.getPosition();
   Angle a = howitzer.getElevation();

   // pos.setPixelsX(pos.getPixelsX() + 5);
   // pos.setMetersY(pos.getMetersY() + .3);
   for (double age = 0; age <= 3; age += .1)
   {
      howitzer.draw(gout, age);
   }

   shell.fire(howitzer.getElevation(), pos, howitzer.getMuzzleVelocity());
}

/*********************************************
 * ADVANCE PROJECTILE
 * wrapper to calc next projectile position
 *********************************************/
void Simulator::advanceProjectile()
{
   simTime += SIMTIME;
   if (shell.getIsFlying())
      shell.advance(simTime);

   // check if shell has impacted ground
   Position pos = shell.getPojectilePosition();
   double groundY = ground.getElevationMeters(pos);
    if (!shell.checkImpact(groundY))
      resetProjectile();

}

/*********************************************
 * HOWITZER CONTROLS
 * wrapper to calc next projectile position
 *********************************************/
void Simulator::howizerControls(const Interface *pUI)
{
   if (pUI->isRight())
      howitzer.rotate(0.02);

   if (pUI->isLeft())
      howitzer.rotate(-0.02);

   if (pUI->isDown())
      howitzer.raise(-0.001);

   if (pUI->isUp())
      howitzer.raise(0.001);
}

/*********************************************
 * TRUNCATE STRING
 * converts doubles into a string and knocks
 *    off everything after decimal precision
 *********************************************/
std::string Simulator::truncateString(double value, int precision)
{
   std::string num = std::to_string(value);

   for (int i = 0; i < num.length(); i++)
   {
      if (num[i] == '.')
      {
         i += precision + 1;
         return num.erase(i);
      }
   }

   return num;
}
