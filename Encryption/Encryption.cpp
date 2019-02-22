//
//  Encryption.cpp
//  
//
//  Created by Derrick Neal on 2/14/19.
//

#include "Encryption.hpp"

//Define Encryption Methods

//Constructor 1 without data given
Encryption::Encryption(void)
{
    //ask for user input to get the string to decrpyt
    std::string userData;
    char isCorrect;
    std::cout << "Please enter the phrase you like to encrypt: " << std::endl;
    std::cin >> userData;
    std::cout << "The phrase you just entered was " << userData << std::endl;
    std::cout << "Is this correct (y/n)" << std::endl;
    std::cin >> isCorrect;
    if(isCorrect == 'n')
    {
        std::cout << "Please re-enter the phrase you like to encrypt: " << std::endl;
        std::cin >> userData;
        std::cout << "The phrase you just entered was " << userData << std::endl;
        std::cout << "Is this correct (y/n)" << std::endl;
        std::cin >> isCorrect;
    }
    
    this->dataToEncrypt = userData;
}

//Constructor 2 with data given
Encryption::Encryption(std::string data)
{
    this->dataToEncrypt = data;
}

//Standard Destructor deletes
Encryption::~Encryption(void)
{
    delete this->colors;
}


std::string Encryption::generateKey(int offsetr, int offsetg, int offsetb, int oddOrEven)
{
    // do operations on the dataToEncrypt to decide how to make the key
    //determine odd or even using rand?
    int newChar;
    char buffer[2];
    std::string keyString;
    
    // key will be 32 bits
    //if even
    //offsetr will be at index[3]
    //offsetg will be at index[10]
    //offsetb will be at index[15] doesnt neccessarily need to be included as it can be infered
    
    //if odd
    //offsetr will be at index[13]
    //offsetg will be at index[5]
    //offsetb will be at index[16]

    // how to determine other values
    int keylength = (rand() % (17)) + 16; // different sized keys! 32-64
    
    if(oddOrEven) // when it's even
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i)
            {
                case 3:
                    sprintf(buffer, "%d", offsetr);
                    keyString.append(buffer);
                    break;
                
                case 10:
                    sprintf(buffer, "%d", offsetg);
                    keyString.append(buffer);
                    break;
                    
                case 15:
                    sprintf(buffer, "%d", offsetb);
                    keyString.append(buffer);
                    break;
                    
                default:
                    newChar = (rand() % 95) + 32;
                    sprintf(buffer, "%d", newChar);
                    keyString.append(buffer);
                    break;
            }
        }
    }
    else if(!oddOrEven) // when it's even
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i) //puts the information in the right place
            {
                case 5:
                    sprintf(buffer, "%d", offsetg);
                    keyString.append(buffer[0], 1);
                    break;
                    
                case 13:
                    sprintf(buffer, "%d", offsetr);
                    keyString.append(buffer[0], 1);
                    break;
                            
                case 16:
                    sprintf(buffer, "%d", offsetb);
                    keyString.append(buffer[0], 1);
                    break;
                            
                default:
                    newChar = (rand() % 95) + 32;
                    sprintf(buffer, "%d", newChar);
                    keyString.append(buffer[0], 1);
                    break;
            }
        }
    }
    return keyString;
}

   
    

void Encryption::doEncryption()
{
    int numChars = this->dataToEncrypt.size();
    if(numChars % 3 == 2)
    {
        numChars++;
        this->dataToEncrypt += ' ';
    }
    else if(numChars % 3 == 1)
    {
        numChars+=2;
        this->dataToEncrypt += ' ';
        this->dataToEncrypt += ' '; //this might not work
        
    }
    
    int numColors = numChars * 3; //numchars * 3 so we have 3 color channels per char
    
    this->colors = new double[numChars+1];
    
    //offsetr r = rand() mod 100
    //offsetg g = rand() mod (100-r)
    //offsetb b = 100 - (r+g)
    
    int oddOrEven = (rand() % 2); // decide if odd or even
    int offsetr = (rand() % (100));// rand value between 32 and 99
    int offsetg = (rand() % (100-offsetr));
    int offsetb = 100 - (offsetr + offsetg);
    
    double ratior = offsetr/100;
    double ratiog = offsetg/100;
    double ratiob = offsetb/100;
    
    if(oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            //in the picture we drew dots were V1,
            // 0  1  2  3  4  5  6  7  8
            // R1 R2 R3 G3 G1 G2 B3 B2 B1
            int colorindex = i * 9;
            
            this->colors[colorindex] = atoi(&(this->dataToEncrypt[i])) * offsetr;
            this->colors[colorindex+4] = atoi(&(this->dataToEncrypt[i])) * offsetg;
            this->colors[colorindex+8] = atoi(&(this->dataToEncrypt[i])) * offsetb;
            
            this->colors[colorindex+1] = atoi(&(this->dataToEncrypt[i+1])) * offsetr;
            this->colors[colorindex+5] = atoi(&(this->dataToEncrypt[i+1])) * offsetg;
            this->colors[colorindex+7] = atoi(&(this->dataToEncrypt[i+1])) * offsetb;
            
            this->colors[colorindex+2] = atoi(&(this->dataToEncrypt[i+2])) * offsetr;
            this->colors[colorindex+3] = atoi(&(this->dataToEncrypt[i+2])) * offsetg;
            this->colors[colorindex+6] = atoi(&(this->dataToEncrypt[i+2])) * offsetb;
        }
        
    }
    else if(!oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            // 0  1  2  3  4  5  6  7  8
            // R2 R3 R1 G1 G2 G3 B3 B1 B2
            int colorindex = i * 9;
            
            this->colors[colorindex+2] = atoi(&(this->dataToEncrypt[i])) * offsetr;
            this->colors[colorindex+3] = atoi(&(this->dataToEncrypt[i])) * offsetg;
            this->colors[colorindex+7] = atoi(&(this->dataToEncrypt[i])) * offsetb;
            
            this->colors[colorindex] = atoi(&(this->dataToEncrypt[i+1])) * offsetr;
            this->colors[colorindex+4] = atoi(&(this->dataToEncrypt[i+1])) * offsetg;
            this->colors[colorindex+8] = atoi(&(this->dataToEncrypt[i+1])) * offsetb;
            
            this->colors[colorindex+1] = atoi(&(this->dataToEncrypt[i+2])) * offsetr;
            this->colors[colorindex+5] = atoi(&(this->dataToEncrypt[i+2])) * offsetg;
            this->colors[colorindex+6] = atoi(&(this->dataToEncrypt[i+2])) * offsetb;
        }
        
    }
    
    
    this->key = this->generateKey(offsetr, offsetg, offsetb, oddOrEven);
    printf("%s\n", this->key.c_str());
    
    
    //return key?

    
}

int main(void)
{
    Encryption encryp;
    
    encryp.doEncryption();
    
    return 0;
}
