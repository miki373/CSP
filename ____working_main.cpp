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

	cout << "Generating CSP...\n";
	constreaints = generate.return_csp();
	var = generate.return_var();
	generate.print();

	do{
		cout << "AC Arch consistancy yes [1] no [0]"; cin >> ac;
	} while (ac < 0 || ac >1);

	if (ac)
	{
		int continue_to_test;
		int ac_resoult = solve.ac(var, constreaints);
		if (!ac_resoult)
		{
			cout << "AC: No solution.\n";
		}
	}


	do{
	cout << "Choose algorithm\n[1] BT Standart Backtracking\n[2] FC Forward Checking\n[3] FLA Full Look Ahead\n"; cin >> choice;
	} while (choice < 1 || choice > 3);	
	// start timer
	s_time = clock();

	solve.backtrack(var, constreaints, choice);
	
	e_time = clock();
	t_time = (e_time - s_time) / CLOCKS_PER_SEC;


	if (solve.is_solved())
	{
		assignments = solve.return_assign();
		cout << "\nSolution:\n";
		for (unsigned int i = 0; i < assignments.size(); i++)
		{
			cout << "x" << i << " " << assignments[i] << endl;
		}
	}
	else
	{
		cout << "No solution\n";
	}


	cout << "Search took: " << t_time << endl;
	// end timer



	
	



	





	
	

	

	
	
	

	
	


	return 0;
}

