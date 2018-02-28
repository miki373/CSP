#include "solver.h"
Solver::Solver()
{

}

// Return most constrained variable position in array
// Using integer to save resources
int Solver::unassigned(std::vector<_variable> vars, std::vector<_constraint_touple> touples)
{
	int pos = -1;
	int pos_num_constrained = -1;
	int temp_pos = -1;
	int num_constrained = -1;
	for (int i = 0; i < vars.size(); i++)
	{
		if (vars[i].assignment == UNASSIGNED)
		{
			temp_pos = i;
		}
		num_constrained = 0;
		for (int k = 0; k < touples.size(); k++)
		{
			if ((vars[i].var == touples[k].x.var) || vars[i].var == touples[k].y.var)
			{
				num_constrained += 1;
			}
		}
		if (pos_num_constrained < num_constrained)
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
	for (int i = 0; i < touples.size(); i++)
	{
		if (var.var == touples[i].x.var)
		{
			for (int k = 0; k < touples[i].constraints.size(); k++)
			{
				if (value == touples[i].constraints[k].x)
				{
					return false;
				}
			}
		}
		else if (var.var == touples[i].y.var)
		{
			for (int k = 0; k < touples[i].constraints.size(); k++)
			{
				if (value == touples[i].constraints[k].y)
				{
					return false;
				}
			}
		}
	}
	return true;
}
