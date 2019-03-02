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

//Constructor 1 without data given
Encryption::Encryption(void)
{
    //ask for user input to get the string to decrpyt
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
	this->colors = nullptr;
}

//Constructor 2 with data given
Encryption::Encryption(char* data)
{
    //this doesnt really work might just always need to have it input through std in
    //could do file reading...
    this->dataToEncrypt = data;
    this->colors = nullptr;
}

//Standard Destructor deletes
Encryption::~Encryption(void)
{
	if(this->colors != nullptr) delete this->colors;
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
    
    if(!oddOrEven) // when it's even
    {   
        for(int i = 0; i < keylength; i++)
        {   
            switch(i)
            {   
                case 0:
                    keyString[0] = (oddOrEven+32) + '0';
                    break;
                case 3:
                    //printf("%c\n", offsetr+'0');
                    //sprintf(buffer, "%c", (char)offsetr);
                    //printf("%c\n", buffer[0]);
                    keyString[3] = offsetr;
    
                    break;
    
                case 10:
                    //sprintf(buffer, "%c", (char)offsetg);
                    keyString[10] = offsetg;
                    break;
                        
                case 15: 
                    //sprintf(buffer, "%c", (char)offsetb);
                    keyString[15] = offsetb;
                    break;
                        
                default:
                    newChar = (rand() % 32) + 32; // made it look more natural
                    //printf(buffer, "%c", (char)newChar);
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

                case 5:
                    //sprintf(buffer, "%c", (char)offsetg);
                    keyString[5] = offsetg;
                    //printf("%c\n", keyString[5]);
                    break;
                        
                case 13: 
                    //sprintf(buffer, "%c", (char)offsetr);
                    keyString[13] = offsetr;
                    break;
                              
                case 16: 
                    //sprintf(buffer, "%c", (char)offsetb);
                    keyString[16] = offsetb;
                    break;
                default:
                    newChar = (rand() % 95) + 32; 
                    //sprintf(buffer, "%d", newChar);
                    keyString[i] = newChar;
                    break;
            }   
        }   
    }   
    return keyString;
}

double* Encryption::doEncryption() 
{ 
    srand(time(0)); 
    int numChars = this->dataToEncrypt.size(); 
    printf("num chars is %d\n", numChars); 
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
        
    printf("numChars after being made to mult of 3, %d\n", this->dataToEncrypt.size()); 
    std::cerr << "encrypting: \"" << dataToEncrypt << "\"" << std::endl;
        
    int numColors = numChars * 3; //numchars * 3 so we have 3 color channels per char 
    this->numColors = numColors; 
        
    double* Newcolors = new double[numColors+1]; 
        
    //offsetr r = rand() mod 100 
    //offsetg g = rand() mod (100-r)
    //offsetb b = 100 - (r+g)
    int c = 0;
    int oddOrEven = (rand() % 2); // decide if odd or even
    int offsetr = (rand() % (99))+1;// rand value between 32 and 99
    int offsetg = (rand() % (99-offsetr))+1;
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
     
     
    if(!oddOrEven) 
    {   
        for(int i = 0; i < numChars; i+=3) 
        {   
            //in the picture we drew dots were V1, 
            // 0  1  2  3  4  5  6  7  8 
            // R1 R2 R3 G3 G1 G2 B3 B2 B1 
            int colorindex = c * 9; 
             
            Newcolors[colorindex] = (double)(this->dataToEncrypt[i]) * ratior /100; 
            Newcolors[colorindex+4] = (this->dataToEncrypt[i]) * ratiog / 100; 
            Newcolors[colorindex+8] = (this->dataToEncrypt[i]) * ratiob / 100; 
            printf("(%f, %f, %f)\n", Newcolors[colorindex], Newcolors[colorindex+4], Newcolors[colorindex+8]); 
            Newcolors[colorindex+1] = (this->dataToEncrypt[i+1]) * ratior / 100; 
            Newcolors[colorindex+5] = (this->dataToEncrypt[i+1]) * ratiog / 100; 
            Newcolors[colorindex+6] = (this->dataToEncrypt[i+1]) * ratiob / 100; 
            printf("(%f, %f, %f)\n", Newcolors[colorindex+1], Newcolors[colorindex+5], Newcolors[colorindex+6]); 
             
            Newcolors[colorindex+2] = (this->dataToEncrypt[i+2]) * ratior / 100; 
            Newcolors[colorindex+3] = (this->dataToEncrypt[i+2]) * ratiog / 100; 
            Newcolors[colorindex+7] = (this->dataToEncrypt[i+2]) * ratiob / 100; 
            printf("(%f, %f, %f)\n", Newcolors[colorindex+2], Newcolors[colorindex+3], Newcolors[colorindex+7]); 
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
            Newcolors[colorindex+2] = (double)(this->dataToEncrypt[i]) * ratior / 100; 
            Newcolors[colorindex+3] = (this->dataToEncrypt[i]) * ratiog / 100; 
            Newcolors[colorindex+7] = (this->dataToEncrypt[i]) * ratiob / 100; 
            printf("(%f, %f, %f)\n", Newcolors[colorindex+2], Newcolors[colorindex+3], Newcolors[colorindex+7]); 
             
            Newcolors[colorindex] = (this->dataToEncrypt[i+1]) * ratior / 100; 
            Newcolors[colorindex+4] = (this->dataToEncrypt[i+1]) * ratiog / 100; 
            Newcolors[colorindex+8] = (this->dataToEncrypt[i+1]) * ratiob / 100; 
            printf("(%f, %f, %f)\n", Newcolors[colorindex], Newcolors[colorindex+4], Newcolors[colorindex+8]); 
             
            Newcolors[colorindex+1] = (this->dataToEncrypt[i+2]) * ratior / 100; 
            Newcolors[colorindex+5] = (this->dataToEncrypt[i+2]) * ratiog / 100;
            Newcolors[colorindex+6] = (this->dataToEncrypt[i+2]) * ratiob / 100;
            printf("(%f, %f, %f)\n", Newcolors[colorindex+1], Newcolors[colorindex+5], Newcolors[colorindex+6]); 
            c++;
        }   
    
    }   
    
    this->key = this->generateKey(offsetr, offsetg, offsetb, oddOrEven);
//    this->colors = Newcolors;
    printf("%s\n", this->key);

    return Newcolors;
}
#endif /* Encryption_hpp */
