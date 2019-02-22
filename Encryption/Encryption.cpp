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
Encryption::Encryption(char* data)
{
    this->dataToEncrypt = data;
}

//Standard Destructor deletes
Encryption::~Encryption(void)
{
    delete this->colors;
}


char* Encryption::generateKey(int offsetr, int offsetg, int offsetb, int oddOrEven)
{
    srand(time(0));
    // do operations on the dataToEncrypt to decide how to make the key
    //determine odd or even using rand?
    int newChar;
    char buffer[2];
    
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
    printf("key length %d\n", keylength);
    char* keyString = new char[keylength+1];
    
    if(oddOrEven) // when it's even
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i)
            {
                case 0:
                    keyString[i] = (oddOrEven+32) + '0';
                    break;
                case 3:
                    //printf("%c\n", offsetr+'0');
                    //sprintf(buffer, "%c", (char)offsetr);
                    //printf("%c\n", buffer[0]);
                    keyString[i] = offsetr+'0';
                    break;
                
                case 10:
                    //sprintf(buffer, "%c", (char)offsetg);
                    keyString[i] = offsetg+'0';
                    break;
                    
                case 15:
                    //sprintf(buffer, "%c", (char)offsetb);
                    keyString[i] = offsetb + '0';
                    break;
                    
                default:
                    newChar = (rand() % 32) + 32; // made it look more natural
                    //printf(buffer, "%c", (char)newChar);
                    keyString[i] = newChar + '0';
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
                case 0:
                    keyString[i] = (oddOrEven+32) + '0';
                    break;

                case 5:
                    //sprintf(buffer, "%c", (char)offsetg);
                    keyString[i] = offsetg + '0';
                    break;
                    
                case 13:
                    //sprintf(buffer, "%c", (char)offsetr);
                    keyString[i] = offsetr + '0';
                    break;
                            
                case 16:
                    //sprintf(buffer, "%c", (char)offsetb);
                    keyString[i] = offsetr + '0';
                    break;
                            
                default:
                    newChar = (rand() % 95) + 32;
                    //sprintf(buffer, "%d", newChar);
                    keyString[i] = newChar + '0';
                    break;
            }
        }
    }
    return keyString;
}

   
    

void Encryption::doEncryption()
{
    srand(time(0));
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
    
    printf("oddOrEven is %d\n", oddOrEven);
    printf("offsetr, %d\n", offsetr);
    printf("offsetg, %d\n", offsetg);
    printf("offsetb, %d\n", offsetb);
    
    double ratior = offsetr * .01;
    double ratiog = offsetg * .01;
    double ratiob = offsetb * .01;
    
    printf("ratior, %f\n", ratior);
    printf("ratiog, %f\n", ratiog);
    printf("ratiob, %f\n", ratiob);
    
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
    printf("%s\n", this->key);
    
    
    //return key?

    
}

int main(int argc, char* argv[])
{
    Encryption encryp;
    encryp.doEncryption();
    
    char* keysmurf = encryp.getKey();
    
    int oddOrEvenFlag = (keysmurf[0] - '0') - 32;
    printf("odd or even %d\n", oddOrEvenFlag);
    
    
    
    return 0;
}
