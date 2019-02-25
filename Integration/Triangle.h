#ifndef TRIANGLE_H
#define TRIANGLE_H

enum direction { UP, DOWN, RIGHT, ARBITRARY };

double GetSlope(double x1, double x2, double y1, double y2);
double GetOffset(double y, double m, double x);

class Triangle
{
  public:
      // Variables
      double X[3];
      double Y[3];
      unsigned char color[3];
      direction d;
      double slope[2];
      double offset[2];

      // Methods
      void SetSlopes();
      void SetOffsets();
      void SetDirection();
};

void Triangle::SetSlopes()
{
    slope[0] = GetSlope(X[0], X[1], Y[0], Y[1]);
    slope[1] = GetSlope(X[0], X[2], Y[0], Y[2]);
}

void Triangle::SetOffsets()
{
    offset[0] = GetOffset(Y[1], slope[0], X[1]);
    offset[1] = GetOffset(Y[2], slope[1], X[2]);
}

void Triangle::SetDirection()
{
     if ((Y[0] == Y[1] && Y[1] < Y[2]) ||
         (Y[0] == Y[2] && Y[2] < Y[1]) ||
         (Y[1] == Y[2] && Y[2] < Y[0]))
     {
          d = UP;
     }
     else if ((Y[0] == Y[1] && Y[2] < Y[1]) ||
              (Y[0] == Y[2] && Y[1] < Y[2]) ||
              (Y[1] == Y[2] && Y[0] < Y[2]))
     {
          d = DOWN;
     }
     else if ((X[0] == X[1] && X[1] < X[2]) ||
              (X[0] == X[2] && X[2] < X[1]) ||
              (X[1] == X[2] && X[2] < X[0]))
     {
          d = RIGHT;
     }
     else
     {
          d = ARBITRARY;
     }
}

#endif
