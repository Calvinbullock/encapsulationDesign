
/***********************************************************************
 * Source File:
 *    THRUST
 * Author:
 *    Calvin, Bullock
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#include "thrust.h"

 /***************************************************************
  * ROTATION
  * return the rate of rotation
  ***************************************************************/
double Thrust::rotation() const
{
   if (clockwise && counterClockwise)
   {
      return 0.0;
   }
   else if (counterClockwise)
   {
      return -0.1;
   }
   else if (clockwise)
   {
      return 0.1;
   }
   return 0.0;
}

 /***************************************************************
  * SET
  * Set the engines on off 
  ***************************************************************/
void Thrust::set(const Interface *pUI)
{
   if (pUI->isDown())
   {
      mainEngine = true;
   }
   else
   {
      mainEngine = false;
   }

   if (pUI->isLeft())
   {
      clockwise = true;
   }
   else
   {
      clockwise = false;
   }

   if (pUI->isRight())
   {
      counterClockwise = true;
   }
   else
   {
      counterClockwise = false;
   }
}
