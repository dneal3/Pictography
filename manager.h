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
      double *colors;
      std::string key;
      int numColors;
      int oddOrEvenFlag;
      void Encrypt();
      void Decrypt(const char *vtkfile);
      void WriteData(const char *vtkfile, const char *image);
      void ReadData(const char *vtkfile, const char *key);
      void WriteKey();
};

void Manager::Encrypt()
{
    // Create an Encryption class
    Encryption encrypt;

    // Get the variables of the Manager object
    colors = encrypt.doEncryption();
    key = encrypt.getKey();
    numColors = encrypt.getNumColors();
    oddOrEvenFlag = (key[0] - '0') - 32;
}

void Manager::WriteData(const char *vtkfile, const char *image)
{
    // This class writes encrypted message into a .vtk file
    DataWriter writer;

    // Put doubles into vector for colors
    std::vector<double> vectorColorBuffer(numColors);
    for (int i = 0; i < numColors; i++)
    {   
        vectorColorBuffer[i] = colors[i];
    }   

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
    writer.write(vectorColorBuffer, vectorPoints, vtkfile);

    std::vector<Triangle> temp = DataReader::Read(vtkfile);
    ImageManager::CreateImage(temp, image);
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
   std::ofstream keyFile;
   keyFile.open("secretkey.txt");
   keyFile << key;
   keyFile.close();
}

#endif
