#ifndef MANAGER
#define MANAGER

#include "aux/crypto/Encryption.hpp"
#include "aux/crypto/Decryption.h"
#include "aux/io/DataWriter.h"
#include "aux/io/DataReader.h"
#include "aux/imageCreation/ImageManager.h"

#include <iostream>
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
	std::cerr << "after encryption" << std::endl;
    key = encrypt.getKey();
	fprintf(stderr, "key in manager is %p\n", &key);
    oddOrEvenFlag = (key[0] - '0') - 32;
	std::cerr << "writing key to file" << std::endl;
    std::ofstream keyFile;
    keyFile.open("secretkey.txt");
	std::cerr << "opened" << std::endl;
	fprintf(stderr, "keyFile ptr is %p\n", &keyFile);
    keyFile << key;
	std::cerr << "added" << std::endl;
    keyFile.close();
	std::cerr << "end of encryption" << std::endl;
}

void Manager::WriteData(const char *vtkfile, const char *image)
{
	fprintf(stderr, "vtkfile is%p, image is%p\n", vtkfile, image);
    // This class writes encrypted message into a .vtk file
    DataWriter writer;

    // Put doubles into vector for colors
	std::cerr << "number of colors " << numColors << std::endl;
    // Put doubles into vector for vertices
    std::vector<std::pair<double, double>> vectorPoints(numColors/3);
    vectorPoints[0] = {50,50};
    for (int i = 1; i < (numColors/3); i+=3)
    {   
       vectorPoints[i  ] = { vectorPoints[i-1].first   , vectorPoints[i-1].second + 50};
       vectorPoints[i+1] = { vectorPoints[i-1].first-50, vectorPoints[i-1].second + 50};
       vectorPoints[i+2] = { vectorPoints[i-1].first+50, vectorPoints[i-1].second + 50};
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
       printf("Received the following colors for triangle %d\n", i);
       printf("%f\n%f\n%f\n", triangles[i].colors[0][0], triangles[i].colors[0][1], triangles[i].colors[0][2]);
       printf("%f\n%f\n%f\n", triangles[i].colors[1][0], triangles[i].colors[1][1], triangles[i].colors[1][2]);
       printf("%f\n%f\n%f\n", triangles[i].colors[2][0], triangles[i].colors[2][1], triangles[i].colors[2][2]);
    }

    Decrypter decrypt(key);
    decrypt.Decrypt(triangles, key);
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
