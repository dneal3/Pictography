#include "manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;

    // Encrypt a message
    manager.Encrypt();

    // Write data to .vtk file
    manager.WriteData(argv[1], argv[2]);

    // Write key to file
    manager.WriteKey();

    return 0;
}
