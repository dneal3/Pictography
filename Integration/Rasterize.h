#ifndef RASTERIZE_H
#define RASTERIZE_H

#include "Triangle.h"

class Screen
{
  public:
      // Variables
      unsigned char *buffer;
      int width, height;

      // Methods
      void SetPixel(unsigned char *buffer, int row, int column, Triangle triangle);
};

void Screen::SetPixel(unsigned char *b, int r, int c, Triangle t)
{
    b[3*(r*width + c) + 0] = t.color[0];
    b[3*(r*width + c) + 1] = t.color[1];
    b[3*(r*width + c) + 2] = t.color[2];
}


/* Image Methods */
vtkImageData * NewImage(int width, int height)
{
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(width, height, 1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
}

void WriteImage(vtkImageData *img, const char *filename)
{
   std::string full_filename = filename;
   full_filename += ".png";
   vtkPNGWriter *writer = vtkPNGWriter::New();
   writer->SetInputData(img);
   writer->SetFileName(full_filename.c_str());
   writer->Write();
   writer->Delete();
}

/* Getter Methods */
double GetCeiling(double f)
{
    return ceil(f-0.00001);
}

double GetFloor(double f)
{
    return floor(f+0.00001);
}

double GetRowMin(Triangle t)
{
    double min = *std::min_element(t.Y, t.Y+3);
    return GetCeiling(min);
}

double GetRowMax(Triangle t)
{
    double max = *std::max_element(t.Y, t.Y+3);
    return GetFloor(max);
}

double GetSlope(double x1, double x2, double y1, double y2)
{
    if (x1 == x2)
    {
         return INFINITY;
    }
    else
    {
      return ((y2 - y1) / (x2 - x1));
    }
}

double GetOffset(double y, double m, double x)
{
    if (isinf(m))
    {
        return 0.0;
    }
    else
    {
        return (y - (m * x));
    }
}

double GetEndpoint(double x, double r, double b, double m)
{
    if (isinf(m))
    {
         return x;
    }
    else
    {
         return ((r - b) / m);
    }
}

int WithinBounds(int r, int c)
{
    if (0 <= r && r < 1000 &&  0 <= c && c < 1000)
    {
         return 1;
    }
    else
    {
         return 0;
    }
}

/* Rasterize Methods */
void RasterizeGoingUpTriangle(Triangle &t, unsigned char *b, Screen s)
{
    double rowMin = GetRowMin(t);
    double rowMax = GetRowMax(t);
    t.SetSlopes();
    t.SetOffsets();
    int r;
    int c;
    double leftEnd = 0.0;
    double rightEnd = 0.0;
    for (r = rowMin; r <= rowMax; r++)
    {
        leftEnd = GetEndpoint(t.X[1], r, t.offset[0], t.slope[0]);
        rightEnd = GetEndpoint(t.X[2], r, t.offset[1], t.slope[1]);

        for (c = GetCeiling(leftEnd); c <= GetFloor(rightEnd); c++)
        {
            if (WithinBounds(r, c))
            {
                s.SetPixel(b, r, c, t);
            }
        }
    }
}

void RasterizeGoingDownTriangle(Triangle &t, unsigned char *b, Screen s)
{
    double rowMin = GetRowMin(t);
    double rowMax = GetRowMax(t);
    t.SetSlopes();
    t.SetOffsets();
    int r;
    int c;
    double leftEnd;
    double rightEnd;
    for (r = rowMin; r <= rowMax; r++)
    {
        leftEnd = GetEndpoint(t.X[1], r, t.offset[0], t.slope[0]);
        rightEnd = GetEndpoint(t.X[2], r, t.offset[1], t.slope[1]);

        for (c = GetCeiling(leftEnd); c <= GetFloor(rightEnd); c++)
        {
            if (WithinBounds(r, c))
            {
                s.SetPixel(b, r, c, t);
            }
        }
    }
}

void RasterizeArbitraryTriangle(Triangle up, Triangle down, unsigned char *b, Screen s)
{
    RasterizeGoingUpTriangle(up, b, s);
    RasterizeGoingDownTriangle(down, b, s);
}

/* Setting Indices Methods */
void SetIndicesGoingUpTriangle(Triangle original, Triangle &t)
{
    // Find the index of the top vertex
    int tIndex = 0;
    int possibilities[2] = { 1, 2 };
    if (original.Y[tIndex] < original.Y[1])
    {
        tIndex = 1;
        possibilities[0] = 0;
        possibilities[1] = 2;
    }
    if (original.Y[tIndex] < original.Y[2])
    {
        tIndex = 2;
        possibilities[0] = 0;
        possibilities[1] = 1;
    }

    // Find the indices of the bottom and middle vertices
    int bIndex = possibilities[0];
    int midIndex = possibilities[1];
    if (original.Y[bIndex] < original.Y[midIndex])
    {
        bIndex = possibilities[0];
        midIndex = possibilities[1];
    }
    else
    {
        bIndex = possibilities[1];
        midIndex = possibilities[0];
    }

    // Save the vertices as top = 0, bottom-left = 1, and bottom-right = 2
    t.X[0] = original.X[tIndex];
    t.Y[0] = original.Y[tIndex];
    if (original.Y[bIndex] == original.Y[midIndex])
    {
         t.X[1] = original.X[midIndex];
         t.Y[1] = original.Y[midIndex];
         t.X[2] = original.X[bIndex];
         t.Y[2] = original.Y[bIndex];
   }
    else
    {
         t.X[2] = original.X[midIndex];
         t.Y[2] = original.Y[midIndex];
         double y = original.Y[bIndex];
         double x = original.X[bIndex];
         double m = GetSlope(t.X[0], x, t.Y[0], y);
         double b = GetOffset(y, m, x);
         if (isinf(m))
         {
              x = original.X[bIndex];
         }
         else
         {
              x = ((original.Y[midIndex] - b) / m);
         }
         t.X[1] = x;
         t.Y[1] = original.Y[midIndex];
    }

    // Switch x values if bottom-left is bigger than bottom-right
    if (t.X[1] > t.X[2])
    {
        double original = t.X[1];
        t.X[1] = t.X[2];
        t.X[2] = original;
    }
}

void SetIndicesGoingDownTriangle(Triangle original, Triangle &t)
{
    // Find the index of the bottom vertex
    int bIndex = 0;
    int possibilities[2] = { 1, 2 };
    if (original.Y[bIndex] > original.Y[1])
    {
        bIndex = 1;
        possibilities[0] = 0;
        possibilities[1] = 2;
    }
    if (original.Y[bIndex] > original.Y[2])
    {
        bIndex = 2;
        possibilities[0] = 0;
        possibilities[1] = 1;
    }

    // Find the indices of the top and middle vertices
    int tIndex = possibilities[0];
    int midIndex = possibilities[1];
    if (original.Y[tIndex] < original.Y[midIndex])
    {
        tIndex = possibilities[0];
        midIndex = possibilities[1];
    }
    else
    {
        tIndex = possibilities[1];
        midIndex = possibilities[0];
    }

    // Save the vertices as top = 0, top-left = 1, and top-right = 2
    t.X[0] = original.X[bIndex];
    t.Y[0] = original.Y[bIndex];
    if (original.Y[tIndex] == original.Y[midIndex])
    {
         t.X[1] = original.X[tIndex];
         t.Y[1] = original.Y[tIndex];
         t.X[2] = original.X[midIndex];
         t.Y[2] = original.Y[midIndex];
    }
    else 
    {
         t.X[1] = original.X[tIndex];
         t.Y[1] = original.Y[tIndex]; 
         double y = original.Y[midIndex];
         double x = original.X[midIndex];
         double m = GetSlope(t.X[0], x, t.Y[0], y);
         double b = GetOffset(y, m, x);
         if (isinf(m))
         {
              x = original.X[midIndex];
         }
         else
         {
              x = ((original.Y[tIndex] - b) / m);
         }
         t.X[2] = x;
         t.Y[2] = original.Y[tIndex];
    }

    // Switch x values if top-left is bigger than top-right
    if (t.X[1] > t.X[2])
    {
        double original = t.X[1];
        t.X[1] = t.X[2];
        t.X[2] = original;
    }
}

void SetIndicesArbitraryTriangle(Triangle original, Triangle &up, Triangle &down)
{
   SetIndicesGoingUpTriangle(original, up);
   SetIndicesGoingDownTriangle(original, down);
}

void ScanLine(std::vector<Triangle> triangles, unsigned char *b, Screen s)
{
   int i;
   for (i = 0; i < triangles.size(); i++)
   {
       triangles[i].SetDirection();
       if (triangles[i].d == UP)
       {
           Triangle up = triangles[i];
           SetIndicesGoingUpTriangle(triangles[i], up);
           RasterizeGoingUpTriangle(up, b, s);
       }
       else if (triangles[i].d == DOWN)
       { 
           Triangle down = triangles[i];
           SetIndicesGoingDownTriangle(triangles[i], down);
           RasterizeGoingDownTriangle(down, b, s);
       }
       else
       {
           Triangle up = triangles[i];
           Triangle down = triangles[i];
           SetIndicesArbitraryTriangle(triangles[i], up, down);
           RasterizeArbitraryTriangle(up, down, b, s);
       }
   }
}

class Rasterization
{
   public:
      Rasterization(std::vector<Triangle> triangles);
};

Rasterization::Rasterization(std::vector<Triangle> triangles)
{
   vtkImageData *image = NewImage(1000, 1000);
   unsigned char *buffer = 
     (unsigned char *) image->GetScalarPointer(0,0,0);
   int npixels = 1000*1000;
   for (int i = 0 ; i < 3 * npixels; i++)
       buffer[i] = 0;

   Screen screen;
   screen.buffer = buffer;
   screen.width = 1000;
   screen.height = 1000;

   ScanLine(triangles, buffer, screen);

   WriteImage(image, "project1C");
}

#endif
