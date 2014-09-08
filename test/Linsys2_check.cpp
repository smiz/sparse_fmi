#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
	double e1max = 0.0, e2max = 0.0;
	char line[1000];
	double t, x1, x2, dx1, dx2, A11, A12, A21, A22;
	ifstream fin("Linsys2.dat");
	fin.getline(line,999);
	while (true)
	{
		fin >> t >> x1 >> x2 >> dx1 >> dx2 >> A11 >> A12 >> A21 >> A22;
		if (!fin.eof())
		{
			e1max = ::max(e1max,fabs(x1-1.0*exp(-0.5*t)));
			e2max = ::max(e2max,fabs(x2-2.0*exp(-1.0*t)));
		}
		else break;
	}
	fin.close();
	cerr << "error: " << e1max << " " << e2max << endl;
	if (e1max > 1E-3 || e2max > 1E-3) cerr << "Linsys2 FAILED" << endl;
	else cerr << "Linsys2 PASSED" << endl;
}
