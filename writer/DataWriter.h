#ifndef DATAWRITER
#define DATAWRITER
#include <iostream>
#include <vector>
class DataWriter
{
	public:
	DataWriter(void);
	void write(std::vector<double> colors, std::vector<std::pair<double, double> > pointsIn, const char *filename);
};

#endif
