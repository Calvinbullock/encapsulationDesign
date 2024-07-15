
/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Angle
{

public:
   Angle()
   {
   }

private:
   double angle; // degrees
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Velocity
{

public:
   Velocity(double vel) : vel(vel) {}
   double getVel() { return vel; }

private:
   double vel;
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Acceleration
{

public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

   void set(double angle, double vel)
   {
      ddx = sin(angle) * vel;
      ddy = cos(angle) * vel;
   }

private:
   double ddx;
   double ddy;
};

/* ********************************************
 * TODO  fill in class header
 * ***************************************** */
class Shell
{

public:
private:
   Angle angle;
   Acceleration accel;
   Position pos;
};


