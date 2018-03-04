#include "solver.h"
Solver::Solver()
{
	copied = false;
	solved = false;
	w_ac = false;
	w_mac = false;
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


// copy variable assignments to assignments vector to be returned to user
bool Solver::copy_to_assign(std::vector<_variable> vars)
{
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		assign.push_back(vars[i].assignment);
	}
	copied = true;
	return true;
}

// returns assignment
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

// returns true if CSP is solver, false if no solution
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
		}

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
		}
	}

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
bool Solver::ac(std::vector<_variable>& vars, std::vector<_constraint_touple> constraints)
{
	std::queue<_constraint_touple> contraints_queue;
	_constraint_touple temp;
	int temp_pos_x, temp_pos_y;

	// push all constraint into queue
	for (unsigned int i = 0; i < constraints.size(); i++)
	{
		contraints_queue.push(constraints[i]);
		_variable temp = constraints[i].x;
		constraints[i].x = constraints[i].y;
		constraints[i].y = temp;
		for (unsigned int j = 0; j < constraints[i].constraints.size(); j++)
		{
			int temp = constraints[i].constraints[j].x;
			constraints[i].constraints[j].x = constraints[i].constraints[j].y;
			constraints[i].constraints[j].y = temp;
		}
		contraints_queue.push(constraints[i]);
	}

	// begin AC
	while (!contraints_queue.empty())
	{
		temp = contraints_queue.front();// get next time
		contraints_queue.pop();	// remove next item

		temp_pos_x = variable_position(vars, temp.x.var);
		temp_pos_y = variable_position(vars, temp.y.var);

		if (revise(temp, vars[temp_pos_x], vars[temp_pos_y]))
		{
			if (vars[temp_pos_x].domain.size() == 0)
			{
				return false;
			}
			for (unsigned int i = 0; i < constraints.size(); i++)
			{
				if (((constraints[i].x.var == vars[temp_pos_x].var) || (constraints[i].y.var == vars[temp_pos_x].var)) && (constraints[i].y.var != vars[temp_pos_y].var))
				{
					contraints_queue.push(constraints[i]);
					_variable temp = constraints[i].x;
					constraints[i].x = constraints[i].y;
					constraints[i].y = temp;
					for (unsigned int j = 0; j < constraints[i].constraints.size(); j++)
					{
						int temp = constraints[i].constraints[j].x;
						constraints[i].constraints[j].x = constraints[i].constraints[j].y;
						constraints[i].constraints[j].y = temp;
					}
					contraints_queue.push(constraints[i]);
				}
			}
		}

	}
	return true;
	
}

// NOTE * this is my inplementation of revise function psudocode found in "Artificial Intellegence: A modern approach (3rd Edition)"
// Algorithm:
// given xi, this function checks if there exists any value in dj such that
// (xi, dj) satesfies the constraint, if there isn't, remove xi from domain. 
bool Solver::revise(_constraint_touple touple, _variable& xi, _variable& xj)
{
	bool revised = false;
	unsigned int unsatasfied;
	
	for (unsigned int i = 0; i < xi.domain.size(); i++)
	{
		unsatasfied = 0;
		for (unsigned int j = 0; j < xj.domain.size(); j++)
		{	
			for (unsigned int k = 0; k < touple.constraints.size(); k++)
			{
				// check if exists compatable pair in domain
				if ((xi.domain[i] == touple.constraints[k].x) && (xj.domain[j] == touple.constraints[k].y))
				{
					unsatasfied++;
					break;
				}
			}

		}
		if (unsatasfied == xj.domain.size())
		{
			xi.domain.erase(xi.domain.begin() + i);
			i--;
			revised = true;
		}

	}
	return revised;
}

// based on variable value, return variable position in array
int Solver::variable_position(std::vector<_variable> vars, int variable)
{
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		if (vars[i].var == variable)
		{
			return i;
		}
	}

	return -1;
}