//
//  Encryption.hpp
//  
//
//  Created by Derrick Neal on 2/14/19.
//

#ifndef Encryption_hpp
#define Encryption_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

class Encryption
{
    std::string key;
    int numColors; // for debugging
    std::string dataToEncrypt;
    double* colors;
    
    std::string generateKey(int offsetr, int offsetg, int offsetb, int oddeven); //Might want to return key and just use it in doEncryption.
    public:
        Encryption(void);
        Encryption(std::string data);
        ~Encryption();
        double* doEncryption();
        std::string getKey() {return this->key;};
        int getNumColors() {return this->numColors;};
    
};

#endif /* Encryption_hpp */
