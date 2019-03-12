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
      std::vector<Triangle> triangles;
      std::string key;
      int numColors;
      int oddOrEvenFlag;
      void Encrypt(std::string toEncrypt);
      void Decrypt();
      void WriteData(const char *vtkfile, const char *image);
      void ReadData(const char *vtkfile, const char *key);
};

void Manager::Encrypt(std::string toEncrypt)
{
    // Create an Encryption class
    Encryption encrypt(toEncrypt);

    // Get the variables of the Manager object
    colors = encrypt.doEncryption();
    numColors = colors.size();
    key = encrypt.getKey();
    oddOrEvenFlag = (key[0] - '0') - 32;
    std::cout << key;	//key is returned to UI via std::cout. Qt runs process in virtual environment, this is not printed anywhere
}

void Manager::WriteData(const char *vtkfile, const char *image)
{
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
    writer.write(colors, vectorPoints, vtkfile);
    std::vector<Triangle> temp = DataReader::Read(vtkfile);
    ImageManager::CreateImage(temp, image);
}

void Manager::ReadData(const char *vtkfile, const char *key)
{
    triangles = DataReader::Read(vtkfile);
    this->key = key; 
}

void Manager::Decrypt()
{
    //std::vector<Triangle> triangles = DataReader::Read(vtkfile);
    Decrypter decrypt(key);
    std::cout << decrypt.Decrypt(triangles);	//decrypted string is returned to the UI via std::cout. This is run in a virtual environment, so this is not printed anywhere.
}

#endif
