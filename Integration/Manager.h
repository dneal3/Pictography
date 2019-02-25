#ifndef MANAGER
#define MANAGER

#include "Encryption.hpp"
#include "Decryption.hpp"
#include "DataWriter.h"
#include "DataReader.h"
#include "Rasterize.h"

class Manager
{
   public:
      double *colors;
      char *key;
      int numColors;
      int oddOrEvenFlag;
      void Encrypt();
      void Decrypt();
      void WriteData();
      void Rasterize();
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

void Manager::WriteData()
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
    for (int i = 0; i < (numColors/3); i++)
    {   
       vectorPoints[i] = { 0, 1 };
    }   

    // Write data to output file
    const char *filename = "output.vtk";
    writer.write(vectorColorBuffer, vectorPoints, filename);
}

void Manager::Rasterize()
{
    DataReader reader;
    Rasterization rasterize(reader.GetTriangles());
}

void Manager::Decrypt()
{
    Decryption decrypt;
}

#endif
