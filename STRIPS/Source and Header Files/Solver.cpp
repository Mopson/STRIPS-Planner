#include "libs.h"
#include "Structs.h"
#include "Helpers.h"

STRIPSInstance I; //GLOBAL VARIABLE//

//The TOP level function which makes use of the tokenizer functions, the recognizer functions,
//the parser functions, and the ConcreteAction/Successor functions
vector<ConcreteAction> solve(string S)
{
	vector<string> toks = tokenize(S);
	vector<ConcreteAction> Res;

	if (!STRIPS_program(toks))
	{
		cout << "Sorry this isn't a valid STRIPS program." << endl;
		return Res;
	}

	I = STRIPS_programP(toks);
	vector<ConcreteAction> v;
	node n, a;

	n.path = v;
	n.dest = I.initialState;
	a = search(n);
	Res = a.path;

	return Res;
}

//removes any duplicants in a vector of strings
vector<string> removeDuplicants(vector<string> c)
{
	string check;
	for (int i = 0; i < c.size(); i++)
	{
		check = c[i];
		for (int j = i + 1; j < c.size(); j++)
		{
			if (check == c[j])
			{
				c.erase(c.begin() + j);
				j = i;
			}
		}
	}
	return c;
}

//gets all constants that are found in a STRIPS program.
vector<string> getConstants()
{
	vector<string> c, constants;
	State initials = I.initialState;
	Condition goals = I.goal;
	vector<Action> theActions = I.actions;
	int i, j, k, l;
	vector<string> nc, notConsts;
	bool checker = true;
	for (i = 0; i < theActions.size(); i++)
	{
		for (j = 0; j < theActions[i].label.args.size(); j++)
		{
			nc.push_back(theActions[i].label.args[j]);

		}
	}

	notConsts = removeDuplicants(nc);

	for (i = 0; i < initials.size(); i++)
	{
		for (j = 0; j < initials[i].args.size(); j++)
		{
			c.push_back(initials[i].args[j]);
		}
	}

	for (i = 0; i < goals.positive.size(); i++)
	{
		for (j = 0; j < goals.positive[i].args.size(); j++)
		{
			c.push_back(goals.positive[i].args[j]);
		}
	}

	for (i = 0; i < goals.negative.size(); i++)
	{
		for (j = 0; j < goals.negative[i].args.size(); j++)
		{
			c.push_back(goals.negative[i].args[j]);
		}
	}

	for (i = 0; i < theActions.size(); i++)
	{
		for (j = 0; j < theActions[i].preconditions.positive.size(); j++)
		{
			for (k = 0; k < theActions[i].preconditions.positive[j].args.size(); k++)
			{
				for (l = 0; l < notConsts.size();)
				{
					if (theActions[i].preconditions.positive[j].args[k] != notConsts[l])
					{
						if (l + 1 == notConsts.size() && checker)
							c.push_back(theActions[i].preconditions.positive[j].args[k]);
						l++;
					}
					else
					{
						l++;
						checker = false;
					}
				}
				checker = true;
			}
		}
	}

	for (i = 0; i < theActions.size(); i++)
	{
		for (j = 0; j < theActions[i].preconditions.negative.size(); j++)
		{
			for (k = 0; k < theActions[i].preconditions.negative[j].args.size(); k++)
			{
				for (l = 0; l < notConsts.size();)
				{
					if (theActions[i].preconditions.negative[j].args[k] != notConsts[l])
					{
						if (l + 1 == notConsts.size() && checker)
							c.push_back(theActions[i].preconditions.negative[j].args[k]);
						l++;
					}
					else
					{
						l++;
						checker = false;
					}
				}
				checker = true;
			}
		}
	}

	for (i = 0; i < theActions.size(); i++)
	{
		for (j = 0; j < theActions[i].effects.positive.size(); j++)
		{
			for (k = 0; k < theActions[i].effects.positive[j].args.size(); k++)
			{
				for (l = 0; l < notConsts.size();)
				{
					if (theActions[i].effects.positive[j].args[k] != notConsts[l])
					{
						if (l + 1 == notConsts.size() && checker)
							c.push_back(theActions[i].effects.positive[j].args[k]);
						l++;
					}
					else
					{
						l++;
						checker = false;
					}
				}
				checker = true;
			}
		}
	}

	for (i = 0; i < theActions.size(); i++)
	{
		for (j = 0; j < theActions[i].effects.negative.size(); j++)
		{
			for (k = 0; k < theActions[i].effects.negative[j].args.size(); k++)
			{
				for (l = 0; l < notConsts.size();)
				{
					if (theActions[i].effects.negative[j].args[k] != notConsts[l])
					{
						if (l + 1 == notConsts.size() && checker)
							c.push_back(theActions[i].effects.negative[j].args[k]);
						l++;
					}
					else
					{
						l++;
						checker = false;
					}
				}
				checker = true;
			}
		}
	}
	constants = removeDuplicants(c);
	return constants;
}

//Used to get the label of every action in the global STRIPSInstance I
vector<string> allActionTypes()
{
	vector<string> actions;
	for (int i = 0; i < I.actions.size(); i++)
	{
		actions.push_back(I.actions[i].label.relation);
	}
	return actions;
}

//Checks the arity of each Action prototype
bool arity(string s, int a)
{
	for (int i = 0; i < I.actions.size(); i++)
	{
		if (I.actions[i].label.relation == s)
		{
			if (I.actions[i].label.args.size() == a)
				return true;
		}

	}
	return false;
}

vector<string> emptyVectorOfStrings()
{
	vector<string> res;
	return res;
}

//Creates every possible action using the every constant and every Action label,
//returns a vector of ConcreteAction
vector<ConcreteAction> allActions()
{
	vector<string> ATS = allActionTypes();
	vector<string> consts = getConstants();
	vector<ConcreteAction> Res;
	ConcreteAction act;

	for (int s = 0; s < ATS.size(); s++)
	{
		if (arity(ATS[s], 0))
		{
			act.actionType = ATS[s];
			act.arguments = emptyVectorOfStrings();
			Res.push_back(act);
		}
	}

	for (int s = 0; s < ATS.size(); s++)
	{
		if (arity(ATS[s], 1))
		{
			for (int t = 0; t < consts.size(); t++)
			{
				act.actionType = ATS[s];
				act.arguments = emptyVectorOfStrings();
				act.arguments.push_back(consts[t]);
				Res.push_back(act);
			}
		}
	}

	for (int s = 0; s < ATS.size(); s++)
	{
		if (arity(ATS[s], 2))
		{
			for (int t1 = 0; t1 < consts.size(); t1++)
			{
				for (int t2 = 0; t2 < consts.size(); t2++)
				{
					act.actionType = ATS[s];
					act.arguments = emptyVectorOfStrings();
					act.arguments.push_back(consts[t1]);
					act.arguments.push_back(consts[t2]);
					Res.push_back(act);
				}
			}
		}
	}

	return Res;
}

//Compares the arguments of the two AtomicStmts
bool compareAtm(AtomicStmt a, AtomicStmt b)
{
	if ((a.relation == b.relation) && (a.args.size() == b.args.size()))
	{
		for (int i = 0; i < a.args.size(); i++)
		{
			if (a.args[i] != b.args[i])
				return false;
		}
		return true;
	}

	return false;
}

//Compares the arguments
vector<string> compareArgs(vector<string> a, vector<string> b)
{
	//a is the prototype's arguments
	//b is the precondition's and effect's arguments
	int count = 0;
	vector<string> ret;

	for (int i = 0; i < b.size(); i++) //Every argument in b
	{
		for (int j = 0; j < a.size(); j++) //Every argument in a
		{
			if (b[i] == a[j]) //If arg of b is in a, count increments. Otherwise count remains 0.
			{
				count++;
				break; //Arg in b is somewhere in a, that's all we need to know
			}
		}
		if (count == 0) //Count is the number of times an argument in b is found in a. Count = 0 means that there was no match
			ret.push_back(b[i]); //Ret will contain every argument in b that is not found in a.
		count = 0;
	}
	return ret;
}

//Compare the AtomicStmt with the State
bool checkAtmSt(State S, AtomicStmt a)
{
	for (int i = 0; i < S.size(); i++)
	{
		if (compareAtm(a, S[i]))
			return true;
	}

	return false;
}

//Gets all constants that could be used in a ConcreteAction. Used to help check
//if the move is logical or not.
vector<string> alienConstants()
{
	vector<string> preAndeffConstants, protoConstants, constants, Ret;
	int m = 0;
	for (int i = 0; i < I.actions.size(); i++)//for every action in global variable I
		for (int j = 0; j < I.actions[i].label.args.size(); j++)//for every argument in action[i]'s prototype in I
		{
			protoConstants.push_back(I.actions[i].label.args[j]);//protoConstants = arguments in prototype
			for (int k = 0; k < I.actions[i].preconditions.positive.size(); k++)//For every argument in preconditions positive
			{
				while (m != I.actions[i].preconditions.positive[k].args.size())
				{
					preAndeffConstants.push_back(I.actions[i].preconditions.positive[k].args[m]);
					m++;
				}
				m = 0;
			}
			for (int k = 0; k < I.actions[i].preconditions.negative.size(); k++)//For every argument in preconditions negative
			{
				while (m != I.actions[i].preconditions.negative[k].args.size())
				{
					preAndeffConstants.push_back(I.actions[i].preconditions.negative[k].args[m]);
					m++;
				}
				m = 0;
			}
			for (int k = 0; k < I.actions[i].effects.positive.size(); k++)//For every argument in effects positive
			{
				while (m != I.actions[i].effects.positive[k].args.size())
				{
					preAndeffConstants.push_back(I.actions[i].effects.positive[k].args[m]);
					m++;
				}
				m = 0;
			}
			for (int k = 0; k < I.actions[i].effects.negative.size(); k++)//For every argument in effects negative
			{
				while (m != I.actions[i].effects.negative[k].args.size())
				{
					preAndeffConstants.push_back(I.actions[i].effects.negative[k].args[m]);
					m++;
				}
				m = 0;
			}
		}

	preAndeffConstants = removeDuplicants(preAndeffConstants);
	protoConstants = removeDuplicants(protoConstants);
	Ret = compareArgs(protoConstants, preAndeffConstants);

	return Ret;
}

//If all positive members of C are in S, and no negative members of C are in S, return true.
bool satisfies(State S, Condition C)
{
	for (int i = 0; i < C.positive.size(); i++) {
		if (!checkAtmSt(S, C.positive[i])) {
			return false;
		}
	}

	for (int i = 0; i < C.negative.size(); i++) {
		if (checkAtmSt(S, C.negative[i])) {
			return false;
		}
	}

	return true;
}

//Replaces the each argument of an Action in STRIPSInstance I with the passed arguments
Action substitute(vector<string> args, Action A)
{
	string a, b;
	if (args.size() == 2)
	{
		a = A.label.args[0];
		b = A.label.args[1];
	}

	else if (args.size() == 1)
	{
		a = A.label.args[0];
	}

	for (int i = 0; i < args.size(); i++)
	{
		A.label.args[i] = args[i];

		for (int j = 0; j < A.preconditions.positive.size(); j++)
		{
			if (A.preconditions.positive[j].args[0] == a)
			{
				A.preconditions.positive[j].args[0] = args[0];
			}
			else if (A.preconditions.positive[j].args[0] == b)
			{
				A.preconditions.positive[j].args[0] = args[1];
			}
		}

		for (int j = 0; j < A.preconditions.negative.size(); j++)
		{
			if (A.preconditions.negative[j].args[0] == a)
			{
				A.preconditions.negative[j].args[0] = args[0];
			}
			else if (A.preconditions.negative[j].args[0] == b)
			{
				A.preconditions.negative[j].args[0] = args[1];
			}
		}

		for (int j = 0; j < A.effects.positive.size(); j++)
		{
			if (A.effects.positive[j].args[0] == a)
			{
				A.effects.positive[j].args[0] = args[0];
			}
			else if (A.effects.positive[j].args[0] == b)
			{
				A.effects.positive[j].args[0] = args[1];
			}
		}

		for (int j = 0; j < A.effects.negative.size(); j++)
		{
			if (A.effects.negative[j].args[0] == a)
			{
				A.effects.negative[j].args[0] = args[0];
			}
			else if (A.effects.negative[j].args[0] == b)
			{
				A.effects.negative[j].args[0] = args[1];
			}
		}
	}
	return A;
}

//Tests if a ConcreteAction c is possible in the current State S
bool possible(ConcreteAction c, State S)
{
	string nameOfAction = c.actionType;
	vector<string> args = c.arguments;
	vector<Action> moves = I.actions;
	vector<string> alienConsts = alienConstants();

	for (int i = 0; i < moves.size(); i++)
	{
		if (nameOfAction == moves[i].label.relation)
		{
			Action a = moves[i];
			if (args.size() == a.label.args.size())
			{
				for (int iter = 0; iter < args.size(); iter++)
				{
					for (int iter2 = 0; iter2 < alienConsts.size(); iter2++)
					{
						if (args[iter] == alienConsts[iter2])
							return false;
					}
				}

				Action b = substitute(args, a);

				if (satisfies(S, b.preconditions))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//Returns the new state after performing ConcreteAction c
State result(ConcreteAction c, State S)
{
	Action A;
	State newState;

	if (possible(c, S))
	{
		for (int i = 0; i < I.actions.size(); i++)
		{
			if (c.actionType == I.actions[i].label.relation)
			{
				A = substitute(c.arguments, I.actions[i]);//A is new parameterized action
				for (int i = 0; i < S.size(); i++)
				{
					if (!checkAtmSt(A.effects.negative, S[i]))
						newState.push_back(S[i]);
				}
				for (int i = 0; i < A.effects.positive.size(); i++)
				{
					if (!checkAtmSt(newState, A.effects.positive[i]))
						newState.push_back(A.effects.positive[i]);
				}
			}
		}
	}

	return newState;
}

//Creates a node struct
node makeNode(State S, vector<ConcreteAction> X)
{
	node n;
	n.dest = S;
	n.path = X;
	return n;
}

//Concats the two vector of nodes together
vector<node> concateVecOfNode(vector<node> tailEnd, vector<node> kids)
{
	vector<node> open = tailEnd;
	for (int i = 0; i < kids.size(); i++)
	{
		open.push_back(kids[i]);
	}
	return open;
}

//Removes the first node in the vector of nodes and returns all of the other nodes
vector<node> tail(vector<node> nodeVec)
{
	vector<node> tailEnd = nodeVec;
	tailEnd.erase(tailEnd.begin());
	return tailEnd;
}

//Tests if the State of node n is the Goal we want to achieve for the STRIPSInstance I
bool Green(node n)
{
	return satisfies(n.dest, I.goal);
}

//Create a vector of nodes for all the possible nodes that are the results
//of doing a possible ConcreteAction that can be made from the current State in node n.
vector<node> children(node n)
{
	vector<node> kids;
	vector<ConcreteAction> X, PC, all;
	State S;
	all = allActions();

	//For every ConcreteAction in all, find every possible ConcreteAction that can be made from the State in node n
	for (int c = 0; c < all.size(); c++)
	{
		if (possible(all[c], n.dest))
		{
			PC.push_back(all[c]);
		}
	}

	//For every possible ConcreteAction in PC, create a node with its new State and the ConcreteAction
	//that got it there
	for (int k = 0; k < PC.size(); k++)
	{
		node temp = n;
		S = result(PC[k], n.dest);
		temp.path.push_back(PC[k]);
		X = temp.path;

		node madeNode = makeNode(S, X);
		kids.push_back(madeNode);

	}
	return kids;
}

//Searches through each node, looking for the Goal of STRIPSInstance I, and the path it takes from the initial
//state to get to the Goal.
node search(node n) {

	vector<node> open, closed, tailEnd, kids;
	bool check = false, match;
	open.push_back(n);
	int it, jit, time = 0;
	while (open.size() != 0)
	{
		time++;
		node X = open.at(0);
		if (Green(X))
		{
			return X;
		}
		vector<node> other;
		other.push_back(X);
		tailEnd = tail(open);
		closed = concateVecOfNode(closed, other);
		open.erase(open.begin());
		kids = children(X);


		for (int c = 0; c < kids.size(); c++) //for every kid of x
		{
			jit = 0;
			for (int closedHead = 0; closedHead < closed.size(); closedHead++) //for every node in closed
			{
				match = false;
				it = 0; //used to see if everything in kids[c] matches a node of closed
				for (int kidsRel = 0; kidsRel < kids[c].dest.size(); kidsRel++)//for every relation in the dest of kids
				{
					for (int closedRel = 0; closedRel < closed[closedHead].dest.size(); closedRel++)//for every relation in the dest of closed
					{
						if (kids[c].dest[kidsRel].relation == closed[closedHead].dest[closedRel].relation) //if the relation of kids.dest == the relation of closed.dest
						{
							for (int p = 0; p < kids[c].dest[kidsRel].args.size(); p++) //Then compare the arguments, for every arg in kids.dest
							{
								for (int g = 0; g < closed[closedHead].dest[closedRel].args.size(); g++) //for every arg in closed.dest
								{
									if (kids[c].dest[kidsRel].args[p] == closed[closedHead].dest[closedRel].args[g])
									{
										check = true;
									}
									else
										check = false;
								}
							}
						}

						if (check)
						{
							it++;
							check = false;
							break;
						}
					}
				}
				if (it == kids[c].dest.size())
				{
					match = true; //This kid node matched a closed node. Don't need to check this kid node with anymore closed nodes.
					break;
				}
				else
					jit++; //This kid node didn't match, need to check with next closed node.
			}
			if (match)
				continue;//kid node already has a match, move on.
			if (jit == closed.size())
			{
				open.push_back(kids[c]); //Went through every closed node and didn't find a match, we can push this node onto open.
			}
		}

	}

	return n;
}