#include "manager.h"

int main(int argc, char* argv[])
{
    // Create a manager for the program
    Manager manager;
    std::string toEncrypt(argv[3]);
    // Encrypt a message
<<<<<<< Updated upstream
	std::cerr << "encrypting:\n" << toEncrypt << std::endl;
    manager.Encrypt(toEncrypt);
=======
    manager.Encrypt("The honey badger is the only species of the genus Mellivora. Although in the 1860s it was assigned to the badger subfamily, the Melinae, it is now generally agreed that it bears very few similarities to the Melinae. It is much more closely related to the marten subfamily, Mustelinae, but furthermore is assigned its own subfamily, Mellivorinae.[3] Differences between Mellivorinae and Melinae include differences in their dentition formulae. Though not in the same subfamily as the wolverines, which are a genus of large-sized and atypical Mustelinae, the honey badger can be regarded as another, analogous, form of outsized weasel or polecat.");
>>>>>>> Stashed changes

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
