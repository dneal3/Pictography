#ifndef DATAREADER
#define DATAREADER

#include <iostream>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>

#include "Triangle.h"

class DataReader
{
   public:
     std::vector<Triangle> triangles;
     std::vector<Triangle> GetTriangles(std::string f);
     std::vector<Triangle> read(std::string f);
};

std::vector<Triangle> DataReader::GetTriangles(std::string filename)
{
	int numCells, i;
	int hash = 0;
	double *pt = NULL;
	vtkIdType npts, *ptIds;
	vtkPolyDataReader *reader = vtkPolyDataReader::New();	
	reader->SetFileName(filename.c_str());
	reader->Update();
	vtkPolyData *data = reader->GetOutput();
	numCells = data->GetNumberOfCells();
	if(numCells == 0){cerr << "NO CELLS!!!" << endl; exit(0);/*throw err*/}
	vtkPoints *pts = data->GetPoints();
	vtkCellArray *cells = data->GetPolys();
	vtkDoubleArray *colors = (vtkDoubleArray *)data->GetFieldData()->GetArray("COLORS");
double *color_ptr = colors->GetPointer(0);
	//vtkDoubleArray *hashArray = (vtkDoubleArray *)data->GetFieldData()->GetArray("HASH");
	//hash = hashArray->GetComponent(0, 1);
	for(i =0; i<9; i++)
	{
		cerr << colors->GetComponent(0, i) << endl;
	}
	cerr << "points: " << endl;
	std::vector<Triangle> tris(numCells);
	for(i =0, cells->InitTraversal(); cells->GetNextCell(npts, ptIds); i++)
	{
		if(npts != 3){}
		pt = pts->GetPoint(ptIds[0]);
                tris[i].X[0] = pt[0];
                tris[i].Y[0] = pt[1];
                tris[i].Z[0] = pt[2];
		pt = pts->GetPoint(ptIds[1]);
                tris[i].X[1] = pt[0];
                tris[i].Y[1] = pt[1];
                tris[i].Z[1] = pt[2];
		pt = pts->GetPoint(ptIds[2]);
		tris[i].X[2] = pt[0];
		tris[i].Y[2] = pt[1];
		tris[i].Z[2] = pt[2];

tris[i].color[0] = (unsigned char) colors->GetComponent(0, i);
//tris[i].color[0] = (unsigned char) color_ptr[4*ptIds[0]+0];;
printf("color is %c\n", tris[i].color[0]);
	}

/*
    vtkIdType npts;
    vtkIdType *ptIds;
    int idx;
    for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++)
    {
        tris[idx].X[0] = pts->GetPoint(ptIds[0])[0];
        tris[idx].X[1] = pts->GetPoint(ptIds[1])[0];
        tris[idx].X[2] = pts->GetPoint(ptIds[2])[0];
        tris[idx].Y[0] = pts->GetPoint(ptIds[0])[1];
        tris[idx].Y[1] = pts->GetPoint(ptIds[1])[1];
        tris[idx].Y[2] = pts->GetPoint(ptIds[2])[1];
        tris[idx].color[0] = (unsigned char) color_ptr[4*ptIds[0]+0];
        tris[idx].color[1] = (unsigned char) color_ptr[4*ptIds[0]+1];
        tris[idx].color[2] = (unsigned char) color_ptr[4*ptIds[0]+2];
    }
    cerr << "Done reading" << endl;
*/
    return tris;
}

std::vector<Triangle> DataReader::read(std::string filename)
{
   triangles = GetTriangles(filename);
   return triangles;
}

#endif
