#include "Manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;

    // Encrypt a message
    manager.Encrypt();

    // Write data to .vtk file
    manager.WriteData(argv[1], argv[2]);

    return 0;
}
