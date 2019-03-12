#ifndef MANAGER
#define MANAGER

#include "aux/crypto/Encryption.hpp"
#include "aux/crypto/Decryption.h"
#include "aux/io/DataWriter.h"
#include "aux/io/DataReader.h"
#include "aux/imageCreation/ImageManager.h"

#include <iostream>
#include <math.h>
#include <fstream>
class Manager
{
   public:
      std::vector<double> colors;
      std::string key;
      int numColors;
      int oddOrEvenFlag;
      void Encrypt(std::string toEncrypt);
      void Decrypt(const char *vtkfile);
      void WriteData(const char *vtkfile, const char *image);
      void ReadData(const char *vtkfile, const char *key);
      void WriteKey();
};

void Manager::Encrypt(std::string toEncrypt)
{
    // Create an Encryption class
    Encryption encrypt(toEncrypt);

    // Get the variables of the Manager object
    colors = encrypt.doEncryption();
	int count = 0;
	int tempIndex = 0;
	numColors = colors.size();
    key = encrypt.getKey();
    oddOrEvenFlag = (key[0] - '0') - 32;
	std::cout << key;
	std::cerr << "end of encryption" << std::endl;
}

void Manager::WriteData(const char *vtkfile, const char *image)
{
	fprintf(stderr, "vtkfile is%p, image is%p\n", vtkfile, image);
    // This class writes encrypted message into a .vtk file
    DataWriter writer;
	const int numberOfTriangles = numColors/9;
	const int numPoints = floor(numberOfTriangles/2.0);
	const int numPointsTop      = numPoints;
	const int numPointsBottom   =  numberOfTriangles%2 == 0 ? numPoints : numPoints+1;
	const double spacingTop = 1000/numPointsTop;
	const double spacingBottom = 1000/numPointsBottom;
	double tempSpacing = spacingTop;
	int tempCtr = 0;

	fprintf(stderr, "number of tris %d\n", numberOfTriangles);
	fprintf(stderr, "number of top points %d\n", numPointsTop);
	fprintf(stderr, "number of bottom points %d\n", numPointsBottom);
	fprintf(stderr, "spacing of top %f\n", spacingTop);
	fprintf(stderr, "spacing of bottom %f\n", spacingBottom);

    // Put doubles into vector for colors
	std::cerr << "number of colors " << numColors << std::endl;
    // Put doubles into vector for vertices
    std::vector<std::pair<double, double>> vectorPoints(numColors/3);
    vectorPoints[0] = {0, 0};
    vectorPoints[1] = {1000, 0};
    vectorPoints[2] = {0, spacingBottom};
    for (int i = 3; i < (numColors/3); i+=3)
    {   
	tempSpacing = tempCtr%2 == 0 ? spacingTop : spacingBottom;
       vectorPoints[i  ] = { vectorPoints[i-2].first, vectorPoints[i-2].second};
       vectorPoints[i+1] = { vectorPoints[i-1].first, vectorPoints[i-1].second};
       vectorPoints[i+2] = { vectorPoints[i-2].first, vectorPoints[i-2].second+tempSpacing};
	tempCtr++;
    }   

    // Write data to output file
	std::cerr << "beginning to write data " << std::endl;
    writer.write(colors, vectorPoints, vtkfile);
	std::cerr << "written all data " << std::endl;

    std::vector<Triangle> temp = DataReader::Read(vtkfile);
    ImageManager::CreateImage(temp, image);
	std::cerr << "end of write data" << std::endl;
}

void Manager::ReadData(const char *vtkfile, const char *key)
{
    std::vector<Triangle> temp = DataReader::Read(vtkfile);
    this->key = key; 
}

void Manager::Decrypt(const char *vtkfile)
{
    std::vector<Triangle> triangles = DataReader::Read(vtkfile);

    double vectorColorBuffer[triangles.size()][3];
    for (int i = 0; i < triangles.size(); i++)
    {
       fprintf(stderr, "Received the following colors for triangle %d\n", i);
       fprintf(stderr, "%f\n%f\n%f\n", triangles[i].colors[0][0], triangles[i].colors[0][1], triangles[i].colors[0][2]);
       fprintf(stderr, "%f\n%f\n%f\n", triangles[i].colors[1][0], triangles[i].colors[1][1], triangles[i].colors[1][2]);
       fprintf(stderr, "%f\n%f\n%f\n", triangles[i].colors[2][0], triangles[i].colors[2][1], triangles[i].colors[2][2]);
    }

    Decrypter decrypt(key);
    std::cout << decrypt.Decrypt(triangles, key);
}

void Manager::WriteKey()
{
	std::cerr << "in write key" << std::endl;
//   std::ofstream keyFile;
//   keyFile.open("secretkey.txt");
//   keyFile << key;
//   keyFile.close();
}

#endif
