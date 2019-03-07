#include "manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;

    // Encrypt a message
    manager.Encrypt("Hel");

    // Write data to .vtk file
	std::cerr << "argv[1] is " << argv[1] << std::endl;
	std::cerr << "address of argv[1] is " << &argv[1] << std::endl;
	std::cerr << "argv[2] is " << argv[2] << std::endl;
	std::cerr << "address of argv[2] is " << &argv[2] << std::endl;
    manager.WriteData(argv[1], argv[2]);

    // Write key to file
    manager.WriteKey();

    return 0;
}
