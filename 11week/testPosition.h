/***********************************************************************
 * Header File:
 *    TEST POSITION
 * Author:
 *    Calvin, Hyrum Bullock
 * Summary:
 *    Unit tests for the Position class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <iostream>

using namespace std;

/*******************************
 * TEST Position
 * A friend class for Position which contains the Position unit tests
 ********************************/
class TestPosition : public UnitTest
{
public:
   void run()
   {
      // Ticket 7: Meters
      construct_default();
      construct_nonDefault();
      construct_copy();
      assign();
      setMetersX();
      setMetersY();
      getMetersX();
      getMetersY();

      // Ticket 8: Pixels and Zoom
      setZoom_member();
      setZoom_anotherVariable();
      getZoom_member();
      getZoom_anotherVariable();
      setPixelsX_noZoom();
      setPixelsX_zoom();
      setPixelsY_noZoom();
      setPixelsY_zoom();
      getPixelsX_noZoom();
      getPixelsX_zoom();
      getPixelsY_noZoom();
      getPixelsY_zoom();

      // Ticket 9: Add
      addMetersX();
      addMetersY();
      addPixelsX_noZoom();
      addPixelsX_zoom();
      addPixelsY_noZoom();
      addPixelsY_zoom();
      add_stationary();
      add_moving();
      add_movingLonger();
      add_fromStop();
      add_fromStopLonger();
      add_complex();
      
      report("Position");
   }
   
private:


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  pos=(0, 0)
    *********************************************/
   void construct_default()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      // exercise
      Position pos;
      // verify
      assertEquals(pos.x, 0.0);
      assertEquals(pos.y, 0.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    NON-DEFAULT CONSTRUCTOR
    * input:   x=120.0, y=360.0
    * output:  pos=(120.0, 360.0)
    *********************************************/
   void construct_nonDefault()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      double x = 120.0;
      double y = 360.0;
      // exercise
      Position pos(x, y);
      // verify
      assertEquals(pos.x, 120.0);
      assertEquals(pos.y, 360.0);
      assertEquals(pos.metersFromPixels, 99.9);
      assertEquals(x, 120.0);
      assertEquals(y, 360.0);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    COPY CONSTRUCTOR
    * input:   posRHS = (1234.5, 6789.0)
    * output:  pos = (1234.5, 6789.0)
    *********************************************/
   void construct_copy()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position posRHS;
      posRHS.x = 1234.5;
      posRHS.y = 6789.0;
      // exercise
      Position pos(posRHS);
      // verify
      assertEquals(posRHS.x, 1234.5);
      assertEquals(posRHS.y, 6789.0);
      assertEquals(posRHS.metersFromPixels, 99.9);
      assertEquals(pos.x, 1234.5);
      assertEquals(pos.y, 6789.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ASSIGNMENT OPERATOR
    * input:   posLHS=(-99.9, -88.8)  posRHS=(24.68, -13,57)
    * output:  posLHS=(24.68, -13,57)
    *********************************************/
   void assign()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position posLHS;
      posLHS.x = -99.9;
      posLHS.y = -88.8;
      Position posRHS;
      posRHS.x =  24.68;
      posRHS.y = -13.57;
      // exercise
      posLHS = posRHS;
      // verify
      assertEquals(posRHS.x, 24.68);
      assertEquals(posRHS.y, -13.57);
      assertEquals(posRHS.metersFromPixels, 99.9);
      assertEquals(posLHS.x, 24.68);
      assertEquals(posLHS.y, -13.57);
      assertEquals(posLHS.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/
   
   /*********************************************
    * name:    GET ZOOM : member variable
    * input:   pos.metersFromPixels=123.4
    * output:  zoom=123.4
    *          Position::metersFromPixels=123.4
    *********************************************/
   void getZoom_member()
   {  // setup
      double zoomLV = 123.4;

      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = zoomLV;
      Position pos;
      // exercise
      double zoom = pos.getZoom();
      // verify
      assertEquals(zoom, zoomLV);
      assertEquals(pos.metersFromPixels, zoomLV);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }
   
   /*********************************************
    * name:    GET ZOOM : another variable
    * input:   pos1.metersFromPixels=99.9  (set this first)
    *          pos2.metersFromPixels=123.4 (set this second)
    * output:  zoom=123.4
    *          pos1.metersFromPixels=123.4 (last assignment sticks)
    *          pos2.metersFromPixels=123.4
    *********************************************/
   void getZoom_anotherVariable()
   {  // setup
      double zoomLV = 123.4;

      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = zoomLV;
      Position pos;
      Position pos2;
      pos.metersFromPixels = 99.9;
      pos2.metersFromPixels = zoomLV;

      // exercise
      double zoom = pos.getZoom();
      double zoom2 = pos2.getZoom();
      // verify
      assertEquals(zoom, zoomLV);
      assertEquals(zoom2, zoomLV);
      assertEquals(pos.metersFromPixels, zoomLV);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }


   /*********************************************
    * name:    GET METERS X
    * input:   pos=(4500.0, 2500.0)   Store meters internally
    * output:  x=4500.0
    *********************************************/
   void getMetersX()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 4500.0;
      pos.y = 2500.0;
      // exercise
      double x = pos.getMetersX();
      // verify
      assertEquals(x, 4500.0);
      assertEquals(pos.x, 4500.0);
      assertEquals(pos.y, 2500.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET METERS Y
    * input:   pos=(4500.0, 2500.0)
    * output:  y=2500.0
    *********************************************/
   void getMetersY()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 4500.0;
      pos.y = 2500.0;
      // exercise
      double y = pos.getMetersY();
      // verify
      assertEquals(pos.x, 4500.0);
      assertEquals(pos.y, 2500.0);
      assertEquals(pos.metersFromPixels, 99.9);
      assertEquals(y, 2500.0);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET METERS X NO ZOOM
    * input:   pos=(123.4, 567.8) metersFromPixels=1
    * output:  x=123.4
    *********************************************/
   void getPixelsX_noZoom()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 123.4;
      pos.y = 567.8;
      pos.metersFromPixels = 1;

      // exercise
      double pixelX = pos.getPixelsX();

      // verify
      assertEquals(pos.x, 123.4);
      assertEquals(pixelX, 123.4);

      // teardown
      Position::metersFromPixels = metersFromPixels;
   }
   
   /*********************************************
    * name:    GET PIXELS X ZOOM
    *          pixels = meters / metersFromPixels
    * input:   pos=(123.4, 567.8) metersFromPixels=100
    * output:  x=1.234
    *********************************************/
   void getPixelsX_zoom()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position pos;
      pos.x = 123.4;
      pos.y = 567.8;
      pos.metersFromPixels = 100.0;

      // exercise
      double pixelX = pos.getPixelsX();

      // verify
      assertEquals(pixelX, 1.234);

      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET PIXELS Y NO ZOOM
    * input:   pos=(123.4, 567.8) metersFromPixels=1
    * output:  y=567.8
    *********************************************/
   void getPixelsY_noZoom()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position pos;
      pos.x = 123.4;
      pos.y = 567.8;
      pos.metersFromPixels = 1.0;

      // exercise
      double pixelY = pos.getPixelsY();

      // verify
      assertEquals(pixelY, 567.8);

      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET PIXELS Y ZOOM
    * input:   pos=(123.4, 567.8) metersFromPixels=100
    * output:  y=5.678
    *********************************************/
   void getPixelsY_zoom()
   {
      // setup
      double metersFromPixels = Position::metersFromPixels;
      Position pos;
      pos.x = 123.4;
      pos.y = 567.8;
      pos.metersFromPixels = 100.0;

      // exercise
      double pixelY = pos.getPixelsY();

      // verify
      assertEquals(pixelY, 5.678);

      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/
   
   /*********************************************
    * name:    SET METERS X
    *          We store pixels internally
    * input:   pos=(999.9, 888.8) x = 123.4
    * output:  pos=(123.4, 888.8)
    *********************************************/
   void setMetersX()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setMetersX(123.4);
      // verify
      assertEquals(pos.x, 123.4);
      assertEquals(pos.y, 888.8);
      assertEquals(pos.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET METERS Y 
    * input:   pos=(999.9, 888.8) y = 123.4
    * output:  pos=(999.9, 123.4)
    *********************************************/
   void setMetersY()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setMetersY(123.4);
      // verify
      assertEquals(pos.x, 999.9);
      assertEquals(pos.y, 123.4);
      assertEquals(pos.metersFromPixels, 99.9);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    SET PIXELS X NO ZOOM
    *          When meterFromPixels == 1, pixels and meters are the same
    * input:   pos=(999.9, 888.8) x=123.4 meterFromPixels=1
    * output:  pos=(123.4, 888.8)
    *********************************************/
   void setPixelsX_noZoom()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 1;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setPixelsX(123.4);
      // verify
      assertEquals(pos.x, 123.4);
      assertEquals(pos.y, 888.8);
      assertEquals(pos.metersFromPixels, 1);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    SET PIXELS X ZOOM
    *          meters = pixels * metersFromPixels
    * input:   pos=(999.9, 888.8) x=123.4 meterFromPixels=100
    * output:  pos=(12340.0, 888.8)
    *********************************************/
   void setPixelsX_zoom()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 100;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setPixelsX(123.4);
      // verify
      assertEquals(pos.x, 12340.0);
      assertEquals(pos.y, 888.8);
      assertEquals(pos.metersFromPixels, 100);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }
   
   /*********************************************
    * name:    SET PIXELS Y NO ZOOM
    * input:   pos=(999.9, 888.8) y=123.4 meterFromPixels=1
    * output:  pos=(999.9, 123.4)
    *********************************************/
   void setPixelsY_noZoom()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 1;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setPixelsY(123.4);
      // verify
      assertEquals(pos.x, 999.9);
      assertEquals(pos.y, 123.4);
      assertEquals(pos.metersFromPixels, 1);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    SET PIXELS Y ZOOM
    * input:   pos=(999.9, 888.8) y=123.4 meterFromPixels=100
    * output:  pos=(999.9, 12340.0)
    *********************************************/
   void setPixelsY_zoom()
   {  // setup
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 100;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // exercise
      pos.setPixelsY(123.4);
      // verify
      assertEquals(pos.x, 999.9);
      assertEquals(pos.y, 12340.0);
      assertEquals(pos.metersFromPixels, 100);
      // teardown
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ADD METERS X
    * input:   pos=(4500,2500) x=123.4 
    * output:  pos=(4623.4,2500)
    *********************************************/
   void addMetersX()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;

      // exercise
      double newXPos = pos.addMetersX(123.4);

      // verify
      assertEquals(newXPos, 4623.4 );
      assertEquals(pos.x, 4623.4 );
      assertEquals(pos.y, 2500);
   }  // teardown

   /*********************************************
    * name:    ADD METERS Y
    * input:   pos=(4500,2500) y=123.4
    * output:  pos=(4500,2623.4)
    *********************************************/
   void addMetersY()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;

      // exercise
      double newYPos = pos.addMetersY(123.4);

      // verify
      assertEquals(newYPos, 2623.4 );
      assertEquals(pos.x, 4500 );
      assertEquals(pos.y, 2623.4);
   }  // teardown


   /*********************************************
    * name:    ADD PIXELS X ZERO ZOOM
    * input:   pos=(4500,2500) x=3pixels meterFromPixels=1.0
    * output:  pos=(4503,2500)
    *********************************************/
   void addPixelsX_noZoom()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;
      pos.metersFromPixels = 1.0;

      // exercise
      double newXPos = pos.addPixelsX(3);

      // verify
      assertEquals(newXPos, 4503.0 );
      assertEquals(pos.x, 4503.0 );
      assertEquals(pos.y, 2500);
   }  // teardown

   /*********************************************
    * name:    ADD PIXELS X ZOOM
    * input:   pos=(4500,2500) x=3pixels meterFromPixels=50.0
    * output:  pos=(4650,2500)
    *********************************************/
   void addPixelsX_zoom()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;
      pos.metersFromPixels = 50.0;

      // exercise
      double newXPos = pos.addPixelsX(3);

      // verify
      assertEquals(newXPos, 4650.0 );
      assertEquals(pos.x, 4650.0 );
      assertEquals(pos.y, 2500);
   }  // teardown

   /*********************************************
    * name:    ADD PIXELS Y ZERO ZOOM
    * input:   pos=(4500,2500) y=3pixels meterFromPixels=1.0
    * output:  pos=(4500,2503)
    *********************************************/
   void addPixelsY_noZoom()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;
      pos.metersFromPixels = 1.0;

      // exercise
      double newYPos = pos.addPixelsY(3);

      // verify
      assertEquals(newYPos, 2503.0 );
      assertEquals(pos.x, 4500.0 );
      assertEquals(pos.y, 2503.0);
   }  // teardown

   /*********************************************
    * name:    ADD PIXELS Y ZOOM
    * input:   pos=(4500,2500) y=3pixels meterFromPixels=50.0
    * output:  pos=(4500,2650)
    *********************************************/
   void addPixelsY_zoom()
   {  // setup
      Position pos;
      pos.x = 4500;
      pos.y = 2500;
      pos.metersFromPixels = 50.0;

      // exercise
      double newYPos = pos.addPixelsY(3);

      // verify
      assertEquals(newYPos, 2650.0 );
      assertEquals(pos.x, 4500.0 );
      assertEquals(pos.y, 2650.0);
   }  // teardown

   /*********************************************
    * name:    SET ZOOM : member variable
    * input:   pos.metersFromPixels = 99.9, setZoom(123.4)
    * output:  pos.metersFromPixels=123.4
    *          Position::metersFromPixels=123.4
    *********************************************/
   void setZoom_member()
   {  // setup
      double ans = 123.4;
      Position pos;
      pos.metersFromPixels = 99.0;

      // exercise
      pos.setZoom(ans);

      // verify
      assertUnit(pos.metersFromPixels == ans);
      assertUnit(Position::metersFromPixels == ans);
   }  // teardown

   /*********************************************
    * name:    SET ZOOM : another variable
    * input:   pos1.metersFromPixels=99.9
    *          pos2.metersFromPixels=88.9
    *          pos2.setZoom(123.4)
    * output:  pos1.metersFromPixels=123.4
    *          pos2.metersFromPixels=123.4
    *          Position::metersFromPixels=123.4
    *********************************************/
   void setZoom_anotherVariable()
   {  // setup
      double ans = 123.4;
      Position pos1;
      pos1.metersFromPixels = 99.0;

      Position pos2;
      pos2.metersFromPixels = 88.9;

      // exercise
      pos1.setZoom(ans);
      pos2.setZoom(ans);

      // verify
      assertUnit(pos1.metersFromPixels == ans);
      assertUnit(pos2.metersFromPixels == ans);
      assertUnit(Position::metersFromPixels == ans);
   }  // teardown

   /*********************************************
    * name:    ADD update position when not moving and not accelerating
    * input:   pos=(11.1,22.2) acc=(0,0), vel=(0,0) t=1
    * output:  pos=(11.1,22.2)
    *********************************************/
   void add_stationary()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;
      Acceleration acc;
      acc.ddx = 0.0;
      acc.ddy = 0.0;
      double time(1.0);

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  11.1); // 12.5 = 11.1 + 0.5*2 + 1/2 .2 2^2
      assertEquals(pos.y,  22.2); // 23.6 = 22.2 + 0.4*2 + 1/2 .3 2^2

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ADD update position when moving but not accelerating
    * input:   pos=(11.1,22.2) acc=(0,0), vel=(0.5,0.4) t=1
    * output:  pos.x = 11.6 = 11.1 + 0.5*1
    *          pos.y = 22.6 = 22.2 + 0.4*1
    *********************************************/
   void add_moving()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.5;
      vel.dy = 0.4;
      Acceleration acc;
      acc.ddx = 0.0;
      acc.ddy = 0.0;
      double time = 1.0;

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  11.6);
      assertEquals(pos.y,  22.6);
      assertEquals(vel.dx,  0.5);
      assertEquals(vel.dy,  0.4);
      assertEquals(acc.ddx, 0.0);
      assertEquals(acc.ddy, 0.0);
      assertEquals(time,    1.0);

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ADD update position when moving longer (2 seconds) but not accelerating
    * input:   pos=(11.1,22.2) acc=(0,0), vel=(0.5,0.4) t=2
    * output:  pos.x = 12.1 = 11.1 + 0.5*2
    *          pos.y = 23.0 = 22.2 + 0.4*2
    *********************************************/
   void add_movingLonger()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.5;
      vel.dy = 0.4;
      Acceleration acc;
      acc.ddx = 0.0;
      acc.ddy = 0.0;
      double time = 2.0;

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  12.1);
      assertEquals(pos.y,  23.0);
      assertEquals(vel.dx,  0.5);
      assertEquals(vel.dy,  0.4);
      assertEquals(acc.ddx, 0.0);
      assertEquals(acc.ddy, 0.0);
      assertEquals(time,    2.0);

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ADD update position when accelerating but not moving
    * input:   pos=(11.1,22.2) acc=(0.2,0.3), vel=(0,0) t=1
    * output:  pos.x = 11.20 = 11.1 + 1/2 .2 1^2
    *          pos.y = 22.35 = 22.2 + 1/2 .3 1^2
    *********************************************/
   void add_fromStop()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;
      Acceleration acc;
      acc.ddx = 0.2;
      acc.ddy = 0.3;
      double time = 1.0;

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  11.20);
      assertEquals(pos.y,  22.35);
      assertEquals(vel.dx,  0.0);
      assertEquals(vel.dy,  0.0);
      assertEquals(acc.ddx, 0.2);
      assertEquals(acc.ddy, 0.3);
      assertEquals(time,    1.0);

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ADD update position when accelerating longer (2 seconds)
    * input:   pos=(11.1,22.2) acc=(0.2,0.3), vel=(0,0) t=2
    * output:  pos.x = 11.5 = 11.1 + 1/2 .2 2^2
    *          pos.y = 22.8 = 22.2 + 1/2 .3 2^2
    *********************************************/
   void add_fromStopLonger()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;
      Acceleration acc;
      acc.ddx = 0.2;
      acc.ddy = 0.3;
      double time = 2.0;

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  11.5);
      assertEquals(pos.y,  22.8);
      assertEquals(vel.dx,  0.0);
      assertEquals(vel.dy,  0.0);
      assertEquals(acc.ddx, 0.2);
      assertEquals(acc.ddy, 0.3);
      assertEquals(time,    2.0);

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }
   
   /*********************************************
    * name:    ADD update position when both moving and accelerating for 2 seconds
    * input:   pos=(11.1,22.2) acc=(0.2,0.3), vel=(0.5,0.4) t=2
    * output:  pos.x = 12.5 = 11.1 + 0.5*2 + 1/2 .2 2^2
    *          pos.y = 23.6 = 22.2 + 0.4*2 + 1/2 .3 2^2
    *********************************************/
   // update position when both moving and accelerating for 2 seconds
   void add_complex()
   {  // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 11.1;
      pos.y = 22.2;
      Velocity vel;
      vel.dx = 0.5;
      vel.dy = 0.4;
      Acceleration acc;
      acc.ddx = 0.2;
      acc.ddy = 0.3;
      double time(2.0);

      // EXERCISE
      pos.add(acc, vel, time);

      // VERIFY
      assertEquals(pos.x,  12.5); // 12.5 = 11.1 + 0.5*2 + 1/2 .2 2^2
      assertEquals(pos.y,  23.6); // 23.6 = 22.2 + 0.4*2 + 1/2 .3 2^2
      assertEquals(vel.dx,  0.5);
      assertEquals(vel.dy,  0.4);
      assertEquals(acc.ddx, 0.2);
      assertEquals(acc.ddy, 0.3);
      assertEquals(time,    2.0);

      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

};