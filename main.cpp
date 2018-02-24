#include "generator.h"
#include <iostream>

#include <cmath>
using namespace std;


int main()
{
	Generator generate;
	vector<_constraint_touple> constreaints;

	generate.setN(7);
	generate.setP(0.2);
	generate.setAlpha(.9);
	generate.setR(0.3);
	generate.create();
	generate.print();
	
	constreaints = generate.return_csp();
	cout << constreaints[1].x.var;


	return 0;
}