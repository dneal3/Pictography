#ifndef Decryption_h
#define Decryption_h
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
class Decrypter
{
	std::string key;
	
  public:
	//Dont want a getter for key, want to keep that to ourselves
	Decrypter(std::string keyIn){key = keyIn; printf("Received key %s\n", key.c_str());}

	static std::string Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points);	//allows for caller to use without creating an instance of the class
};

std::string Decrypter::Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points)
{
        return "Hello";
	//return temp.Decrypt(colors, points);
}

#endif
