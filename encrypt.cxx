#include "manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;
    std::string toEncrypt(argv[3]);
    // Encrypt a message
	std::cerr << "encrypting:\n" << toEncrypt << std::endl;
    manager.Encrypt(toEncrypt);

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
