#ifndef SOLVER_H
#define SOLVER_H
#include "storage.h"
#include <vector>


class Solver
{
public:
	Solver();
	int unassigned(std::vector<_variable> vars, std::vector<_constraint_touple> touples);
	bool is_valid(int value, _variable var, std::vector<_constraint_touple> touples);
	

private:
	std::vector<int> assign;
};
#endif