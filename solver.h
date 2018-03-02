#ifndef SOLVER_H
#define SOLVER_H
#include "storage.h"
#include <vector>
#include <iostream>


class Solver
{
public:
	Solver();
	int unassigned(std::vector<_variable> vars, std::vector<_constraint_touple> touples);
	bool is_valid(int value, _variable var, std::vector<_constraint_touple> touples);
	bool copy_to_assign(std::vector<_variable> vars);
	std::vector<int> return_assign();
	bool backtrack(std::vector<_variable> vars, std::vector<_constraint_touple> touples);
	bool is_solved();
	bool is_consistant(int value, int position, std::vector<_variable> vars, std::vector<_constraint_touple> touples);
	int get_assignment(std::vector<_variable> variables, int x);
private:
	std::vector<int> assign;
	bool copied;
	bool solved;
};
#endif