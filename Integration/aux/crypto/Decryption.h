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
	int trisSize, i, i2, colorPositions[9];
	double charSum;
	std::string toRet = "";
	bool isOdd = key[0]%2 == 1 ? true : false;
	double offR, offG, offB;
	offR = offG = offB = -1;
	trisSize = tris.size();
	if(isOdd)
	{
		std::cerr << "is Odd" << std::endl;
		offR = key[13] * 0.01;
		offG = key[5]  * 0.01;
		offB = key[16] * 0.01;
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
		offR = key[3]  * 0.01;
		offG = key[10] * 0.01;
		offB = key[15] * 0.01;
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
