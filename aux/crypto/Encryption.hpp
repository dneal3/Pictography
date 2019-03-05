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
#include <functional>

class Encryption
{
    std::string key;
    size_t plainHash;
    int rearrFactors[2];
    int numColors; // for debugging
    std::string dataToEncrypt;
    
    std::string generateKey(int offsetr, int offsetg, int offsetb, int oddeven);
    void RearrangePlain(void);
    void Factorize(void);
    
    public:
        Encryption(void);
        Encryption(std::string data);
        double* doEncryption();
        std::string getKey() {return this->key;};
        int getNumColors() {return this->numColors;};
    
};

#endif /* Encryption_hpp */
