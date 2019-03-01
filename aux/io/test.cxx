#include "DataWriter.h"
#include "DataReader.h"
int main()
{
	DataReader::Read("garbage");
	cerr << "ran successfully" << endl;
}
