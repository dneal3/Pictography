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
    std::string dataToEncrypt;
    
    void generateKey(int oddeven);
    void RearrangePlain(void);
    void Factorize(void);
    
    public:
        Encryption(void);
        Encryption(std::string data);
        double* doEncryption();
        std::string getKey() {return key;};
        int* getFactors() {return rearrFactors;};
    
};

#endif /* Encryption_hpp */
