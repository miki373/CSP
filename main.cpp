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
	/*
	vector<_constraint_touple> constreaints;
	vector<_variable> var;
	vector<int> assignments;
	// User input
	int n, choice, ac;
	double p, alpha, r;
	// Timing
	clock_t s_time, e_time, t_time;

	generate.setN(5);
	generate.setP(0.3);
	generate.setAlpha(.7);
	generate.setR(0.8);
	generate.create();
	generate.print();
	constreaints = generate.return_csp();
	var = generate.return_var();

	cout << "Domain: \n";
	for (unsigned int i = 0; i < var[0].domain.size(); i++)
	{
		cout << var[0].domain[i] << endl;
	}
	*/


	
	_constraint_touple constraint;
	_variable x;
	_variable y;


	x.domain.push_back(0);
	x.domain.push_back(1);
	x.domain.push_back(2);
	
	y.domain.push_back(0);
	y.domain.push_back(1);
	y.domain.push_back(2);

	constraint.x = x;
	constraint.y = y;

	_constraint_values values;

	values.x = 0;
	values.y = 0;
	constraint.constraints.push_back(values);
	values.x = 0;
	values.y = 1;
	constraint.constraints.push_back(values);
	values.x = 0;
	values.y = 2;
	constraint.constraints.push_back(values);

	values.x = 1;
	values.y = 0;
	constraint.constraints.push_back(values);
	values.x = 1;
	values.y = 1;
	constraint.constraints.push_back(values);
	values.x = 1;
	values.y = 2;
	constraint.constraints.push_back(values);


	values.x = 1;
	values.y = 0;
	constraint.constraints.push_back(values);
	values.x = 1;
	values.y = 1;
	constraint.constraints.push_back(values);
	values.x = 1;
	values.y = 2;
	constraint.constraints.push_back(values);

	solve.revise(constraint, x, y);

	for (int i = 0; i < x.domain.size(); i++)
	{
		cout << x.domain[i] << ' ';
	}




















	/*

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

	*/
	
	

	
	

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

