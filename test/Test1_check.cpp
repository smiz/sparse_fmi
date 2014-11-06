#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

int main()
{
	double emax = 0.0;
	string line;
	double t, x, dx, a;
	ifstream fin("Test1.dat");
	int count = -1;
	while (getline(fin,line))
	{	
		count++;
		stringstream ss( line );
		{string val;
		getline(ss,val,',');
		stringstream( val ) >> t;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> x;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> dx;}
		{string val;
    		getline( ss, val );
   		stringstream( val ) >> a;}
		if (count > 0){
			emax = ::max(emax,fabs(x-1.0*exp(-1.0*t)));
		}				
	}
	fin.close();
	cerr << "error: " << emax << endl;
	if (emax > 1E-3) cerr << "Test1 FAILED" << endl;
	else cerr << "Test1 PASSED" << endl;
}
