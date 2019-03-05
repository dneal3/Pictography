//
//  Encryption.cpp
//  
//
//  Created by Derrick Neal on 2/14/19.
//

#include "Encryption.hpp"
#define TESTING 0

//Define Encryption Methods

//Constructor 1 without data given
Encryption::Encryption(void)
{
    //ask for user input to get the string to decrpyt only really for testing
    std::string userData;
    std::string isCorrect;
    std::cout << "Please enter the phrase you like to encrypt: " << std::endl;
    std::getline(std::cin, userData);
    std::cout << "The phrase you just entered was " << userData << std::endl;
    std::cout << "Is this phrase correct?(y/n)" << std::endl;
    std::getline(std::cin, isCorrect);
    while((isCorrect != "y") && (isCorrect != "n"))
    {
        std::cout << "The phrase you just entered was " << userData << std::endl;
        std::cout << "Please use only y or n to indicate if this is the phrase you entered.\n Is this phrase correct?(y/n)" << std::endl;
        std::getline(std::cin, isCorrect);

    }
    while(isCorrect != "y")
    {
        std::cout << "Please re-enter the phrase you like to encrypt: " << std::endl;
        std::getline(std::cin, userData);
        std::cout << "The phrase you just entered was " << userData << std::endl;
        std::cout << "Is this phrase correct?(y/n)" << std::endl;
        std::getline(std::cin, isCorrect);
        while((isCorrect != "y") && (isCorrect != "n"))
        {
            std::cout << "The phrase you just entered was " << userData << std::endl;
            std::cout << "Please use only y or n to indicate if this is the phrase you entered.\n Is this phrase correct?(y/n)" << std::endl;
            std::getline(std::cin, isCorrect);
        }
    }
    
    this->dataToEncrypt = userData;
}

//Constructor 2 with data given
Encryption::Encryption(std::string data)
{
    //this doesnt really work might just always need to have it input through std in
    //could do file reading...
    this->dataToEncrypt = data;
}



void Encryption::Factorize(void)
{
    srand(time(0));
    int factors[128];
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
            std::cout << "index is " << index << std::endl;
            std::cout << "newString is "<< newString << std::endl;
        }
    }
    dataToEncrypt = newString;
}

std::string Encryption::generateKey(int offsetr, int offsetg, int offsetb, int oddOrEven)
{
    srand(time(0));
    int newChar;
    char buffer[2];
    
    //if even
    //offsetr will be at index[3]
    //offsetg will be at index[10]
    //offsetb will be at index[15]
    
    //if odd
    //offsetr will be at index[13]
    //offsetg will be at index[5]
    //offsetb will be at index[16]

    // how to determine other values
    int keylength = 128;
    char* keyString = new char[keylength+1];
    
    if(!oddOrEven) // when it's even
    {
        for(int i = 0; i < keylength; i++)
        {
            switch(i)
            {
                
                case 0:
                    keyString[0] = (oddOrEven+32) + '0';
                    break;
                /*
                case 3:
                    keyString[3] = offsetr+'0';
                    break;
                
                case 10:
                    keyString[10] = offsetg+'0';
                    break;
                    
                case 15:
                    keyString[15] = offsetb + '0';
                    break;
                */
                default:
                    newChar = (rand() % 10);
                    keyString[i] = newChar;
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
                    keyString[0] = (oddOrEven+32) + '0';
                    break;
                /*
                case 5:
                    keyString[5] = offsetg + '0';
                    break;
                    
                case 13:
                    keyString[13] = offsetr + '0';
                    break;
                            
                case 16:
                    keyString[16] = offsetb + '0';
                    break;
                */
                default:
                    newChar = (rand() % 10);
                    keyString[i] = newChar;
                    break;
            }
        }
    }
    return std::string(keyString);
}

   
    

double* Encryption::doEncryption()
{
    srand(time(0));
    int numChars = this->dataToEncrypt.size();
    std::hash<std::string> hashPlain;
    plainHash = hashPlain(dataToEncrypt);
    Factorize();
    RearrangePlain();
    if(numChars % 3 == 2)
    {
        numChars++;
        this->dataToEncrypt += ' ';
    }
    else if(numChars % 3 == 1)
    {
        numChars+=2;
        this->dataToEncrypt += ' ';
        this->dataToEncrypt += ' ';
        
    }
    //decide if hash after adding padding, or not?
    //plainHash = hashPlain(dataToEncrypt);
    std::cout << "new data to encrypt " << dataToEncrypt << std::endl;
    int numColors = numChars * 3;
    this->numColors = numColors;
    
    double* Newcolors = new double[numColors+1];
    
    //offsetr r = rand() mod 100
    //offsetg g = rand() mod (100-r)
    //offsetb b = 100 - (r+g)
    
    int c = 0;
    int oddOrEven = (rand() % 2);
    int offsetr = (rand() % (100));
    int offsetg = (rand() % (100-offsetr));
    int offsetb = 100 - (offsetr + offsetg);
    
    
    double ratior = offsetr * .01;
    double ratiog = offsetg * .01;
    double ratiob = offsetb * .01;
    
    if(TESTING)
    {
        printf("oddOrEven is %d\n", oddOrEven);
     
        printf("offsetr, %d\n", offsetr);
        printf("offsetg, %d\n", offsetg);
        printf("offsetb, %d\n", offsetb);
        
        printf("ratior, %f\n", ratior);
        printf("ratiog, %f\n", ratiog);
        printf("ratiob, %f\n", ratiob);
    }
    
    if(!oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            //in the picture we drew dots were V1,
            // 0  1  2  3  4  5  6  7  8
            // R1 R2 R3 G3 G1 G2 B3 B2 B1
            int colorindex = c * 9;
            
            Newcolors[colorindex] = (this->dataToEncrypt[i]) * ratior;
            Newcolors[colorindex+4] = (this->dataToEncrypt[i]) * ratiog;
            Newcolors[colorindex+8] = (this->dataToEncrypt[i]) * ratiob;
            
            Newcolors[colorindex+1] = (this->dataToEncrypt[i+1]) * ratior;
            Newcolors[colorindex+5] = (this->dataToEncrypt[i+1]) * ratiog;
            Newcolors[colorindex+7] = (this->dataToEncrypt[i+1]) * ratiob;
            
            Newcolors[colorindex+2] = (this->dataToEncrypt[i+2]) * ratior;
            Newcolors[colorindex+3] = (this->dataToEncrypt[i+2]) * ratiog;
            Newcolors[colorindex+6] = (this->dataToEncrypt[i+2]) * ratiob;
            c++;
        }
        
    }
    else if(oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            // 0  1  2  3  4  5  6  7  8
            // R2 R3 R1 G1 G2 G3 B3 B1 B2
            int colorindex = c * 9;
            
            Newcolors[colorindex+2] = (this->dataToEncrypt[i]) * ratior;
            Newcolors[colorindex+3] = (this->dataToEncrypt[i]) * ratiog;
            Newcolors[colorindex+7] = (this->dataToEncrypt[i]) * ratiob;
            
            Newcolors[colorindex] = (this->dataToEncrypt[i+1]) * ratior;
            Newcolors[colorindex+4] = (this->dataToEncrypt[i+1]) * ratiog;
            Newcolors[colorindex+8] = (this->dataToEncrypt[i+1]) * ratiob;
            
            Newcolors[colorindex+1] = (this->dataToEncrypt[i+2]) * ratior;
            Newcolors[colorindex+5] = (this->dataToEncrypt[i+2]) * ratiog;
            Newcolors[colorindex+6] = (this->dataToEncrypt[i+2]) * ratiob;
            c++;
        }
        
    }
    
    this->key = this->generateKey(offsetr, offsetg, offsetb, oddOrEven);

    return Newcolors;
}

int main(int argc, char* argv[])
{
    Encryption encryp;
    double* colorBuffer;
    colorBuffer = encryp.doEncryption();

    if(TESTING)
    {
        std::string keysmurf = encryp.getKey();
        int colors = encryp.getNumColors();
        int oddOrEvenFlag = (keysmurf[0] - '0') - 32;
        for(int i=0; i<colors; i++)
        {
            printf("Color %d is %f\n", i, colorBuffer[i]);
        }
        if(!oddOrEvenFlag)
        {
            printf("%d\n", (keysmurf[0] - '0')-32);
            printf("%d\n", keysmurf[3] - '0');
            printf("%d\n", keysmurf[10] - '0');
            printf("%d\n", keysmurf[15] - '0');
        }
        else{
            printf("%d\n", (keysmurf[0] - '0')-32);
            printf("%d\n", keysmurf[5] - '0');
            printf("%d\n", keysmurf[13] - '0');
            printf("%d\n", keysmurf[16] - '0');
        }
    }

    
    
    return 0;
}
