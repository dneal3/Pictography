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
    
    dataToEncrypt = userData;
}

//Constructor 2 with data given
Encryption::Encryption(std::string data)
{
    //this doesnt really work might just always need to have it input through std in
    //could do file reading...
    dataToEncrypt = data;
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
        }
    }
    dataToEncrypt = newString;
}

void Encryption::generateKey(int oddOrEven)
{
    srand(time(0));
    int newChar;
    
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
    key[1] = std::to_string((rearrFactors[0])/100)[0];
    key[2] = std::to_string((rearrFactors[0]/10)%10)[0];
    key[3] = std::to_string((rearrFactors[0]) % 10)[0];
    key[4] = std::to_string((rearrFactors[1])/100)[0];
    key[5] = std::to_string(((rearrFactors[1])/10) % 10)[0];
    key[6] = std::to_string((rearrFactors[1]) % 10)[0];
    std::cout << "rearrfactor 0 " << rearrFactors[0] <<  std::endl;
    std::cout << "rearrfactor 1 " << rearrFactors[1] <<  std::endl;
    
    std::cout << "key 1 " << key[1] << std::endl;
    std::cout << "key 2 " << key[2] << std::endl;
    std::cout << "key 3 " << key[3] << std::endl;
    std::cout << "key 4 " << key[4] << std::endl;
    std::cout << "key 5 " << key[5] << std::endl;
    std::cout << "key 6 " << key[6] << std::endl;

    std::cout << key << std::endl;
}

   
    

double* Encryption::doEncryption()
{
    srand(time(0));
    int numChars = dataToEncrypt.size();
    std::hash<std::string> hashPlain;
    if(numChars % 3 == 2)
    {
        numChars++;
        dataToEncrypt += ' ';
    }
    else if(numChars % 3 == 1)
    {
        numChars+=2;
        dataToEncrypt += ' ';
        dataToEncrypt += ' ';
        
    }
    //decide if hash after adding padding, or not?
    std::cout << "new data to encrypt " << dataToEncrypt << std::endl;
    plainHash = hashPlain(dataToEncrypt);
    Factorize();
    RearrangePlain();
    int numColors = numChars * 3;
    
    double* newColors = new double[numColors+1];
    
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
    
    if(!oddOrEven)
    {
        for(int i = 0; i < numChars; i+=3)
        {
            //in the picture we drew dots were V1,
            // diffuse across triangles same sprial pattern
            // 0  1  2  3  4  5  6  7  8
            // R1 R2 R3 G3 G1 G2 B2 B3 B1
            int colorindex = c * 9;
            
            newColors[colorindex] = (dataToEncrypt[i]) * ratior;
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
            //diffuse mix up vertices
            // 0  1  2  3  4  5  6  7  8
            // R2 R3 R1 G1 G2 G3 B3 B1 B2
            int colorindex = c * 9;
            
            newColors[colorindex+2] = (dataToEncrypt[i]) * ratior;
            newColors[colorindex+3] = (dataToEncrypt[i]) * ratiog;
            newColors[colorindex+7] = (dataToEncrypt[i]) * ratiob;
            
            newColors[colorindex] = (dataToEncrypt[i+1]) * ratior;
            newColors[colorindex+4] = (dataToEncrypt[i+1]) * ratiog;
            newColors[colorindex+8] = (dataToEncrypt[i+1]) * ratiob;
            
            newColors[colorindex+1] = (dataToEncrypt[i+2]) * ratior;
            newColors[colorindex+5] = (dataToEncrypt[i+2]) * ratiog;
            newColors[colorindex+6] = (dataToEncrypt[i+2]) * ratiob;
            c++;
        }
        
    }
    
    generateKey(oddOrEven);
   
    //for colors
    //loop through the colors and offset colors by the values in the key. the casear cipher.
    //change the colors by the offsets given by the key.
    for(int i = 0; i<numColors; i++)
    {
        newColors[i] = newColors[i] + (key[(i%127)]);
        std::cout << "color " << i << " is " << newColors[i] << std::endl;
        //i believe this is actually fine, because while its adding the character value of every integer it should never be over 255 as the highest two values it could add together would be 126 (~) + 57 (9)
    }
    //maybe pass in actual colors that are multiplied by 255.0 this would make the offsetting easier could also take each number and divide it by 255.0 then add it to the number as a new offset, max add is 9/255 (0.035)
    // ask what the handling is for a number greater than 1.0 or rather 255

    return newColors;
}

int main(int argc, char* argv[])
{
    Encryption encryp("In designing security systems, it is wise to assume that the details of the cryptographic algorithm are already available to the attacker. This is known as Kerckhoffs\' principle — \"only secrecy of the key provides security\", or, reformulated as Shannon's maxim, \"the enemy knows the system\". The history of cryptography provides evidence that it can be difficult to keep the details of a widely used algorithm secret (see security through obscurity). A key is often easier to protect (it\'s typically a small piece of information) than an encryption algorithm, and easier to change if compromised. Thus, the security of an encryption system in most cases relies on some key being kept secret.");
    double* colorBuffer;
    colorBuffer = encryp.doEncryption();

    return 0;
}
