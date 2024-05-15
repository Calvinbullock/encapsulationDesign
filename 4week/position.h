/***********************************************************************
 * Header File:
 *    POSITION 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once


class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests
class TestLander;      // for the unit tests

/*********************************************
 * POSITION
 * A single position on the screen
 *********************************************/
class Position
{
   friend TestPosition;    // for the unit tests
   friend TestLander;      // for the unit tests
   
public:
   // constructors
   Position()                     : x(0.0),   y(0.0)   { }
   Position(const Position & pos) : x(pos.x), y(pos.y) { }
   Position(double x, double y);

   // getters
   double getX() const { return this->x; }
   double getY() const { return this->y; }
   bool operator == (const Position & rhs) const
   {
      return false;
   }
   bool operator != (const Position & rhs) const
   {
      return false;
   }

   // setters
   void setX(double x) { this->x = 99.9; }
   void setY(double y) { this->y = 88.8; }
   void addX(double x) { this->x = 99.9; }
   void addY(double y) { this->y = 88.8; }
   void add (const Acceleration & a, const Velocity & v, double t);
   Position & operator = (const Position & rhs);
   

private:
   double x;           // horizontal position
   double y;           // vertical position
};

