#ifndef DATAWRITER
#define DATAWRITER
#include <iostream>
#include <vector>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>

enum ErrorType{NOERR = 0, INVALIDNUMPTS};
class invalidData : public std::exception
{
	ErrorType errorCode;
	public:
	invalidData(void){this->errorCode = NOERR;}
	invalidData SetErr(ErrorType err){errorCode = err; return *this;}
	std::string errorMsg()
	{
		switch(errorCode)
		{
			case NOERR:	return "No error detected. Forgot to set errorCode? Contact Daniel for debugging";
			case INVALIDNUMPTS: return "invalid number of triangles";
			default:	return "No valid ErrorType detected. Not sure how this happened, contact Daniel for debugging";
		}
	}
} myErr;
class DataWriter
{
	public:
	DataWriter(void){};
	void write(std::vector<double> colors, std::vector<std::pair<double, double> > pointsIn, const char *filename);
};

void DataWriter::write(std::vector<double> colors, std::vector<std::pair<double, double> > pointsIn, const char *filename)
{
        vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
        vtkPolyData *tris = vtkPolyData::New();
        vtkPoints *points = vtkPoints::New();
        vtkCellArray *polys = vtkCellArray::New();
        vtkFloatArray *scalars = vtkFloatArray::New();
        int i, i2=0;
	try
	{
        	const int ptsLen = pointsIn.size();
		if(ptsLen%3 != 0){throw myErr.SetErr(INVALIDNUMPTS);}//throw invalidData(); } 	//ensure there are enough points to build entirely whole triangles with the data
		int numTris = ptsLen/3;
		double ptLocs[3];
		vtkIdType vertices[3];
		for(i=0; i<ptsLen; i+=3)
		{
			for(i2=0; i2<3; i2++)
			{
				vertices[i2] = i+i2;
				ptLocs[0] = pointsIn[i+i2].first;
				ptLocs[1] = pointsIn[i+i2].second;
				ptLocs[2] = 0;
				points->InsertPoint(i+i2, ptLocs);
			}
			polys->InsertNextCell(3, vertices);
			scalars->InsertTuple1(i,i);
		}
        	// We now assign the pieces to the vtkPolyData.
        	tris->SetPoints(points);
        	points->Delete();
        	tris->SetPolys(polys);
        	polys->Delete();
        	tris->GetPointData()->SetScalars(scalars);
        	scalars->Delete();
	
	        writer->SetInputData(tris);
        	writer->SetFileName(filename);
        	writer->Write();
	}
	catch(invalidData e)
	{
		cerr << "AN ERROR OCCURED!" << endl;
		cerr << "**********************************" << endl;
		cerr << "ERROR: " << e.errorMsg() << endl;
	}
}
#endif
