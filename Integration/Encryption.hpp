#ifndef Encryption_hpp
#define Encryption_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

class Encryption
{
    char* key;
    int numColors;
    std::string dataToEncrypt;
    double* colors;
    
    char* generateKey(int offsetr, int offsetg, int offsetb, int oddeven); //Might want to return key and just use it in doEncryption.
    public:
        Encryption(void);
        Encryption(char* data);
        ~Encryption();
        double* doEncryption();
        char* getKey() {return this->key;};
        int getNumColors() {return this->numColors;};
    
};

#endif /* Encryption_hpp */