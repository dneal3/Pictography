#include "DataWriter.h"
using namespace std;
int main(void)
{
	DataWriter w;
	vector<double> c = {1.0, 0.3, 0.8, 1.5, 0.7, 1.9, 0.7, 0.12345, 0.663};
	vector<pair<double, double> >pts = {{0,0}, {1,0}, {1,1}, {0,1}, {0,0}, {1,0}, {1,1}, {0,1}, {1,1}};
	const char * fn = "output";
	w.write(c, pts, fn);
}
