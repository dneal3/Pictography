#include "manager.h"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
	std::cout << "USAGE ERROR\nUsage: ./encrypt filename.vtk imagename \"string to encrypt\"" << std::endl;
	return 1;
    }
    // Create a manager for the program
    Manager manager;
    std::string toEncrypt(argv[3]);
    // Encrypt a message
    manager.Encrypt(toEncrypt);

    // Write data to .vtk file
    manager.WriteData(argv[1], argv[2]);

    return 0;
}
