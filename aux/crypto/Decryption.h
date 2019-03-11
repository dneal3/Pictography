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
		std::cerr << "no key input detected. Exiting to avoid crash." << std::endl;
		return std::string();	//caller checks for empty string on other end
	}

        int numColors = 9*tris.size();
        double shiftedColors[numColors];

        printf("\n\n");

        // Put triangle colors into array
        for (int i = 0; i < tris.size(); i++)
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
            shiftedColors[i] = shiftedColors[i] * 255 - key[i%127];
            printf("shiftedColors[%d] = %f\n", i, shiftedColors[i]);
        }

        for (int i = 0; i < tris.size(); i++)
        {
        }

	int trisSize, i, i2, colorPositions[9];
	double charSum;
	std::string toRet = "";
	bool isOdd = key[0]%2 == 1 ? true : false;
	trisSize = tris.size();
	if(isOdd)
	{
		std::cerr << "is Odd" << std::endl;
		colorPositions[0] = 2;
		colorPositions[1] = 0;
		colorPositions[2] = 1;
	
		colorPositions[3] = 0;
		colorPositions[4] = 1;
		colorPositions[5] = 2;
	
		colorPositions[6] = 1;
		colorPositions[7] = 2;
		colorPositions[8] = 0;
	}
	else
	{
		std::cerr << "is Even" << std::endl;
		colorPositions[0] = 0;
		colorPositions[1] = 1;
		colorPositions[2] = 2;
	
		colorPositions[3] = 1;
		colorPositions[4] = 2;
		colorPositions[5] = 0;
	
		colorPositions[6] = 2;
		colorPositions[7] = 0;
		colorPositions[8] = 1;
	}
	for(i =0; i < trisSize; i++)
	{
		for(i2 = 0; i2<3; i2++)
		{
		charSum = 0;
		charSum += tris[i].colors[0][colorPositions[3*i2  ]];

		charSum += tris[i].colors[1][colorPositions[3*i2+1]];

		charSum += tris[i].colors[2][colorPositions[3*i2+2]];

		charSum *= 100;
		charSum = ceil(charSum-0.5);
		toRet += (char)charSum;
		}
	}
	std::cerr << "final string: \"" << toRet << "\""<< std::endl;
	return toRet;
}

std::string Decrypter::Decrypt(std::vector<Triangle> tris, std::string keyToUse)
{
	Decrypter temp(keyToUse);
	return temp.Decrypt(tris);
}

#endif
