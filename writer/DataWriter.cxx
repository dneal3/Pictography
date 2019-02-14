#include "DataWriter.h"
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
using namespace std;
DataWriter::DataWriter(void)
{
}
void DataWriter::write(vector<double> colors, vector<pair<double, double> > pointsIn, const char *filename)
{
	vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
	int i;
 	static double x[8][3]={{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};
 	static vtkIdType pts[6][4]={{0,1,2}, {4,5,6}, {0,5,4}, {1,6,5}, {3,7,6}, {3,4,7}};
	vtkPolyData *tri = vtkPolyData::New();
	vtkPoints *points = vtkPoints::New();
	vtkCellArray *polys = vtkCellArray::New();
	vtkFloatArray *scalars = vtkFloatArray::New();
 	for (i=0; i<8; i++) points->InsertPoint(i,x[i]);
 	for (i=0; i<6; i++) polys->InsertNextCell(3,pts[i]);
 	for (i=0; i<8; i++) scalars->InsertTuple1(i,i);
 	// We now assign the pieces to the vtkPolyData.
 	tri->SetPoints(points);
 	points->Delete();
 	tri->SetPolys(polys);
 	polys->Delete();
 	tri->GetPointData()->SetScalars(scalars);
 	scalars->Delete();

	writer->SetInputData(tri);
	writer->SetFileName(filename);
	writer->Write();
}
int main(void)
{
	DataWriter w;
	vector<double> c;
	vector<pair<double, double> >pts;
	const char * fn = "output";
	w.write(c, pts, fn);
}
