#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#define EPSILON 0.00001
using std::cerr;
using std::endl;
enum VertexLocations{TOP = 0, BOTTOM, TOP_RIGHT, TOP_LEFT, BOTTOM_RIGHT, BOTTOM_LEFT, RIGHT, LEFT};
enum TriangleType{GOING_UP = 0, GOING_DOWN, ARBITRARY, UNDEFINED};
void printVertexLocs(std::vector<VertexLocations> locsToPrint)
{
    std::vector<VertexLocations>::iterator iter;
    cout << "Locations for this vector are: \n" << endl;
    for(iter = locsToPrint.begin(); iter < locsToPrint.end(); iter++)
    {
	switch(*iter)
	{
	    case TOP: cout << "\tTOP\n" << endl;
		break;
	    case BOTTOM: cout << "\tBOTTOM\n" << endl;
		break;
	    case RIGHT: cout << "\tRIGHT\n" << endl;
		break;
	    case LEFT: cout << "\tLEFT\n" << endl;
		break;
	    case TOP_LEFT: cout << "\tTOP_LEFT\n" << endl;
		break;
	    case TOP_RIGHT: cout << "\tTOP_RIGHT\n" << endl;
		break;
	    case BOTTOM_RIGHT:  cout << "\tBOTTOM_RIGHT\n" << endl;
		break;
	    case BOTTOM_LEFT: cout << "\tBOTTOM_LEFT\n" << endl;
		break;
	}
    }
}

double ceil_441(double f)
{
    return ceil(f-0.00001);
}

double floor_441(double f)
{
    return floor(f+0.00001);
}

int convertColor(double colorVal)
{
    return ceil_441(colorVal*255);
}

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(width, height, 1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
}

void
WriteImage(vtkImageData *img, const char *filename)
{
   std::string full_filename = filename;
   full_filename += ".png";
   vtkPNGWriter *writer = vtkPNGWriter::New();
   writer->SetInputData(img);
   writer->SetFileName(full_filename.c_str());
   writer->Write();
   writer->Delete();
}

class Point
{
  public:
     double x, y, z;
	Point()
	{
	    this->x = 0;
	    this->y = 0;
	    this->z = 0;
	}
	std::string PointAsString()
	{
	    std::string ret = "("+ std::to_string(x)+", "+std::to_string(y)+", "+ std::to_string(z)+")";
	    return ret;
	}
};

class Line
{
//stores an instance of a line in point-slope form
  public:
    Point point, point2;
    double slope, offset;
    Line()
    {
	slope = offset = 0;
	point = Point();
    }
    void CalculateSlope()
    {
    // calculates slope, requires all other variables to be intialized
	slope = (point.y-offset)/point.x;
    }
    void CalculateOffset()
    // calculates offset, requires all other variables to be intialized
    {
	if(!isnan(slope))
	{
	offset = point.y - (point.x*slope);
	}
	else
	{
	offset = 0;
	}
    }

    Point CalculateIntersection(Line otherLine)
    //Determines where two lines intersect, when otherLine is a horizontal line
    {
	Point ret = Point();
	if(!isnan(this->slope))	
	{
	    double intersectX;
	    intersectX = (otherLine.point.y - this->offset) / this->slope;
	    ret.x = intersectX;
	    ret.y = otherLine.point.y;
	}
	else
	{
	    ret.x = this->point.x;
	    ret.y = otherLine.point.y;
	}
	return ret;
    }
    template <typename T>
    // templated incase we have later fields that are non doubles
    static T InterpolateValue(double position1, double position2, T value1, T value2, double positionToFind)
    {
	double t;
	if(value1 == value2)
	{
	    return value1;
	}
	t = (positionToFind - position2)/(position1 - position2);
	return value2 + (t*(value1-value2));
    }
	    

    void PrintLine()
    {
	printf("This line has the attributes:\n");
	printf("\tx: %f\n", point.x);
	printf("\ty: %f\n", point.y);
	printf("\tslope: %f\n", slope);
	printf("\toffset: %f\n", offset);
    }
};

class Triangle
{
  public:
      double         X[3];
      double         Y[3];
      double         Z[3];
      double colors[3][3];
      TriangleType type;
      std::vector<VertexLocations> vertexLocs;
    void Intialize()
    {
	type = UNDEFINED;
	this->DetermineLocations();
	this->DetermineType();
    } 
    std::string TypeString()
    //returns the type as a string, if no type is found, UNDEFINED is returned
    {
	std::string ret;
	switch(type)
	{
	case GOING_UP:
	    ret = "GOING_UP";
	    break;
	case GOING_DOWN:
	    ret = "GOING_DOWN";
	    break;
	case ARBITRARY:
	    ret = "ARBITRARY";
	    break;
	default:
	    ret = "UNDEFINED";
	    break;
	}
	return ret;
    }
    std::vector<double> DetermineSlopes()
    //calculates and returns the slopes of the intersection sides of the triangle, if slope = X/0 set to 0.0, caller handles accordingly, slope for the line is stored in [I1][I2], where I1
    //    is the index of the first vertex and I2 the second.
    {
	double slope;
	double minX = std::numeric_limits<double>::max();
	double maxX = -1*std::numeric_limits<double>::max();
	int otherIndex = -1;
 	int minIndex, maxIndex;
	minIndex = maxIndex = -1;
	int index;
	std::vector<double> ret;
	if(type == GOING_DOWN)
	{
	    for(index = 0; index < 3; index++)
	    {
		if(vertexLocs[index] == BOTTOM)
		{
		    otherIndex = index;
		}
		if(minX > X[index] && index != otherIndex)
		{
		    minIndex = index;
	            minX = X[index];
		}
	        if(maxX < X[index] && index != otherIndex)
		{
			maxIndex = index;
			maxX = X[index];
	        }
	    }
	}
	if(type == GOING_UP)
	{
	    for(index = 0; index < 3; index++)
	    {
		if(vertexLocs[index] == TOP)
		{
		    otherIndex = index;
		}
		if(minX > X[index] && index != otherIndex)
		{
		    minIndex = index;
	            minX = X[index];
		}
	        if(maxX < X[index] && index != otherIndex)
		{
			maxIndex = index;
			maxX = X[index];
	        }
	    }
	}
	if(fabs(X[minIndex] -  X[otherIndex]) > EPSILON)
	{
	   slope = (Y[otherIndex] - Y[minIndex]) / (X[otherIndex] - X[minIndex]);
	}
	else
	{
	    slope = NAN;
	}
	ret.push_back(slope);
	if(fabs(X[maxIndex] - X[otherIndex]) > EPSILON)
	{
	    slope = (Y[maxIndex] - Y[otherIndex]) / (X[maxIndex] - X[otherIndex]);
	}
	else
	{
	    slope = NAN;
	}
	ret.push_back(slope);
	return ret;
    }
    void DetermineLocations()
    //determines and stores the locations of each vertex with respect to the others
    {
	double min = std::numeric_limits<double>::max();
	double max = -1*std::numeric_limits<double>::max();
	double toCheck;
	int Yindex, minYIndex, maxYIndex, midYIndex, vertexIndex;
	minYIndex = maxYIndex = midYIndex = -1;
	VertexLocations toPush;
	for(Yindex = 0; Yindex < 3; Yindex++)
	{
	//min and max y are bottom and top indices accordingly
	// both min and max are the first occurence of the largest Y val(ie with triangle points [30.4, 99, 99], min index is 0 and max index is 1) 
	    toCheck = Y[Yindex];
	    if(toCheck < min)
	    {
		min = toCheck;
		minYIndex = Yindex;
	    }
	    if(toCheck > max)
	    {
		max = toCheck;
		maxYIndex = Yindex;
	    }
	}
	
	for(vertexIndex = 0; vertexIndex < 3; vertexIndex++)
	{
	// find the index of the other point
	    if(vertexIndex != minYIndex && vertexIndex != maxYIndex)
	    {
		midYIndex = vertexIndex;
	    }
	}
	for(vertexIndex = 0; vertexIndex < 3; vertexIndex++)
	{
	    if(maxYIndex == vertexIndex)
	    {
		toPush = TOP;
	    }
	    else if(minYIndex == vertexIndex)
	    {
		toPush = BOTTOM;
	    }
	    else if(midYIndex == vertexIndex)
	    {
	        if(Y[midYIndex] - Y[minYIndex] < EPSILON)
	        {
		    toPush = X[midYIndex] > X[minYIndex] ? BOTTOM_RIGHT : BOTTOM_LEFT;	//x coord cant be same, so its either less than or greater than bottom coord
	        }
	        else if(Y[maxYIndex] - Y[midYIndex] < EPSILON)
	        {
		     toPush = X[midYIndex] > X[maxYIndex] ? TOP_RIGHT : TOP_LEFT;	//x coord cant be same, so its either less than or greater than top coord
	        }
	        else
	        {
		     //arbitrary triangle, determine if its the left or right of the top coord
		     toPush = X[midYIndex] > X[maxYIndex] ? RIGHT : LEFT;
	        }
	    }
	    vertexLocs.push_back(toPush);
	}
    }
 
    void DetermineType()
    //Determines the type of the triangle; going up, going down, arbitrary
    {
	int index;
	for(index = 0; index < 3; index++)
	{
	    if(vertexLocs[index] == RIGHT || vertexLocs[index] == LEFT)
	    {
		this->type = ARBITRARY;
	    }
	    if(vertexLocs[index] == TOP_RIGHT || vertexLocs[index] == TOP_LEFT)
	    {
		this->type = GOING_DOWN;
	    }
	    if(vertexLocs[index] == BOTTOM_RIGHT || vertexLocs[index] == BOTTOM_LEFT)
	    {
		this->type = GOING_UP;
	    }
	}
    }

    int NumScanLines()
    //calculates the number of scanlines this triangle needs
    {
	double min = std::numeric_limits<double>::max();
	double max = -1*std::numeric_limits<double>::max();
	double toCheck;
	int Yindex;
	for(Yindex = 0; Yindex < 3; Yindex++)
	{
	    toCheck = Y[Yindex];
	    min = toCheck < min ? toCheck : min;
            max = toCheck > max ? toCheck : max;
	}
	return floor_441(max) - ceil_441(min);
    }

    int *FindPointArray()
    //finds the location of each vertex and stores the index of each relative to each other in [minX, maxX, otherY] formatting
    //this will only work with a going down or going up triangle, so call at the right time
    //it is required that DetermineLocations() and DetermineType() is called before this to know the vertex locations and triangle type	
    {
	int minXIndex, maxXIndex, otherYIndex, index;
	double otherY;
	double maxX = std::numeric_limits<double>::max()*-1;
	double minX = std::numeric_limits<double>::max();
	minXIndex = maxXIndex = otherYIndex = -1;
	int *ret = new int[3];
	ret[0] = -1;
	ret[1] = -1;
	ret[2] = -1;
	if(this->type == GOING_UP)
	{
	    otherY = *std::max_element(Y, Y+3);
	}
	else if(this->type == GOING_DOWN)
	{
	    otherY = *std::min_element(Y, Y+3);
	}
	for(index = 0; index < 3; index++)
	{
	   if(fabs(otherY - Y[index]) < EPSILON)
	   {
		otherYIndex = index;
	   }
	   else// want to check both statements, but only if not the other Y, thus this ugly if statement appears
	   { 
		if(minX > X[index])
	        {
		    minX = X[index];
		    minXIndex = index;
	        }  
	        if(maxX < X[index])
	        {
		    maxX = X[index];
		    maxXIndex = index;
	        }
	   }
	}
	ret[0] = minXIndex;
	ret[1] = maxXIndex;
	ret[2] = otherYIndex;
	return ret;
    }
    void PrintTriangle()
    {
	std::cerr << "this triangle has the attributes" << std::endl;
        for(int i =0; i<3;i++)
	{
	    std::cerr << "\t(" << X[i] << ", " << Y[i] << ", " << Z[i] << ")" <<std::endl;
	}
	std::cerr << "\t" << std::endl;
	cerr << "Vertex Locations: " << endl;
	printVertexLocs(this->vertexLocs);
	std::cerr << "type: " << this->TypeString()<<std::endl;
    }
 
    void SplitTriangle(Triangle *bottomSplit, Triangle *topSplit)
    {
	double minY, maxY, newZ;
	int maxYIndex = -1;
	int minYIndex = -1;
	int midYIndex = -1;
	int index = 0;
	Line whereToSplit= Line();
	Line intersectedEdge = Line();
	Point intersectPoint;
	minY = *std::min_element(this->Y, this->Y+3);
	maxY = *std::max_element(this->Y, this->Y+3);
	for(; index < 3; index++)
	{
	    if(Y[index] != minY && Y[index] != maxY)
	    {
		midYIndex = index;
	    }
	    else if(Y[index] == minY)
	    {
		minYIndex = index;
	    }
	    else if(Y[index] == maxY)
	    {
		maxYIndex = index;
	    }
	}
	if(midYIndex != -1)
	{
	    whereToSplit.slope = 0;
	    whereToSplit.point.x = X[midYIndex];
	    whereToSplit.point.y = Y[midYIndex];
	    whereToSplit.CalculateOffset();
	    intersectedEdge.point.x = X[maxYIndex];
	    intersectedEdge.point.y = Y[maxYIndex];
	    if(X[minYIndex] != X[maxYIndex])
	    {
	        intersectedEdge.slope = (Y[minYIndex] - Y[maxYIndex]) / (X[minYIndex] - X[maxYIndex]);
	    }
	    else
	    {
		intersectedEdge.slope = NAN;
	    }
	    intersectedEdge.CalculateOffset();
	    intersectPoint = intersectedEdge.CalculateIntersection(whereToSplit);
	    newZ = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], Z[minYIndex], Z[maxYIndex], intersectPoint.y);
	    bottomSplit->X[0] = intersectPoint.x;
	    bottomSplit->X[1] = X[minYIndex];
	    bottomSplit->X[2] = X[midYIndex];
	    bottomSplit->Y[0] = intersectPoint.y;
	    bottomSplit->Y[1] = Y[minYIndex];
	    bottomSplit->Y[2] = Y[midYIndex];
	    bottomSplit->Z[0] = newZ;
	    bottomSplit->Z[1] = Z[minYIndex];
	    bottomSplit->Z[2] = Z[midYIndex];
	    bottomSplit->colors[0][0] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][0], colors[maxYIndex][0], intersectPoint.y);
	    bottomSplit->colors[0][1] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][1], colors[maxYIndex][1], intersectPoint.y);
	    bottomSplit->colors[0][2] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][2], colors[maxYIndex][2], intersectPoint.y);
	    bottomSplit->colors[1][0] = this->colors[minYIndex][0];
	    bottomSplit->colors[1][1] = this->colors[minYIndex][1];
	    bottomSplit->colors[1][2] = this->colors[minYIndex][2];
	    bottomSplit->colors[2][0] = this->colors[midYIndex][0];
	    bottomSplit->colors[2][1] = this->colors[midYIndex][1];
	    bottomSplit->colors[2][2] = this->colors[midYIndex][2];

	    topSplit->X[0] = intersectPoint.x;
	    topSplit->X[1] = X[maxYIndex];
	    topSplit->X[2] = X[midYIndex];
	    topSplit->Y[0] = intersectPoint.y;
	    topSplit->Y[1] = Y[maxYIndex];
	    topSplit->Y[2] = Y[midYIndex];
	    topSplit->Z[0] = newZ;
	    topSplit->Z[1] = Z[maxYIndex];
	    topSplit->Z[2] = Z[midYIndex];
	    topSplit->colors[0][0] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][0], colors[maxYIndex][0], intersectPoint.y);
	    topSplit->colors[0][1] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][1], colors[maxYIndex][1], intersectPoint.y);
	    topSplit->colors[0][2] = Line::InterpolateValue(Y[minYIndex], Y[maxYIndex], colors[minYIndex][2], colors[maxYIndex][2], intersectPoint.y);
	    topSplit->colors[1][0] = this->colors[maxYIndex][0];
	    topSplit->colors[1][1] = this->colors[maxYIndex][1];
	    topSplit->colors[1][2] = this->colors[maxYIndex][2];
	    topSplit->colors[2][0] = this->colors[midYIndex][0];
	    topSplit->colors[2][1] = this->colors[midYIndex][1];
	    topSplit->colors[2][2] = this->colors[midYIndex][2];

	    bottomSplit->Intialize();
	    topSplit->Intialize();
	}
    }
};
#endif
