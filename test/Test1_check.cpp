#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
	double emax = 0.0;
	char line[1000];
	double t, x, dx, a;
	ifstream fin("Test1.dat");
	fin.getline(line,999);
	while (true)
	{
		fin >> t >> x >> dx >> a;
		if (!fin.eof())
		{
			emax = ::max(emax,fabs(x-1.0*exp(-1.0*t)));
		}
		else break;
	}
	fin.close();
	cerr << "error: " << emax << endl;
	if (emax > 1E-3) cerr << "Test1 FAILED" << endl;
	else cerr << "Test1 PASSED" << endl;
}
