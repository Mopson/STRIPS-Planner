#include "libs.h"
#include "Structs.h"
#include "Helpers.h"


//TOP level function that uses parsing functions to create a STRIPSInstance struct I, a global variable.
STRIPSInstance STRIPS_programP(vector<string> s)
{
	State A;
	Condition B;
	vector<Action> C;
	STRIPSInstance FIN;

	int theSIZE = s.size();
	int i = 0, pos;

	if (!STRIPS_program(s)) //Test to see if it is a legal STRIPS program.
	{
		cout << "This is not a legal STRIPS Program." << endl << endl;
		return FIN;
	}

	else
	{
		cout << "This is a legal STRIPS Program." << endl << endl;
		while (i + 1 != theSIZE && s[i + 1] != "Goal")
		{
			i = i + 1;
		}

		pos = i;
		A = initial_State_declarationP(slice(s, 0, i + 1)); //Parses the tokens up to the Goal declaration as the Inital State.

		while (i + 1 != theSIZE && s[i + 1] != "Actions")
		{
			i = i + 1;
		}

		B = goal_declarationP(slice(s, pos + 1, i + 1)); //Parses the tokens up the Actions as the Goal.
		C = action_listP(slice(s, i + 1, s.size())); //Parses all of the actions
		FIN.initialState = A;
		FIN.goal = B;
		FIN.actions = C;

		return FIN;
	}
}

bool literal(vector<string> s)
{
	if (atomic_Statement(s))
	{
		return true;
	}
	else if (s.size() > 0 && s.at(0) == "not" && atomic_Statement(slice(s, 1, s.size())))
	{
		return true;
	}
	return false;
}

//Concats two States
State StateConcat(State A, State B)
{
	for (int i = 0; i < B.size(); i++)
	{
		A.push_back(B.at(i));
	}
	return A;
}

//pushes onto Positive member of a Condition
Condition pushingOntoPCondition(Condition A, AtomicStmt p)
{
	A.positive.insert(A.positive.begin(), p);
	return A;
}

//pushes onto Negative member of a Condition
Condition pushingOntoNCondition(Condition A, AtomicStmt p)
{
	A.negative.insert(A.negative.begin(), p);
	return A;
}

//Helper for action_declarationP, returns the label for an Action struct
AtomicStmt action_prototypeP(vector<string> s)
{
	AtomicStmt FIN;
	vector<string> A, B, C;
	int j = 3;
	if (action_prototype(s))
	{
		FIN.relation = s.at(1);
		if (s.at(2) == "(" && s.at(s.size() - 2) == ")")
		{
			A = slice(s, 3, s.size() - 2);

			if (s.at(2) == "(" && s.at(3) == ")")
			{
				return FIN;
			}

			else if (s.at(2) == "(" && symbol(s.at(3)) && s.at(4) == ")")
			{
				B = slice(s, 3, s.size() - 2);
				FIN.args.push_back(B[0]);
			}
			else
			{
				for (int i = 0; i < s.size(); i++)
				{
					if (s.at(i) == "," || s.at(i) == ")")
					{
						int indexInC = 0;
						C = slice(s, j, i);
						FIN.args.push_back(C[indexInC]);
						indexInC++;
						j = j + 2;
					}
				}
			}
		}
		return FIN;
	}

	else
	{
		return FIN;
	}
}

//Helper for action_listP, will split the Action into three categories, the prototype, it's preconditions, and it's effects.
vector<Action> action_declarationP(vector<string> s)
{
	vector<Action> tempVecofAc1, tempVecofAc2, FIN;
	Action anAction;
	Condition X, Y;
	AtomicStmt A, B, C;
	vector<string> tempA, tempB, tempC, tempD;

	int i = 0, pos, pos2, pos3;
	int totalSize = s.size();

	while (s[i + 1] != "Preconditions")
	{
		i = i + 1;
	}

	tempA = slice(s, 0, i + 1);
	pos = i;
	if (action_prototype(tempA))
	{
		A = action_prototypeP(tempA);
		anAction.label = A;

		while (s[i + 1] != "Effects")
		{
			i = i + 1;
		}
		pos2 = i;
		tempB = slice(s, pos + 1, i + 1);

		while (i + 1 != totalSize && s[i + 1] != "_") //If out of bounds, exits with non-zero status
		{
			i = i + 1;
		}
		pos3 = i;
		tempC = slice(s, pos2 + 1, i + 1);
		tempD = slice(s, i + 1, s.size());

		if (precondition_declaration(tempB))
		{
			X = precondition_declarationP(tempB);
			anAction.preconditions = X;

			if (effects_declaration(tempC))
			{
				if (pos3 + 1 == s.size())
				{
					Y = effects_declarationP(tempC);
					anAction.effects = Y;
					tempVecofAc1.push_back(anAction);
					return tempVecofAc1;
				}
				else
				{
					Y = effects_declarationP(tempC);
					anAction.effects = Y;
					tempVecofAc1.push_back(anAction);
					tempVecofAc2 = (action_declarationP(tempD));
					FIN = tempVecofAc1;
					FIN.insert(FIN.end(), tempVecofAc2.begin(), tempVecofAc2.end());
					return FIN;
				}
			}
		}
	}

}

//Parses recognized Action tokens into the Action struct
vector<Action> action_listP(vector<string> s)
{
	return (action_declarationP(slice(s, 2, s.size())));
}

//Will return an Atomicstmt struct to be used in other functions
AtomicStmt AtomicStmtP(vector<string> s)
{
	AtomicStmt FIN;
	vector<string> A;
	int j = 2;

	if (atomic_Statement(s))
	{
		FIN.relation = s.at(0);
		if (s.at(1) == "(" && s.at(s.size() - 1) == ")")
		{
			A = slice(s, 2, s.size() - 1);
			if (s.at(1) == "(" && s.at(2) == ")")
			{
				return FIN;
			}

			else if (s.at(1) == "(" && symbol(s.at(2)) && s.at(3) == ")")
			{
				A = slice(s, 2, s.size() - 1);
				FIN.args.push_back(A[0]);
			}

			else
			{
				for (int i = 0; i < s.size(); i++)
				{
					if (s.at(i) == "," || s.at(i) == ")")
					{
						int indexInA = 0;
						A = slice(s, j, i);
						FIN.args.push_back(A[indexInA]);
						indexInA++;
						j = j + 2;
					}
				}
			}
		}
		return FIN;
	}
	else
	{
		return FIN;
	}
}

//Similar to NE atom list recognizer function up above
State NEatom_listP(vector<string> s)
{
	AtomicStmt A, B;
	State X, Y, FIN;
	if (atomic_Statement(s))
	{
		A = AtomicStmtP(s);
		Y.push_back(A);
		return Y;
	}

	else
	{
		for (int i = 0; i < s.size() - 1; i++)
		{
			if (s[i] == "," && atomic_Statement(slice(s, 0, i)) && i + 1 != s.size())
			{
				B = AtomicStmtP(slice(s, 0, i));
				Y.push_back(B);
				X = NEatom_listP(slice(s, i + 1, s.size()));
				FIN = StateConcat(Y, X);
				return FIN;
			}
		}
	}

}

//Similar to atom list recognizer function up above
State atom_listP(vector<string> s)
{
	State A, B;
	if (s.size() == 0)
	{
		return A;
	}

	else
	{
		B = NEatom_listP(s);
		return B;
	}
}

//Similar to NE literal list recognizer function up above
Condition NEliteral_listP(vector<string> s)
{
	Condition A, B, remaining, tempCon, FIN;
	AtomicStmt X, Y, p;

	if (literal(s))
	{
		if (s.at(0) == "not")
		{
			X = AtomicStmtP(slice(s, 1, s.size()));
			FIN.negative.push_back(X);
			return FIN;
		}

		else
		{
			X = AtomicStmtP(s);
			FIN.positive.push_back(X);
			return FIN;
		}
	}

	else
	{
		for (int i = 3; i < s.size(); i++)
		{
			if (s.at(i) == "," && i != s.size())
			{
				if (atomic_Statement(slice(s, 0, i)))
				{
					remaining = NEliteral_listP(slice(s, i + 1, s.size()));
					p = AtomicStmtP(slice(s, 0, i));
					A.positive = remaining.positive;
					B.negative = remaining.negative;
					tempCon = pushingOntoPCondition(A, p);
					FIN.positive = tempCon.positive;
					FIN.negative = B.negative;
					return FIN;
				}
				else if (literal_chars(slice(s, 0, i)))
				{
					remaining = NEliteral_listP(slice(s, i + 1, s.size()));
					p = AtomicStmtP(slice(s, 1, i));
					A.positive = remaining.positive;
					B.negative = remaining.negative;
					tempCon = pushingOntoNCondition(B, p);
					FIN.positive = A.positive;
					FIN.negative = tempCon.negative;
					return FIN;

				}
			}
		}
	}
}

//Similar to the literal recognizer function up above
Condition literal_listP(vector<string> s)
{
	Condition FIN;

	if (s.size() == 0)
	{
		return FIN;
	}

	else
	{
		return NEliteral_listP(s);
	}

}

//Helper function, returns the effects for an Action struct
Condition effects_declarationP(vector<string> s)
{
	return(literal_listP(slice(s, 2, s.size())));
}

//Helper function, returns the preconditions for an Action struct
Condition precondition_declarationP(vector<string> s)
{
	return(literal_listP(slice(s, 2, s.size())));
}

//Used to parse the Goal declaration
Condition goal_declarationP(vector<string> s)
{
	return(literal_listP(slice(s, 2, s.size())));
}

//Used to parse the Initial State declaration
State initial_State_declarationP(vector<string> s)
{
	return atom_listP(slice(s, 3, s.size()));
}