#include "generator.h"
#include "solver.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <algorithm>
using namespace std;



int main()
{
	Generator generate;
	
	Solver solve;
	
	vector<_constraint_touple> constreaints;
	vector<_variable> var;
	vector<int> assignments;
	// User input
	int n, choice, ac;
	double p, alpha, r;
	// Timing
	clock_t s_time, e_time, t_time;

	generate.setN(11);
	generate.setP(0.7);
	generate.setAlpha(.8);
	generate.setR(0.7);
	generate.create();
	generate.print();
	constreaints = generate.return_csp();
	var = generate.return_var();


	

	//// variable 0
	//_variable x;
	//x.var = 0;
	//x.domain.push_back(0);
	//x.domain.push_back(1);
	//x.domain.push_back(2);
	//// variable 0 end //


	//// variable 1
	//_variable y;
	//y.var = 1;
	//y.domain.push_back(0);
	//y.domain.push_back(1);
	//y.domain.push_back(2);
	//// variable 1 end //

	//// variable 2
	//_variable z;
	//z.var = 2;
	//z.domain.push_back(0);
	//z.domain.push_back(1);
	//z.domain.push_back(2);


	//// create constraint 0 1
	//_constraint_values c1;
	//_constraint_values c2;
	//_constraint_values c3;
	//_constraint_values c4;
	//_constraint_values c5;
	//_constraint_values c6;

	//// (0 2)
	//c1.x = 0;
	//c1.y = 1;

	//// (0 2)
	//c2.x = 0;
	//c2.y = 2;

	//// (0 2)
	//c3.x = 0;
	//c3.y = 0;

	//// (0 2)
	//c4.x = 2;
	//c4.y = 0;

	//// (0 2)
	//c5.x = 1;
	//c5.y = 1;



	//// create constraint 0 2
	//_constraint_values d1;
	//_constraint_values d2;

	//d1.x = 1;
	//d1.y = 0;

	//d2.x = 2;
	//d2.y = 0;

	//// create constraint 1
	//_constraint_touple constraint1;
	//constraint1.x = x;
	//constraint1.y = y;
	//constraint1.constraints.push_back(c1);
	//constraint1.constraints.push_back(c2);
	//constraint1.constraints.push_back(c3);
	//constraint1.constraints.push_back(c4);
	//constraint1.constraints.push_back(c5);


	//// create constraint 2
	//_constraint_touple constraint2;
	//constraint2.x = x;
	//constraint2.y = z;
	//constraint2.constraints.push_back(d1);
	//constraint2.constraints.push_back(d2);


	//// push vars into vector 
	//var.push_back(x);
	//var.push_back(y);
	//var.push_back(z);

	//// push constraint into vector
	//constreaints.push_back(constraint1);
	//constreaints.push_back(constraint2);


	//// BEGIN SOLVER //////////////////////////////////////////////////////////////////////





	cout << "Domain: \n";
	for (unsigned int i = 0; i < var[0].domain.size(); i++)
	{
		cout << var[0].domain[i] << endl;
	}
	
	for (unsigned int i = 0; i < var.size(); i++)
	{
		cout <<"var " << var[i].var << ": ";
		for (unsigned int j = 0; j < var[i].domain.size(); j++)
		{
			cout << var[i].domain[j] << ' ';
		}
		cout << endl;
	}

	cout << "AC: " <<solve.ac(var, constreaints) << endl;
	


	cout << "\n AFTER \n";

	for (unsigned int i = 0; i < var.size(); i++)
	{
		cout << "var " << var[i].var << ": ";
		for (unsigned int j = 0; j < var[i].domain.size(); j++)
		{
			cout << var[i].domain[j] << ' ';
		}
		cout << endl;
	}
	





	
	solve.backtrack(var, constreaints);

	if (solve.is_solved())
	{
		assignments = solve.return_assign();
		cout << "Solution:\n";
		for (unsigned int i = 0; i < assignments.size(); i++)
		{
			cout << "x" << i << " " << assignments[i] << endl;
		}
	}
	else
	{
		cout << "No solution\n";
	}

	
	
	

	
	

	/*
	
	do{
		cout << "Enter n: "; cin >> n;
	} while (!generate.setN(n));
	do
	{
		cout << "Enter p: "; cin >> p;
	} while (!generate.setP(p));
	do{
		cout << "Enter alpha: "; cin >> alpha;
	} while (!generate.setAlpha(alpha));
	do{
		cout << "Enter r: "; cin >> r;
	} while (!generate.setR(r));
	cout << "Choose algorithm\n[1] BT Standart Backtracking\n[2] FC Forward Checking\n[3] FLA Full Look Ahead\n"; cin >> choice;
	cout << "AC Arch consistancy yes [1] no [0]"; cin >> ac;
	// start timer
	s_time = clock();
	e_time = clock();
	t_time = (e_time - s_time) / CLOCKS_PER_SEC;
	// end timer
	*/
	return 0;
}
