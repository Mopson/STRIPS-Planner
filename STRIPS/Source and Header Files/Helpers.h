#include "libs.h"
#include "Structs.h"

#pragma once
#ifndef HELPERS_H_
#define HELPERS_H_

extern STRIPSInstance I;

//Tokenizer
bool head(string s);
void pop(string &s);
void whitespacePopper(string &s);
bool tokenChecker(string s);
bool commentChecker(string s);
bool isEmpty(string s);
vector<string> tokenize(string str);

//Recognizer
vector<string> slice(vector<string> s, int a, int b);
bool literal_chars(vector<string> s);
bool symbol(string s);
bool nonEmpty_symbol_list(vector<string> s);
bool symbol_list(vector<string> s);
bool atomic_Statement(vector<string> s);
bool nonEmpty_atom_list(vector<string> s);
bool atom_list(vector<string> s);
bool literal_chars(vector<string> s);
bool action_prototype(vector<string> s);
bool precondition_declaration(vector<string> s);
bool effects_declaration(vector<string> s);
bool action_declaration(vector<string> s);
bool initial_State_declaration(vector<string> s);
bool goal_declaration(vector<string> s);
bool action_set(vector<string> s);
bool STRIPS_program(vector<string> s);

//Parser
bool literal(vector<string> s);
State StateConcat(State A, State B);
Condition pushingOntoPCondition(Condition A, AtomicStmt p);
Condition pushingOntoNCondition(Condition A, AtomicStmt p);
AtomicStmt action_prototypeP(vector<string> s);
vector<Action> action_declarationP(vector<string> s);
vector<Action> action_listP(vector<string> s);
AtomicStmt AtomicStmtP(vector<string> s);
State NEatom_listP(vector<string> s);
State atom_listP(vector<string> s);
Condition NEliteral_listP(vector<string> s);
Condition literal_listP(vector<string> s);
Condition effects_declarationP(vector<string> s);
Condition precondition_declarationP(vector<string> s);
Condition goal_declarationP(vector<string> s);
State initial_State_declarationP(vector<string> s);
STRIPSInstance STRIPS_programP(vector<string> s);

//Solver
vector<string> removeDuplicants(vector<string> c);
vector<string> getConstants();
vector<string> allActionTypes();
bool arity(string s, int a);
vector<string> emptyVectorOfStrings();
vector<ConcreteAction> allActions();
bool compareAtm(AtomicStmt a, AtomicStmt b);
vector<string> compareArgs(vector<string> a, vector<string> b);
bool checkAtmSt(State S, AtomicStmt a);
vector<string> alienConstants();
bool satisfies(State S, Condition C);
Action substitute(vector<string> args, Action A);
bool possible(ConcreteAction c, State S);
State result(ConcreteAction c, State S);
node makeNode(State S, vector<ConcreteAction> X);
vector<node> concateVecOfNode(vector<node> tailEnd, vector<node> kids);
vector<node> tail(vector<node> nodeVec);
bool Green(node n);
vector<node> children(node n);
node search(node n);
vector<ConcreteAction> solve(string S);

#endif // HELPERS_H_