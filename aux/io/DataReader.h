#ifndef DATAREADER_H
#define DATAREADER_H
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>

class DataReader
{
	
	public:
		DataReader(void){};
		void read(std::string filename);
		static void Read(std::string filename);
};

void DataReader::read(std::string filename)
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
	if(numCells == 0){cerr << "NO CELLS!!!" << endl; return ;/*throw err*/}
	vtkPoints *pts = data->GetPoints();
	vtkCellArray *cells = data->GetPolys();
	vtkDoubleArray *colors = (vtkDoubleArray *)data->GetFieldData()->GetArray("COLORS");
	//vtkDoubleArray *hashArray = (vtkDoubleArray *)data->GetFieldData()->GetArray("HASH");
	//hash = hashArray->GetComponent(0, 1);
	cerr << "hash value read is: " << hash << endl;
	cerr << "colors: " << endl;
	for(i =0; i<9; i++)
	{
		cerr << colors->GetComponent(0, i) << endl;
	}
	cerr << "points: " << endl;
	for(i =0, cells->InitTraversal(); cells->GetNextCell(npts, ptIds); i++)
	{
		if(npts != 3){/*TODO throw err*/}
		pt = pts->GetPoint(ptIds[0]);
		cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
		pt = pts->GetPoint(ptIds[1]);
		cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
		pt = pts->GetPoint(ptIds[2]);
		cerr << "(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")" << endl;
	}
	
	
}

void DataReader::Read(std::string filename)
{
	DataReader temp;
	temp.read(filename);
}


#endif
