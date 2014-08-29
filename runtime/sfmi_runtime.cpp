#include "sfmi_runtime.h"
#include <iostream>
#include <cassert>
using namespace std;
using namespace sfmi;

model_data::model_data(
	int num_reals,
	int num_ints,
	int num_strs,
	int num_bools,
	int num_events):
	Time(0),
	real_vars(new fmi2Real[num_reals]),
	int_vars(new fmi2Integer[num_ints]),
	bool_vars(new fmi2Boolean[num_bools]),
	str_vars(new string[num_strs]),
	pre_real_vars(new fmi2Real[num_reals]),
	pre_int_vars(new fmi2Integer[num_ints]),
	pre_bool_vars(new fmi2Boolean[num_bools]),
	pre_str_vars(new string[num_strs]),
	z(new fmi2Real[num_events])
{
}

void model_data::link(void* var, void(*func)(model_data*))
{
	_input_info[var].push_back(func);
}

void model_data::link(void(*func)(model_data*),void* var)
{
	_output_info[func].push_back(var);
}

void model_data::modify(void* var)
{
	_modified_vars.insert(var);
}

model_data::~model_data()
{
	delete [] real_vars;
	delete [] int_vars;
	delete [] bool_vars;
	delete [] str_vars;
	delete [] pre_real_vars;
	delete [] pre_int_vars;
	delete [] pre_bool_vars;
	delete [] pre_str_vars;
	delete [] z;
}

void model_data::update()
{
	while (!(_modified_vars.empty()))
    {
		// Get the variable that was modified
		set<void*>::iterator next_var = _modified_vars.begin();
		void* var = *next_var;
		// Remove it from the list of modified variables
		_modified_vars.erase(next_var);
		// Get the list of equations that have this variable as input
		map<void*,list<void (*)(model_data*)> >::iterator map_iter =
			_input_info.find(var);
		// If there are any such equations, recalculate them
		if (map_iter != _input_info.end())
		{
			// Get the list of equations
			list<void (*)(model_data*)>& eqns = (*map_iter).second;
			// Calculate each one
			list<void (*)(model_data*)>::iterator eqns_iter = eqns.begin();
			for (; eqns_iter != eqns.end(); eqns_iter++)
			{
				(*eqns_iter)(this);
				// Get the variables that are modified by this eqn and put them into the modified list
				map<void (*)(model_data*),list<void*> >::iterator map_iter_2 =
					_output_info.find(*eqns_iter);
				if (map_iter_2 != _output_info.end())
				{
					list<void*>& vars = (*map_iter_2).second;
					list<void*>::iterator var_iter = vars.begin();
					for (; var_iter != vars.end(); var_iter++)
						_modified_vars.insert(*var_iter);
				}
			}
		}
	}
}


// Functions from LAPACK
extern "C"
{
	int dgetrf_(long*,long*,double*,long*,long*,long*);
	int dgetrs_(char*,long*,long*,double*,long*,long*,double*,long*,long*);
};

/**
 * LAPACK wrappers
 */
void sfmi::GETRF(double* A, long size, long* p)
{
	long ok = 0;
	dgetrf_(&size,&size,A,&size,p,&ok);
	assert(ok==0);
}

void sfmi::GETRS(double* A, long size, long* p, double* B)
{
	long ok = 0;
	long nrhs = 1;
	char N = 'N';
	dgetrs_(&N,&size,&nrhs,A,&size,p,B,&size,&ok);
	assert(ok==0);
}

