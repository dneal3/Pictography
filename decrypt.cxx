#include "manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;

    // Read data from .vtk file and generate image
    manager.ReadData(argv[1], argv[2], argv[3]);

    // Decrypt .vtk file
    manager.Decrypt(argv[1]);

    return 0;
}
