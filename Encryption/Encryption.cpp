//
//  Encryption.cpp
//  
//
//  Created by Derrick Neal on 2/14/19.
//

#include "Encryption.hpp"
#include <stdlib.h>

//Define Encryption Methods

//Constructor 1 without data given
Encryption::Encryption(void)
{
    //ask for user input to get the string to decrpyt
    String userData;
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
    
    this.dataToEncrypt = userData;
}

//Constructor 2 with data given
Encryption::Encryption(std::string data)
{
    std::string newData = strdup(data);
    this.dataToEncrypt = newData;
}

Encryption::~Encryption(void)
{
    delete this.dataToEncrypt;
    delete this.colors;
    delete this.key;
}

String Encryption::getKey()
{
    return this.key;
}

Encryption::generateKey(int offsetr, int offsetg, int offsetb, int oddOrEven)
{
    // do operations on the dataToEncrypt to decide how to make the key
    //determine odd or even using rand?
    int newChar;
    char buffer[2];
    string keyString;
    
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
                    itoa(offsetr, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                
                case 10:
                    itoa(offsetg, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                    
                case 15:
                    itoa(offsetb, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                    
                default:
                    newChar = (rand() % 95) + 32;
                    itoa(newChar, buffer, 10);
                    keyString.append(buffer[0]);
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
                    itoa(offsetg, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                    
                case 13:
                    itoa(offsetr, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                            
                case 16:
                    itoa(offsetb, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
                            
                default:
                    newChar = (rand() % 95) + 32;
                    itoa(newChar, buffer, 10);
                    keyString.append(buffer[0]);
                    break;
            }
        }
    }
}

   
    

Encryption::doEncryption(this)
{
    int numChars = this.dataToEncrypt.size();
    if(numChars % 3 == 2)
    {
        numChars++;
        this.dataToEncrypt += ' ';
    }
    else if(numChars % 3 == 1)
    {
        numChars+=2;
        this.dataToEncrypt += ' ';
        this.dataToEncrypt += ' '; //this might not work
        
    }
    
    int numColors = numChars * 3; //numchars * 3 so we have 3 color channels per char
    
    double this.colors = new double[numChars+1];
    
    int oddOrEven = (rand() % 2); // decide if odd or even
    int offsetr = (rand() % (100));// rand value between 32 and 99
    int offsetg = (rand() % (100-offsetr));
    int offsetb = 100 - (offsetr + offsetg);
    
    double ratior = offsetr/100;
    double ratiog = offsetg/100;
    double ratiob = offsetb/100;
    
    if(oddOrEven)
    {
        for(int i = 0; i < numChars; i++)
        {
            
        }
        
    }
    else if(!oddOrEven)
    {
        for(int i = 0; i < numChars; i++)
        {
            // three chars at once
            
        }
        
    }
    //make numColors mod 3 == 0 always prolly use a switch if it matters could init to -1 so you know the data isn't relevant
   
    
    
    //offsetr r = rand() mod 100
    //offsetg g = rand() mod (100-r)
    //offsetb b = 100 - (r+g)
    //offset could manipulate this
    
    //might want to return the Key so that QT can print it in the UI prolly just return in string format.
    
    // odd or even will change the way colors get added to vertices, like even is v1r = red1 , v2g = green1
    // look at picture on ur phone
    //oddoreven % 2 is triangle offset
    
    
    this.key = this.generateKey(offsetr, offsetg, offsetb, oddOrEven);
    
    //return key?

    
}

int main(void)
{
    return 0;
}
