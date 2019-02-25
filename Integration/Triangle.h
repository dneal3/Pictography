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

#endif
