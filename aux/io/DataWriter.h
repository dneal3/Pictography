#ifndef DATAWRITER
#define DATAWRITER
#include "ErrorHandling.h"
#include <iostream>
#include <vector>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
void log(std::string msg)
{
	std::cerr << msg << std::endl;
}
class DataWriter
{
	public:
	DataWriter(void){};
	void write(std::vector<double> colorsIn, std::vector<std::pair<double, double> > pointsIn, const char *filename);
};

void DataWriter::write(std::vector<double> colorsIn, std::vector<std::pair<double, double> > pointsIn, const char *filename)
{
fprintf(stderr, "entered data writer\n");
        int i, i2=0;
std::cerr << "about to allocate colors" << std::endl;
	vtkSmartPointer<vtkDoubleArray> colorsOut = vtkSmartPointer<vtkDoubleArray>::New();
	//vtkDoubleArray *colorsOut = vtkDoubleArray::New();
fprintf(stderr, "colorsOut %p\n", &colorsOut);
	vtkSmartPointer<vtkDoubleArray> hashOut = vtkSmartPointer<vtkDoubleArray>::New();
	//vtkDoubleArray *hashOut = vtkDoubleArray::New();
fprintf(stderr, "hashOut %p\n", &hashOut);
        vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
        //vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
fprintf(stderr, "writer %p\n", &writer);
        vtkSmartPointer<vtkPolyData> tris = vtkSmartPointer<vtkPolyData>::New();
        //vtkPolyData *tris = vtkPolyData::New();
fprintf(stderr, "tris %p\n", &tris);
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        //vtkPoints *points = vtkPoints::New();
fprintf(stderr, "points %p\n", &points);
        vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
        //vtkCellArray *polys = vtkCellArray::New();
fprintf(stderr, "polys %p\n", &polys);
	vtkIdType vertices[3];
	double colorsToStore[3];
	double hashToStore = 3.33333333;//TODO = Encryption::GetHash();
	double ptLocs[3];

	const int colorsSize = colorsIn.size();
        const int ptsLen = pointsIn.size();
log("after all intialization");
	try
	{
		if(ptsLen%3 != 0){throw myErr.SetErr(INVALIDNUMPTS);} //ensure there are enough points to build entirely whole triangles with the data
		if(colorsSize%3 != 0){throw myErr.SetErr(INVALIDNUMTRIS);}	
		if((double)colorsSize/3 != ptsLen){throw myErr.SetErr(UNEQUALLENS);}
		if(filename == nullptr || filename[0] == '\0'){throw myErr.SetErr(BADFILENAME);}
		log("setting hash");
		hashOut->SetNumberOfComponents(1);
		hashOut->SetName("HASH");
		hashOut->InsertNextTuple(&hashToStore);
log("setting colors");
		colorsOut->SetNumberOfComponents(3);
		colorsOut->SetName("COLORS");
		for(i=0; i<colorsSize; i+=3)
		{
			colorsToStore[0] = colorsIn[i  ];
			colorsToStore[1] = colorsIn[i+1];
			colorsToStore[2] = colorsIn[i+2];
			colorsOut->InsertNextTuple(colorsToStore);
		}
log("setting vertices");
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
	//		scalars->InsertTuple1(i,i);
		}
        	// We now assign the pieces to the vtkPolyData.
log("assigning pieces");
		tris->GetFieldData()->AddArray(colorsOut);
        	tris->SetPoints(points);
  //      	points->Delete();
        	tris->SetPolys(polys);
//        	polys->Delete();
        //	tris->GetPointData()->SetScalars(scalars);
       // 	scalars->Delete();
log("writing to file");
	        writer->SetInputData(tris);
        	writer->SetFileName(filename);
        	writer->Write();
log("end of try statement");
	}
	catch(invalidData e)
	{
		cerr << "AN ERROR OCCURED at " << __func__ << "!" << endl;
		cerr << "ERROR: " << e.errorMsg() << endl;
	}
log("returning");
}
#endif
