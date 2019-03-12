#include "manager.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
	std::cout << "USAGE ERROR\nUsage: ./decryption filename.vtk key" << std::endl;
	return 1;
    }
    // Create a manager for the program
    Manager manager;

    // Read data from .vtk file and generate image
    manager.ReadData(argv[1], argv[2]);

    // Decrypt .vtk file
    manager.Decrypt();

    return 0;
}
