#include "libs.h"

#pragma once
#ifndef STRUCTS_H_
#define STRUCTS_H_

//Data structures for storing a STRIPSInstance.
struct AtomicStmt
{
	string relation;
	vector<string> args;
};

struct Condition
{
	vector<AtomicStmt> positive;
	vector<AtomicStmt> negative;
};

struct Action
{
	AtomicStmt label;
	Condition preconditions;
	Condition effects;
};

typedef vector<AtomicStmt> State;

struct STRIPSInstance
{
	State initialState;
	Condition goal;
	vector<Action> actions;
};

struct ConcreteAction
{
	string actionType;
	vector<string> arguments;
};

struct node
{
	vector<ConcreteAction> path;
	State dest;
};

extern STRIPSInstance I;

#endif // STRUCTS_H_