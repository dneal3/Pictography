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
    char* key;
    std::string dataToEncrypt;
    double* colors;
    
    char* generateKey(int offsetr, int offsetg, int offsetb, int oddeven); //Might want to return key and just use it in doEncryption.
    public:
        Encryption(void);
        Encryption(char* data);
        ~Encryption();
        void doEncryption();
        char* getKey() {return this->key;};
    
};

#endif /* Encryption_hpp */
