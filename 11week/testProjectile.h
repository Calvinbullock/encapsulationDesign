/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "angle.h"
#include "position.h"
#include "projectile.h"
#include "unitTest.h"
#include "velocity.h"


using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      Projectile shell = Projectile();
      
      assertEquals(shell.mass, 46.7);
      assertEquals(shell.radius, 0.077545);
      assertUnit(shell.flightPath.empty());
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
      Projectile shell = Projectile(-99, -99);
      
      assertEquals(shell.mass, -99);
      assertEquals(shell.radius, -99);
      assertUnit(shell.flightPath.empty());
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
      Projectile shell = Projectile(-99, -99);

      assertEquals(shell.mass, -99);
      assertEquals(shell.radius, -99);
      assertUnit(shell.flightPath.empty());
   }


   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/  

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      // set up
      Projectile shell = Projectile();
      Angle angle = Angle(90);
      Position pos = Position(111, 222);
      double muzVel = 100.0;
      
      // content
      shell.fire(angle, pos, muzVel);
      Projectile::PositionVelocityTime pvt = shell.flightPath.back();
      double temp = 0.0;

      assertEquals(pvt.pos.x, 111.0);
      assertEquals(pvt.pos.y, 222.0);
      assertEquals(pvt.v.dx, 100.0);
      assertEquals(pvt.v.dy, 0.0);
      assertEquals(pvt.t, 1);
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      // set up
      Projectile shell = Projectile();
      Angle angle = Angle(-90);
      Position pos = Position(111, 222);
      double muzVel = 100.0;

      // content
      shell.fire(angle, pos, muzVel);
      Projectile::PositionVelocityTime pvt = shell.flightPath.back();

      assertEquals(pvt.pos.x, 111);
      assertEquals(pvt.pos.y, 222);
      assertEquals(pvt.v.dx, -100);
      assertEquals(pvt.v.dy, 0);
      assertEquals(pvt.t, 1);
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      // set up
      Projectile shell = Projectile();
      Angle angle = Angle(0);
      Position pos = Position(111, 222);
      double muzVel = 100.0;

      // content
      shell.fire(angle, pos, muzVel);
      Projectile::PositionVelocityTime pvt = shell.flightPath.back();

      assertEquals(pvt.pos.x, 111);
      assertEquals(pvt.pos.y, 222);
      assertEquals(pvt.v.dx, 0.0);
      assertEquals(pvt.v.dy, 100.0);
      assertEquals(pvt.t, 1);
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/ 

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 0.0;
      pvt.v.dy = 0.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      //p.advance(101.0); // TODO 
      // verify
      assertUnit(p.flightPath.size() == 2);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 100.0); // 100 + 0*1
         assertEquals(p.flightPath.back().pos.y, 195.0968); // 200 + 0*1 + .5(-9.806)*1*1
         assertEquals(p.flightPath.back().v.dx, 0.0);   // 0 + 0*1
         assertEquals(p.flightPath.back().v.dy, -9.8);   // 0 + (-9.8064)*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();

      // WARN 
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = 0.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      //p.advance(101.0); // TODO 
      // verify
      assertUnit(p.flightPath.size() == 2);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9756); // 100 + 50*1 + .5(-0.0487)*1*1
         assertEquals(p.flightPath.back().pos.y, 195.0968); // 200 + 0*1  + .5(-9.8064)*1*1
         assertEquals(p.flightPath.back().v.dx, 49.9513);   // 50 + (-0.0487)*1
         assertEquals(p.flightPath.back().v.dy, -9.8064);   // 0  + (-9.8064)*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();

      // WARN 
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 0.0;
      pvt.v.dy = 100.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      //p.advance(101.0); // TODO 
      // verify
      assertUnit(p.flightPath.size() == 2);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 100.0);    // 0   + 0*1   + .5(0)*1*1*/
         assertEquals(p.flightPath.back().pos.y, 294.9021); // 200 + 100*1 + .5(-9.8064-.3893)*1*1
         assertEquals(p.flightPath.back().v.dx, 0.0);       // 0   + 0*1*/
         assertEquals(p.flightPath.back().v.dy, 89.8042);   // 100 + (-9.8064-.3893)
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();

      // WARN 
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = 40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      //p.advance(101.0); // TODO 
      // verify
      assertUnit(p.flightPath.size() == 2);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9600); // 100 + 50*1 + .5(-0.0799)*1*1
         assertEquals(p.flightPath.back().pos.y, 235.0648); // 200 + 40*1 + .5(-9.8064-0.0638)*1*1
         assertEquals(p.flightPath.back().v.dx, 49.9201);   // 50 + (-0.0799)*1
         assertEquals(p.flightPath.back().v.dy, 30.1297);   // 30.1297  = 40 + (-9.8064-0.0638)*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();

      // WARN 
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {  // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9601); // 100 + 50*1 + .5(-0.0799)*1*1
         assertEquals(p.flightPath.back().pos.y, 155.1287); // 200 +-40*1 + .5(-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().v.dx, 49.9201);   // 50 + (-0.0799)*1
         assertEquals(p.flightPath.back().v.dy, -49.7425);  //-40 + (-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};

