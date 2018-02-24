#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <iostream>
struct _constraint_values
{
	int x;
	int y;
};

struct _variable
{
	int var;
	std::vector<int> domain;
};

struct _constraint_touple
{
	_variable x;
	_variable y;
	std::vector<_constraint_values> constraints;
};

class Generator
{
public:
	Generator();
	bool setN(int);
	bool setP(double);
	bool setAlpha(double);
	bool setR(double);

	int getN();
	double getP();
	double getAlpha();
	double getR();

	int get_error(bool val = false);

	int calc_constraints();
	int calc_incompatables();
	int calc_domain();
	bool unique(int, int);
	bool create();
	

private:

	
	int n;
	double p;
	double alpha;
	double r;
	int number_variables;
	int number_constraints;
	int number_incompatables;
	int domain;
	int error;
	

	std::vector<_constraint_touple> constraint_touples;
	std::vector<_variable> variables;
};