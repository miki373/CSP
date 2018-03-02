#include "solver.h"
Solver::Solver()
{
	copied = false;
	solved = false;
}

// Return most constrained variable (its position in vector) because that
// variable will theoretically fail first and reduce the depth of search
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



bool Solver::copy_to_assign(std::vector<_variable> vars)
{
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		/*if (vars[i].assignment == -1)
		{
			vars[i].assignment = 0;
		}*/
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
	
	for (unsigned int i = 0; i < vars[next_unassigned_var_position].domain.size(); i++)
	{
		value_of_var = vars[next_unassigned_var_position].domain[i];
		if (is_consistant(value_of_var, next_unassigned_var_position, vars, touples))
		{
			vars[next_unassigned_var_position].assignment = value_of_var;
			assigned = backtrack(vars, touples);
			if (assigned)
			{
				break;
			}
		}
	}
	if (!assigned)
	{
		return false;
	}
}


bool Solver::is_solved()
{
	return solved;
}

// checks if assignment is consistant with constraints
bool Solver::is_consistant(int proposed_value,int position, std::vector<_variable> variables, std::vector<_constraint_touple> touple)
{
	int other_value;
	for (unsigned int i = 0; i < touple.size(); i++)
	{
		// check if this variable is in constraints tuple x position
		if (variables[position].var == touple[i].x.var)
		{
			// value of other variable, in this case y
			// if unassigned, y will be -1
			other_value = get_assignment(variables, touple[i].y.var);

			for (unsigned int k = 0; k < touple[i].constraints.size(); k++)
			{
				// this proposed value violates constraints, return false
				if ((proposed_value == touple[i].constraints[k].x) && (other_value == touple[i].constraints[k].y))
				{
					return false;
				}
			}
		}//endif

		if (variables[position].var == touple[i].y.var)
		{
			other_value = get_assignment(variables, touple[i].x.var);

			for (unsigned int k = 0; k < touple[i].constraints.size(); k++)
			{
				if ((proposed_value == touple[i].constraints[k].y) && (other_value == touple[i].constraints[k].x))
				{
					return false;
				}
			}
		}// endif
	}//endfor

	return true;
}

// returns assignment of variable if there is any. 
int Solver::get_assignment(std::vector<_variable> vars, int x)
{
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		if (vars[i].var == x)
		{
			return vars[i].assignment;
		}
	}
	return -1;
}

// ac algorithm based on psudocode found in
// credit "Artificial Intellegence: A modern approach"
std::vector<_variable> Solver::ac(std::vector<_variable> vars, std::vector<_constraint_touple> constraints)
{
	std::queue<_constraint_touple> contraints_queue;
	_constraint_touple temp;

	// push all constraint into queue
	for (unsigned int i = 0; i < constraints.size(); i++)
	{
		contraints_queue.push(constraints[i]);
	}

	while (!contraints_queue.empty())
	{
		temp = contraints_queue.front();// get next time
		contraints_queue.pop();	// remove next item

	}
	return vars;
}

bool Solver::revise(_constraint_touple touple, _variable& xi, _variable& xj)
{
	bool revised = false;
	bool unsatisfied;
	
	for (unsigned int i = 0; i < xi.domain.size(); i++)
	{
		unsatisfied = false;
		for (unsigned int j = 0; j < xj.domain.size(); j++)
		{
			for (unsigned int k = 0; k < touple.constraints.size(); k++)
			{
				// check if exists compatable pair in domain
				if ((xi.domain[i] == touple.constraints[k].x) && (xj.domain[j] == touple.constraints[k].y))
				{
					unsatisfied = true;
					break;
				}
			}
			if (unsatisfied)
			{
				break;
			}
		}
		if (unsatisfied)
		{
			xi.domain.erase(xi.domain.begin() + i);
			--i;;
			revised = true;
		}

	}
	return revised;
}