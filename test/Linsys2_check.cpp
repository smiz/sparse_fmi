#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

int main()
{
	double e1max = 0.0, e2max = 0.0;
	string line;
	double t, x1, x2, dx1, dx2, A11, A12, A21, A22;
	ifstream fin("Linsys2.dat");
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
   		stringstream( val ) >> x1;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> x2;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> dx1;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> dx2;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> A11;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> A12;}
		{string val;
    		getline( ss, val,',');
   		stringstream( val ) >> A21;}
		{string val;
    		getline( ss, val);
   		stringstream( val ) >> A22;}
		if (count > 0){
			e1max = ::max(e1max,fabs(x1-1.0*exp(-0.5*t)));
			e2max = ::max(e2max,fabs(x2-2.0*exp(-1.0*t)));
		}				
	}
	fin.close();
	cerr << "error: " << e1max << " " << e2max << endl;
	if (e1max > 1E-3 || e2max > 1E-3) cerr << "Linsys2 FAILED" << endl;
	else cerr << "Linsys2 PASSED" << endl;
}

