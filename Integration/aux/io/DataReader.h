#ifndef DATAREADER_H
#define DATAREADER_H
#include "ErrorHandling.h"
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include "../imageCreation/Triangle.h"
class DataReader
{
	
	public:
		DataReader(void){};
		std::vector<Triangle> read(std::string filename);
		static std::vector<Triangle> Read(std::string filename);
};

std::vector<Triangle> DataReader::read(std::string filename)
{
	int numCells, i;
	int hash = 0;
	double *pt = NULL;
	std::vector<Triangle> tris;
	vtkIdType npts, *ptIds;
	vtkPolyDataReader *reader = vtkPolyDataReader::New();	
	reader->SetFileName(filename.c_str());
	reader->Update();
	vtkPolyData *data = reader->GetOutput();
	numCells = data->GetNumberOfCells();
	try
	{
		if(numCells == 0){throw myErr.SetErr(BADCELLCOUNT);}
		tris = std::vector<Triangle>(numCells);
		vtkPoints *pts = data->GetPoints();
		vtkCellArray *cells = data->GetPolys();
		vtkDoubleArray *colors = (vtkDoubleArray *)data->GetFieldData()->GetArray("COLORS");
		//vtkDoubleArray *hashArray = (vtkDoubleArray *)data->GetFieldData()->GetArray("HASH");
		//hash = hashArray->GetComponent(0, 1);
		cerr << "hash value read is: " << hash << endl;
		cerr << "points: " << endl;
		for(i =0, cells->InitTraversal(); cells->GetNextCell(npts, ptIds); i++)
		{
			if(npts != 3){myErr.SetErr(NONTRIANGLEFOUND);}
			pt = pts->GetPoint(ptIds[0]);
			tris[i].X[0] = pt[0];
			tris[i].Y[0] = pt[1];
			tris[i].Z[0] = pt[2];
			tris[i].colors[0][0] = colors->GetComponent(0, 3*i  );
			tris[i].colors[0][1] = colors->GetComponent(0, 3*i+1);
			tris[i].colors[0][2] = colors->GetComponent(0, 3*i+2);
			cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
			pt = pts->GetPoint(ptIds[1]);
			tris[i].X[0] = pt[0];
			tris[i].Y[0] = pt[1];
			tris[i].Z[0] = pt[2];
			tris[i].colors[1][0] = colors->GetComponent(0, 3*i+3);
			tris[i].colors[1][1] = colors->GetComponent(0, 3*i+4);
			tris[i].colors[1][2] = colors->GetComponent(0, 3*i+5);
			cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
			pt = pts->GetPoint(ptIds[2]);
			tris[i].X[0] = pt[0];
			tris[i].Y[1] = pt[1];
			tris[i].Z[2] = pt[2];
			tris[i].colors[2][0] = colors->GetComponent(0, 3*i+6);
			tris[i].colors[2][1] = colors->GetComponent(0, 3*i+7);
			tris[i].colors[2][2] = colors->GetComponent(0, 3*i+8);
			cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
			cerr << "colors for this triangle:" << endl;
			cerr << colors->GetComponent(0, 3*i  ) << endl;
			cerr << colors->GetComponent(0, 3*i+1) << endl;
			cerr << colors->GetComponent(0, 3*i+2) << endl;
			cerr << colors->GetComponent(0, 3*i+3) << endl;
			cerr << colors->GetComponent(0, 3*i+4) << endl;
			cerr << colors->GetComponent(0, 3*i+5) << endl;
			cerr << colors->GetComponent(0, 3*i+6) << endl;
			cerr << colors->GetComponent(0, 3*i+7) << endl;
			cerr << colors->GetComponent(0, 3*i+8) << endl;
		}
	}
	catch(invalidData e)
	{
		cerr << e.errorMsg() << endl;
	}
	return tris;
	
}

std::vector<Triangle> DataReader::Read(std::string filename)
{
	DataReader temp;
	return temp.read(filename);
}


#endif