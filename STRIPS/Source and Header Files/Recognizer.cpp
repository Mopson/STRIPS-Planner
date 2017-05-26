#include "libs.h"
#include "Structs.h"
#include "Helpers.h"

//TOP level function of Recognizer. A STRIPS program consists of an Initial State declaration, followed by a Goal declaration,
//followed by an action set.
bool STRIPS_program(vector<string> s)
{
	int i = 0, pos;
	int theSIZE = s.size();
	vector<string> A, B, C;
	if (s.at(0) == "Initial")
	{
		while (i + 1 != theSIZE && s[i + 1] != "Goal") //If i+1 is out of range before finding "goal",it'll
		{
			i = i + 1;
		}                              //exit with a non-zero status
		A = slice(s, 0, i + 1);
		pos = i;

		if (initial_State_declaration(A)) //If it's an initial State declaration, continue
		{
			while (s[i + 1] != "Actions") //When it finds "Actions", it'll create new vector with elements
			{
				i = i + 1;
			}                //up to "Actions" that will be checked for goal declaration

			B = slice(s, pos + 1, i + 1);
			C = slice(s, i + 1, s.size()); //Everything after can be tested for an action set
										   //as long as a legal STRIPS program is passed.

			if (goal_declaration(B))
			{
				if (action_set(C))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//Slice function returning a vector containing strings
vector<string> slice(vector<string> s, int a, int b)
{
	vector<string> temp;
	for (int i = a; i < b; i++)
	{
		temp.push_back(s.at(i));
	}
	return temp;
}

bool literal_chars(vector<string> s);

//Checks if the element of the vector is a symbol(not STRIPS keyword)
bool symbol(string s)
{
	if (s != "Initial" && s != "State" && s != "Goal" && s != "Actions" && s != "Preconditions" && s != "Effects" && s != "not")
	{
		return true;
	}
}

//Checks if vector of strings consists of one or more
//symbols separated by commas.
bool nonEmpty_symbol_list(vector<string> s)
{
	if (s.size() == 1 && symbol(s.at(0)))
	{
		return true;
	}

	else if (s.size() >= 3 && symbol(s.at(0)) && s.at(1) == ",")
	{
		if (nonEmpty_symbol_list(slice(s, 2, s.size())))
		{
			return true;
		}
	}
	return false;
}

//Checks if the vector of strings is zero or more
//symbols separated by commas
bool symbol_list(vector<string> s)
{
	return(s.empty() || nonEmpty_symbol_list(s));
}

/* Checks if vector of strings is an atomic Statement, which consists of
a symbol, "(", zero or more symbols separated by commas, followed by
")" */
bool atomic_Statement(vector<string> s)
{
	if (s.size() >= 3 && symbol(s.at(0)) && s.at(1) == "(" && (s[s.size() - 1] == ")"))
	{
		if (symbol_list(slice(s, 2, s.size() - 1)))
		{
			return true;
		}
	}
	return false;
}

//Checks if the vector of strings passed is either an atomic Statement,
//or an atomic Statement followed by a comma and a non-empty atom list
bool nonEmpty_atom_list(vector<string> s)
{
	if (atomic_Statement(s))
	{
		return true;
	}

	else
	{
		for (int i = 1; i < s.size() - 1; i++)
		{
			if (s[i] == ",")
			{
				if (atomic_Statement(slice(s, 0, i)) && (nonEmpty_atom_list(slice(s, i + 1, s.size())) || literal_chars(slice(s, i + 1, s.size()))))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//Checks if there are zero or more atomic Statements separated by commas
bool atom_list(vector<string> s)
{
	return(s.empty() || nonEmpty_atom_list(s));
}

//Checks if the vector of strings is either an atomic Statement, or the identifier
//"not" followed by an atomic Statement
bool literal_chars(vector<string> s)
{
	if (atom_list(s))
	{
		return true;
	}
	else if (s.size() > 0 && s.at(0) == "not" && atom_list(slice(s, 1, s.size())))
	{
		return true;
	}
	return false;
}

//Checks if the vector of strings is an action prototype, which is "_",
//followed by an atomic Statement, followed by an underscore.
bool action_prototype(vector<string> s)
{
	if (s.size() >= 3 && s.at(0) == "_" && s.at(1) != "_" && s.at(s.size() - 2) != "_" && s.back() == "_")
	{
		if (atomic_Statement(slice(s, 1, s.size() - 1)))
		{
			return true;
		}
	}
}

//Checks if the vector of strings is a precondition declaration, which consists of the 
//identifier "Preconditions", ":", and followed by 0 or more literals separated by commas.
bool precondition_declaration(vector<string> s)
{
	if (s.size() >= 2 && s.at(0) == "Preconditions" && s.at(1) == ":")
	{
		if (literal_chars(slice(s, 2, s.size())))
		{
			return true;
		}
	}
	return false;
}

//Checks if the vector of strings is an effects declaration, which consists of the 
//identifier "Effects", ":", and followed by 0 or more literals separated by ccmmas.
bool effects_declaration(vector<string> s)
{
	if (s.size() >= 2 && s.at(0) == "Effects" && s.at(1) == ":")
	{
		if (literal_chars(slice(s, 2, s.size())))
		{
			return true;
		}
	}
	return false;
}

//Checks if the vector of strings is an action declaration, which consists of an action prototype,
//precondition declaration, and an effects declaration.
bool action_declaration(vector<string> s)
{
	int i = 0, pos, pos2, pos3;
	int totalSize = s.size();
	vector<string> A, B, C, D;

	while (s[i + 1] != "Preconditions")
	{
		i = i + 1;
	}
	A = slice(s, 0, i + 1);
	pos = i;

	if (action_prototype(A))
	{
		while (s[i + 1] != "Effects")
		{
			i = i + 1;
		}
		pos2 = i;
		B = slice(s, pos + 1, i + 1);
		while (i + 1 != totalSize && s[i + 1] != "_") //If out of bounds, exits with non-zero status
		{
			i = i + 1;
		}
		pos3 = i;
		C = slice(s, pos2 + 1, i + 1);
		D = slice(s, i + 1, s.size());

		if (precondition_declaration(B))
		{
			if (effects_declaration(C))
			{
				if (pos3 + 1 == s.size())
				{
					if (effects_declaration(C))    //When there are no more strings in vector, the last
					{
						return true;
					}              //vector of strings will be checked to see if it's
								   //an effects declaration
				}
				else if (action_declaration(D))  //If there are still strings left in the vector,
				{
					return true;
				}                  //action declaration will be recursively called until
								   //there are no more strings in the vector
			}
		}
	}
	return false;
}

/*Checks for initial State declaration, which consists of
the tokens "Initial", "State", and ":", followed by zero or more
atomic Statements*/
bool initial_State_declaration(vector<string> s)
{
	if (s.size() >= 3 && s.at(0) == "Initial" && s.at(1) == "State" && s.at(2) == ":")
	{
		if (atom_list(slice(s, 3, s.size())))
		{
			return true;
		}
	}

	return false;
}

/*Checks for a goal declaration, which consists of
the tokens "Goal" and ":", followed by zero or more
literal_chars separated by commas*/
bool goal_declaration(vector<string> s)
{
	if (s.size() >= 2 && s.at(0) == "Goal" && s.at(1) == ":")
	{
		if (literal_chars(slice(s, 2, s.size())))
		{
			return true;
		}
	}
	return false;
}

/*Checks for an action set, which consists of
the tokens "Actions" and ":", followed by one or more
action declarations*/
bool action_set(vector<string> s)
{
	if (s.size() >= 2 && s.at(0) == "Actions" && s.at(1) == ":")
	{
		if (action_declaration(slice(s, 2, s.size())))
		{
			return true;
		}
	}
	return false;
}