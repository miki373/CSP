#include "generator.h"
#include <iostream>

#include <cmath>
using namespace std;


int main()
{
	Generator generate;

	generate.setAlpha(.2);
	generate.setN(15);
	generate.setR(0.3);
	generate.setP(0.1);
	//cout << generate.calc_constraints() << endl;
	
	generate.create();
	


	return 0;
}