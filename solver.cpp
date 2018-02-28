#include "solver.h"
Solver::Solver()
{
	copied = false;
	solved = false;
}

// Return most constrained variable position in array
// Using integer to save resources
int Solver::unassigned(std::vector<_variable> vars, std::vector<_constraint_touple> touples)
{
	int pos = -1;
	int pos_num_constrained = -1;
	int temp_pos = -1;
	int num_constrained = -1;
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		if (vars[i].assignment != UNASSIGNED)
		{
			continue;
		}
		else
		{
			temp_pos = i;
		}
		// GET NUMBER OF CONSTRAINT
		num_constrained = 0;
		for (unsigned int k = 0; k < touples.size(); k++)
		{
			if ((vars[i].var == touples[k].x.var) || vars[i].var == touples[k].y.var)
			{
				num_constrained += 1;
			}
		}
		if (pos_num_constrained <= num_constrained)
		{
			pos_num_constrained = num_constrained;
			pos = temp_pos;
		}
	}
	return pos;
}

// checks if given value is compatable with constraints placed upon this variable
// true if compatable
// else if not
bool Solver::is_valid(int value,_variable var, std::vector<_constraint_touple> touples)
{
	for (unsigned int i = 0; i < touples.size(); i++)
	{
		if (var.var == touples[i].x.var)
		{
			for (unsigned int k = 0; k < touples[i].constraints.size(); k++)
			{
				int x = touples[i].constraints[k].x;
				if (value == x)
				{
					return false;
				}
			}
		}
		else if (var.var == touples[i].y.var)
		{
			for (unsigned int k = 0; k < touples[i].constraints.size(); k++)
			{
				int y = touples[i].constraints[k].y;
				if (value == y)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Solver::copy_to_assign(std::vector<_variable> vars)
{
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		if (vars[i].assignment == -1)
		{
			vars[i].assignment = 0;
		}
		assign.push_back(vars[i].assignment);
	}
	copied = true;
	return true;
}

std::vector<int> Solver::return_assign()
{
	return assign;
}

bool Solver::backtrack(std::vector<_variable> vars, std::vector<_constraint_touple> touples)
{
	// base case
	// if all are assigned store assignments and return true
	if (unassigned(vars, touples) == -1)
	{
		copy_to_assign(vars);
		solved = true;
		return true;
	}

	// recursive case

	int next_unassigned_var_position = unassigned(vars, touples);
	int value_of_var;
	bool assigned = false;
	bool good_below = false;
	for (unsigned int i = 0; i < vars[next_unassigned_var_position].domain.size(); i++)
	{
		value_of_var = vars[next_unassigned_var_position].domain[i];
		if (is_valid(value_of_var, vars[next_unassigned_var_position], touples))
		{
			vars[next_unassigned_var_position].assignment = value_of_var;
			assigned = true;
			assigned = backtrack(vars, touples);
			if (assigned)
			{
				break;
			}
		}
	}
	if (!assigned)
		return false;	
}


bool Solver::is_solved()
{
	return solved;
}