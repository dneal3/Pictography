#include "DataWriter.h"
using namespace std;
int main(void)
{
	DataWriter w;
	vector<double> c;
	vector<pair<double, double> >pts = {{0,0}, {1,0}, {1,1}, {0,1}, {0,0}, {1,0}, {1,1}, {0,1}, {1,1}};
	const char * fn = "output";
	w.write(c, pts, fn);
}
