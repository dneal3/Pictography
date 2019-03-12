#ifndef Decryption_h
#define Decryption_h
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "../imageCreation/Triangle.h"
#include <vector>
#include <math.h>
class Decrypter
{
	std::string key;
	
  public:
	//Dont want a getter for key, want to keep that to ourselves
	Decrypter(std::string keyIn){key = keyIn;}
	Decrypter(void){key = std::string();}
	
	void SetKey(std::string keyThatShouldveBeenInConstructor){key = keyThatShouldveBeenInConstructor;}
	std::string Decrypt(std::vector<Triangle> tris);
	static std::string Decrypt(std::vector<Triangle> tris,std::string keyToUse);	//allows for caller to use without creating an instance of the class
};

std::string Decrypter::Decrypt(std::vector<Triangle> tris)
{
	if(this->key.empty())
	{
		std::string errMsg =  std::string("no key input detected. Exiting to avoid crash.");
		return errMsg;
	}

    int numColors = 9*tris.size();
    double shiftedColors[numColors];

    // Put triangle colors into array
    int trisSize = tris.size();
    for (int i = 0; i < trisSize; i++)
    {
            shiftedColors[i*9 + 0] = tris[i].colors[0][0];
            shiftedColors[i*9 + 1] = tris[i].colors[0][1];
            shiftedColors[i*9 + 2] = tris[i].colors[0][2];
            shiftedColors[i*9 + 3] = tris[i].colors[1][0];
            shiftedColors[i*9 + 4] = tris[i].colors[1][1];
            shiftedColors[i*9 + 5] = tris[i].colors[1][2];
            shiftedColors[i*9 + 6] = tris[i].colors[2][0];
            shiftedColors[i*9 + 7] = tris[i].colors[2][1];
            shiftedColors[i*9 + 8] = tris[i].colors[2][2];
    }

    for (int i = 0; i < numColors; i++)
    {
        shiftedColors[i] = (shiftedColors[i] * 255) - key[i%127];
    }
    
    int rows;
    int cols;
    std::string n1 = "";
    std::string n2 = "";
    
    //extract first factor
    n1 += key[122];
    n1 += key[123];
    n1 += key[124];
    
    //extract second factor
    n2 += key[125];
    n2 += key[126];
    n2 += key[127];
    
    //convert to integer using std::stoi() "string to integer"
    rows = std::stoi(n1);
    cols = std::stoi(n2);

    //un-rearrange colors
    double unShiftedColors[numColors];
    int unShiftedIndex = 0;
    int shiftedIndex;
    for(int c = 0; c < cols; c++)
    {
        for(int r = 0; r < rows; r++)
        {
            shiftedIndex = (r*cols)+c;
            unShiftedColors[unShiftedIndex] = shiftedColors[shiftedIndex];
            unShiftedIndex++;
        }
    }
    
    std::string tempOdd = "";
    tempOdd += key[0];
    int isOdd = std::stoi(tempOdd);
    int numTris = numColors/9;
    int offset = 0;
    double char1;
    double char2;
    double char3;
    std::string toRet = "";
    
    if(!isOdd)
    {
        for(int i = 0; i < numTris; i++)
        {
            char1 = 0;
            char2 = 0;
            char3 = 0;
            
            offset = 9 * i;
            char1 += unShiftedColors[offset];
            char1 += unShiftedColors[offset+4];
            char1 += unShiftedColors[offset+8];
            char1 = ceil(char1-0.5);
            toRet += (char)char1;
            
            char2 += unShiftedColors[offset+1];
            char2 += unShiftedColors[offset+5];
            char2 += unShiftedColors[offset+6];
            char2 = ceil(char2-0.5);
            toRet += (char)char2;
            
            char3 += unShiftedColors[offset+2];
            char3 += unShiftedColors[offset+3];
            char3 += unShiftedColors[offset+7];
            char3 = ceil(char3-0.5);
            toRet += (char)char3;
            
        }
    }
    else if(isOdd)
    {
        for(int i = 0; i < numTris; i++)
        {
            char1 = 0;
            char2 = 0;
            char3 = 0;
            
            offset = 9 * i;
            char1 += unShiftedColors[offset+2];
            char1 += unShiftedColors[offset+3];
            char1 += unShiftedColors[offset+7];
            char1 = ceil(char1-0.5);
            toRet += (char)char1;
            
            char2 += unShiftedColors[offset];
            char2 += unShiftedColors[offset+4];
            char2 += unShiftedColors[offset+8];
            char2 = ceil(char2-0.5);
            toRet += (char)char2;

            
            char3 += unShiftedColors[offset+1];
            char3 += unShiftedColors[offset+5];
            char3 += unShiftedColors[offset+6];
            char3 = ceil(char3-0.5);
            toRet += (char)char3;
            
        }
    }

    //extract first factor
    n1 = "";
    n2 = "";
    
    n1 += key[1];
    n1 += key[2];
    n1 += key[3];
    
    //extract second factor
    n2 += key[4];
    n2 += key[5];
    n2 += key[6];
    
    //convert to integer using std::stoi() "string to integer"
    rows = std::stoi(n1);
    cols = std::stoi(n2);
    std::string decryptedString;
    int encryptedIndex=0;
    for(int c = 0; c < cols; c++)
    {
        for(int r = 0; r < rows; r++)
        {
            encryptedIndex = (r*cols)+c;
            decryptedString += toRet[encryptedIndex];
        }
    }
    
    return decryptedString;
}

std::string Decrypter::Decrypt(std::vector<Triangle> tris, std::string keyToUse)
{
	Decrypter temp(keyToUse);
	return temp.Decrypt(tris);
}

#endif
