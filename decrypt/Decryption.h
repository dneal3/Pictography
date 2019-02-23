#ifndef Decryption_h
#define Decryption_h
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
class Decrypter
{
	char *key;
	
  public:
	//Dont want a getter for key, want to keep that to ourselves
	Decrypter(char *keyIn){key = strdup(keyIn);}
	Decrypter(void){key = NULL;}
	virtual  ~Decrypter(){if(key != NULL) free(key);}
	
	void SetKey(char *keyThatShouldveBeenInConstructor){key = strdup(keyThatShouldveBeenInConstructor);}
	std::string Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points);
	static std::string Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points, char *keyToUse);	//allows for caller to use without creating an instance of the class
};

std::string Decrypter::Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points)
{
	if(this->key == NULL)
	{
		std::cerr << "no key input detected. Exiting to avoid crash." << std::endl;
	}
	//TODO DECRYPT AND RETURN STRING HERE
	return std::string();
}

std::string Decrypter::Decrypt(std::vector<double> colors, std::vector<std::pair<double, double> > points, char *keyToUse)
{
	Decrypter temp(keyToUse);
	return temp.Decrypt(colors, points);
}

#endif
