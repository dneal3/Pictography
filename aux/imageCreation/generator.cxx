#include "ImageManager.h"
#include "../io/DataReader.h"
int main(void)
{
	//DataReader::Read("proj1d_geometry.vtk");
	std::vector<Triangle> temp = DataReader::Read("output");
	ImageManager::CreateImage(temp, "testOut");
}
