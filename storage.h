// Prevent circular inclusion
#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#define UNASSIGNED -1

struct _constraint_values
{
	int x;
	int y;
};

struct _variable
{
	int var;
	int assignment;
	std::vector<int> domain;
};

struct _constraint_touple
{
	_variable x;
	_variable y;
	std::vector<_constraint_values> constraints;
};



#endif