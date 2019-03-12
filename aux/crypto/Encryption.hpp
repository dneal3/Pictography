#ifndef Encryption_hpp
#define Encryption_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <functional>
#include <vector>

class Encryption
{
    std::string key;
    int rearrFactors[2];
    int numTriFactors[2];
    std::string dataToEncrypt;
    
    void FactorizeNum(int num);
    void generateKey(int oddeven);
    void RearrangePlain(void);
    void Factorize(void);
    
    public:
        Encryption(std::string data);
        std::vector<double> doEncryption();
        std::string getKey() {return key;};
        int* getFactors() {return rearrFactors;};
    
};

Encryption::Encryption(std::string data)
{
    dataToEncrypt = data;
    key = std::string("");
}

void Encryption::FactorizeNum(int num)
{
    int factors[256];
    int numFactors = 0;
    int index1, index2;
    for(int i = 1; i<=num; i++)
    {
        if(num % i == 0)
        {
            factors[numFactors] = i;
            numFactors++;
        }
    }
    
    index1 = rand() % (numFactors-1);
    index2 = (numFactors-1) - index1;
    
    numTriFactors[0] = factors[index1];
    numTriFactors[1] = factors[index2];
    
}



void Encryption::Factorize(void)
{
    int factors[256];
    int numFactors = 0;
    int index1, index2;
    int sizeOfPlain = dataToEncrypt.size();
    for(int i = 1; i<=sizeOfPlain; i++)
    {
        if(sizeOfPlain % i == 0)
        {
            factors[numFactors] = i;
            numFactors++;
        }
    }
    
    index1 = rand() % (numFactors-1);
    index2 = (numFactors-1) - index1;
    rearrFactors[0] = factors[index1];
    rearrFactors[1] = factors[index2];
    
}

void Encryption::RearrangePlain(void)
{
    std::string newString;
    int index;
    int rows = rearrFactors[0];
    int columns = rearrFactors[1];
    
    for(int i=0; i<rows; i++)
    {
        for(int j = 0; j<columns; j++)
        {
            index = (i)+(rows*j);
            newString+=dataToEncrypt[index];
        }
    }
    dataToEncrypt = newString;
}

void Encryption::generateKey(int oddOrEven)
{
    int newChar;
    
    int keylength = 128;
    
    if(!oddOrEven) // when it's even
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i)
            {
                    
                case 0:
                    key += std::to_string(oddOrEven);
                    break;
                default:
                    newChar = ((rand() % 9) + 1);
                    key += std::to_string(newChar);
                    break;
            }
        }
    }
    else if(oddOrEven) // when it's odd
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i) //puts the information in the right place
            {
                    
                case 0:
                    key += std::to_string(oddOrEven);
                    break;
                    
                default:
                    newChar = ((rand() % 9) + 1);
                    key += std::to_string(newChar);
                    break;
            }
        }
    }
    // temporary placement of string rearrangement factors
    key[1] = std::to_string((rearrFactors[0])/100)[0];
    key[2] = std::to_string((rearrFactors[0]/10)%10)[0];
    key[3] = std::to_string((rearrFactors[0]) % 10)[0];
    key[4] = std::to_string((rearrFactors[1])/100)[0];
    key[5] = std::to_string(((rearrFactors[1])/10) % 10)[0];
    key[6] = std::to_string((rearrFactors[1]) % 10)[0];
}




std::vector<double>  Encryption::doEncryption()
{
    srand(time(0));
    int numChars = dataToEncrypt.size();
    while(numChars % 9 != 0)
    {
        numChars++;
        dataToEncrypt += ' ';
    }
    
    Factorize();
    RearrangePlain();
    int numColors = numChars * 3;
    std::vector<double> newColors(numColors);
    
    int c = 0;
    int oddOrEven = (rand() % 2);
    int offsetr = (rand() % (99))+1;
    int offsetg = (rand() % (99-offsetr))+1;
    int offsetb = 100 - (offsetr + offsetg);
    
    
    double ratior = offsetr * .01;
    double ratiog = offsetg * .01;
    double ratiob = offsetb * .01;
    
    if(!oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            // is even
            // 0  1  2  3  4  5  6  7  8
            // R1 R2 R3 G3 G1 G2 B2 B3 B1
            int colorindex = c * 9;
 
            newColors[colorindex] =   (dataToEncrypt[i]) * ratior;
            newColors[colorindex+4] = (dataToEncrypt[i]) * ratiog;
            newColors[colorindex+8] = (dataToEncrypt[i]) * ratiob;
            
            newColors[colorindex+1] = (dataToEncrypt[i+1]) * ratior;
            newColors[colorindex+5] = (dataToEncrypt[i+1]) * ratiog;
            newColors[colorindex+6] = (dataToEncrypt[i+1]) * ratiob;
            
            newColors[colorindex+2] = (dataToEncrypt[i+2]) * ratior;
            newColors[colorindex+3] = (dataToEncrypt[i+2]) * ratiog;
            newColors[colorindex+7] = (dataToEncrypt[i+2]) * ratiob;
            c++;
        }
        
    }
    else if(oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            // is odd
            // 0  1  2  3  4  5  6  7  8
            // R2 R3 R1 G1 G2 G3 B3 B1 B2
            int colorindex = c * 9;
            
            newColors[colorindex+2] = (dataToEncrypt[i]) * ratior;
            newColors[colorindex+3] = (dataToEncrypt[i]) * ratiog;
            newColors[colorindex+7] = (dataToEncrypt[i]) * ratiob;
            
            newColors[colorindex] =   (dataToEncrypt[i+1]) * ratior;
            newColors[colorindex+4] = (dataToEncrypt[i+1]) * ratiog;
            newColors[colorindex+8] = (dataToEncrypt[i+1]) * ratiob;
            
            newColors[colorindex+1] = (dataToEncrypt[i+2]) * ratior;
            newColors[colorindex+5] = (dataToEncrypt[i+2]) * ratiog;
            newColors[colorindex+6] = (dataToEncrypt[i+2]) * ratiob;
            c++;
        }
    }
    
    // Need to shift colors using the same operations as plaintext
    FactorizeNum(numColors);
    int index;
    int rows = numTriFactors[0];
    int columns = numTriFactors[1];

    generateKey(oddOrEven);
    key[122] = std::to_string((numTriFactors[0])/100)[0];
    key[123] = std::to_string(((numTriFactors[0])/10)%10)[0];
    key[124] = std::to_string((numTriFactors[0]) % 10)[0];
    key[125] = std::to_string((numTriFactors[1])/100)[0];
    key[126] = std::to_string(((numTriFactors[1])/10) % 10)[0];
    key[127] = std::to_string((numTriFactors[1]) % 10)[0];

// Decrypt here down
// Have key and triangle set
// Before iterating through triangles in Decryption, at line 66,
// Iterate through colors of triangles and subtract shiftedColors[i] ~line 270
// Two factors, for key [122] through key[127]
    std::vector<double> shiftedColors(numColors);;
    c = 0;
    for(int i=0; i<rows; i++)
    {
        for(int j = 0; j<columns; j++)
        {
            index = (i)+(rows*j);
            shiftedColors[c] =  newColors[index];
            c++;
        }
    }
    
    
    for(int i = 0; i<numColors; i++)
    {
        shiftedColors[i] = ((shiftedColors[i] + (key[(i%127)]))/255);
    }


    return shiftedColors;
}

#endif /* Encryption_hpp */
