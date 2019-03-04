#include "Manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;

    // Encrypt a message
    manager.Encrypt();

    // Write data to .vtk file
    manager.WriteData();

    // Read data from .vtk file and generate image
    manager.Rasterize();

    manager.Decrypt();

    return 0;
}
