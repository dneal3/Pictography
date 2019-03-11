#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <vtkCellArray.h>
#include <vtkDataSet.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include "Triangle.h"

#define ImWidth 1000
#define ImHeight 1000
#define TEST false
#define TEST_RANGE 1
#define TEST_OFFSET 0
using std::cerr;
using std::endl;

class Screen
{
  public:
      unsigned char   *buffer;
      int width, height, totalSize;
      double *zBuffer;
    virtual ~Screen()
    {
	delete []zBuffer;
    }
    void Initialize(int imWidth, int imHeight)
    {
	this->width = imWidth;
	this->height = imHeight;
	this->totalSize = imWidth*imHeight;
	this->zBuffer = new double[totalSize];
	for(int i = 0; i < totalSize; i++)
	{
	    zBuffer[i] = -1;
	} 
    }
    void CheckBounds(double *minX,double *maxX)
    // checks if the bounds passed in are within the screen
    {
	if(*minX < 0)
	{
	    *minX = 0;
	}
	if(*maxX >= width)
	{
	    *maxX = width-1;
	}
    }
    void ColorScreen(double leftVal, double rightVal, int yVal, double zValLeft, double zValRight, double colors_d[3][2])
    //Colors the screen at the specified pixels of the scanline intersection
    {
	double leftBound = leftVal;
	double rightBound = rightVal;
	this->CheckBounds(&leftBound, &rightBound);
	int pixelIndex;
	int ctr = 0;	//use of additional counter avoids unnecessary math
	int rowOffset = yVal*width*3;
	double newZ;
	if(TEST)
	{
	    cerr << "left val: " << leftVal << endl;
	    cerr << "left bound: " << leftBound << endl;

	    cerr << "right val: " << rightVal << endl;
	    cerr << "right bound: " << rightBound << endl;

	    cerr << "red left: " << colors_d[0][0] << endl;
	    cerr << "red right: " << colors_d[0][1] << endl;
	}
	for(pixelIndex = ceil_441(leftBound)*3+rowOffset; pixelIndex <= floor_441(rightBound)*3+rowOffset; pixelIndex+=3)
	{
	    newZ = Line::InterpolateValue(leftVal, rightVal, zValLeft, zValRight, ceil_441(leftBound)+ctr);
	    if(TEST)
	    {
		cerr << "ceil(leftBound)+ctr: " << ceil_441(leftBound)+ctr << endl;
	        cerr << "r: " << Line::InterpolateValue(leftVal, rightVal, colors_d[0][0], colors_d[0][1], ceil_441(leftBound)+ctr) << endl;
	        cerr << "g: " << Line::InterpolateValue(leftVal, rightVal, colors_d[1][0], colors_d[1][1], ceil_441(leftBound)+ctr) << endl;
	        cerr << "b: " << Line::InterpolateValue(leftVal, rightVal, colors_d[2][0], colors_d[2][1], ceil_441(leftBound)+ctr) << endl;
	        cerr << std::setprecision(10) << "r converted: " << convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[0][0], colors_d[0][1], ceil_441(leftBound)+ctr)) << endl;
	        cerr << "g converted: " << convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[1][0], colors_d[1][1], ceil_441(leftBound)+ctr)) << endl;
	        cerr << "b converted: " <<  convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[2][0], colors_d[2][1], ceil_441(leftBound)+ctr)) << endl;
	    }
	    if(this->zBuffer[pixelIndex/3] < newZ)
	    {
 		this->zBuffer[pixelIndex/3] = newZ;	
	        buffer[pixelIndex  ] = convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[0][0], colors_d[0][1], ceil_441(leftBound)+ctr));
	        buffer[pixelIndex+1] = convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[1][0], colors_d[1][1], ceil_441(leftBound)+ctr));
	        buffer[pixelIndex+2] = convertColor(Line::InterpolateValue(leftVal, rightVal, colors_d[2][0], colors_d[2][1], ceil_441(leftBound)+ctr));
	    }
	    else if(TEST)
	    {
		cerr << "PIXEL NOT UPDATED" << endl;
	    }
	    ctr++;
	}
    }
    void Rasterize(Triangle toRasterize)
    // will call the appropiate RasterizeMethod for each type of triangle
    {
	switch(toRasterize.type)
	{
	    case ARBITRARY: RasterizeArbitrary(toRasterize);
		break;
	    case GOING_DOWN: RasterizeGoingTriangle(toRasterize);
		break;
	    case GOING_UP: RasterizeGoingTriangle(toRasterize);
		break;
	    case UNDEFINED: std::cerr << "triangle has type UNDEFINED?? Not rasterizing this triangle";
		break;
	    default:
		break;
	}
    }
    void RasterizeArbitrary(Triangle toRasterize)
    //Rasterizes an arbitrary triangle by calling Triangle.SplitTriangle() then calling RasterizeGoingTriangle for each split
    {
	Triangle bottomTri, topTri;
	toRasterize.SplitTriangle(&bottomTri, &topTri);
	RasterizeGoingTriangle(bottomTri);
	RasterizeGoingTriangle(topTri);
    }
    void RasterizeGoingTriangle(Triangle toRasterize)
    //Rasterizes a Going Down/Up triangle
    // Calls CheckBounds to ensure triangle boundries are valid to screen boundries
    {
	double minX, maxX, yValue, baseValue, zValue_left, zValue_right;
	double colorsOnBounds[3][2];//r,g,b each have left color, right color
	std::vector<double> slopes = toRasterize.DetermineSlopes();
	int numLines, scanLineIndex, colorIndex, colorIndex2;
	int *triangleVertices;
	Line scanLine = Line();
	Line leftIntersectLine = Line();
        Line rightIntersectLine = Line();
	Point leftIntersection;
	Point rightIntersection;
	numLines = toRasterize.NumScanLines();
	triangleVertices = toRasterize.FindPointArray();
	leftIntersectLine.point.x = toRasterize.X[triangleVertices[2]];
	leftIntersectLine.point.y = toRasterize.Y[triangleVertices[2]];
	leftIntersectLine.point.z = toRasterize.Z[triangleVertices[2]];
	leftIntersectLine.point2.x = toRasterize.X[triangleVertices[0]];
	leftIntersectLine.point2.y = toRasterize.Y[triangleVertices[0]];
	leftIntersectLine.point2.z = toRasterize.Z[triangleVertices[0]];
	leftIntersectLine.slope = slopes[0];
	rightIntersectLine.point.x = toRasterize.X[triangleVertices[2]];
	rightIntersectLine.point.y = toRasterize.Y[triangleVertices[2]];
	rightIntersectLine.point.z = toRasterize.Z[triangleVertices[2]];
	rightIntersectLine.point2.x = toRasterize.X[triangleVertices[1]];
	rightIntersectLine.point2.y = toRasterize.Y[triangleVertices[1]];
	rightIntersectLine.point2.z = toRasterize.Z[triangleVertices[1]];
	rightIntersectLine.slope = slopes[1];
	leftIntersectLine.CalculateOffset();
	rightIntersectLine.CalculateOffset();
	baseValue = ceil_441(*std::min_element(toRasterize.Y, toRasterize.Y+3));
	if(TEST)
	{
	    cerr << "\n\tNEW TRIANGLE\n" << endl;
	    toRasterize.PrintTriangle();
	    cerr << "number of scanlines is: " << numLines << endl;
	}
	for(scanLineIndex = 0; scanLineIndex <= numLines; scanLineIndex++)
	{
	    scanLine.point.y = baseValue + scanLineIndex;
	    leftIntersection = leftIntersectLine.CalculateIntersection(scanLine);
	    rightIntersection = rightIntersectLine.CalculateIntersection(scanLine);
	    minX = leftIntersection.x;
	    maxX = rightIntersection.x;
	    yValue = scanLine.point.y;
	    zValue_left = Line::InterpolateValue(leftIntersectLine.point2.y, leftIntersectLine.point.y, leftIntersectLine.point2.z, leftIntersectLine.point.z, scanLine.point.y);
	    zValue_right = Line::InterpolateValue(rightIntersectLine.point2.y, rightIntersectLine.point.y, rightIntersectLine.point2.z, rightIntersectLine.point.z, scanLine.point.y);
	    for(colorIndex2 = 0; colorIndex2 < 2; colorIndex2++)
	    {
		for(colorIndex = 0; colorIndex < 3; colorIndex++)
		{
		    colorsOnBounds[colorIndex][colorIndex2] = Line::InterpolateValue(leftIntersectLine.point2.y, leftIntersectLine.point.y, toRasterize.colors[triangleVertices[colorIndex2]][colorIndex], toRasterize.colors[triangleVertices[2]][colorIndex], scanLine.point.y);
		}
	    }

	    if(TEST)
	    {
		cerr << "*******NEW SCANLINE********" << endl;
		cerr << "scanline value: " << scanLine.point.y << endl;
		cerr << "Z values:\n\tleft: " << zValue_left <<  endl;
		cerr << "\tright: " << zValue_right <<  endl;
	        cerr << "\nBounds:\n\tleft: " << minX << "\n\tright: "<< maxX << endl;
	    }
	    if(yValue >= 0 && yValue < this->height)
	    {
	        this->ColorScreen(minX, maxX, yValue, zValue_left, zValue_right, colorsOnBounds);
	    }
	    else if(TEST)
	    {
		cerr << "scanline skipped. Y value out of range" << endl;
	    }
	}
	delete []triangleVertices;
    }
};

void RunScanRay(Screen *screen, std::vector<Triangle> trianglesToCheck)
{
    int testRange = trianglesToCheck.size();
    int triIndex;
    int testOffset = 0;//offset if I want to start at a certain triangle
    if(TEST)
    {
	testRange = TEST_RANGE;
	testOffset = TEST_OFFSET;
    }
    for(triIndex = testOffset; triIndex < testRange+testOffset; triIndex++)
    {
	trianglesToCheck[triIndex].Intialize();
	if(TEST)
	{
	    cerr << "TRIANGLE " << triIndex << endl;
	    trianglesToCheck[triIndex].PrintTriangle();
	}
	screen->Rasterize(trianglesToCheck[triIndex]);
    }
}

class ImageManager
{
	public:
	static void CreateImage(std::vector<Triangle> triangles, const char *filename)
	{
	   vtkImageData *image = NewImage(ImWidth, ImHeight);
	   unsigned char *buffer = 
	   (unsigned char *) image->GetScalarPointer(0,0,0);
	   int npixels = ImWidth*ImHeight;
	   for (int i = 0 ; i < npixels*3 ; i++)
		buffer[i] = 0;

	   Screen screen;
	   screen.buffer = buffer;
	   screen.Initialize(ImWidth, ImHeight);
	   
	   RunScanRay(&screen, triangles);

	   WriteImage(image, filename);
	}
};
#endif
