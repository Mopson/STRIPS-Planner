#include "libs.h"
#include "Structs.h"
#include "Helpers.h"

int main()
{	
	//solve() will find the solution to the STRIPS program that is the input 
	vector<ConcreteAction> answer = solve("Initial State: At(A), Level(low), BoxAt(C), BananasAt(B)\nGoal: Have(bananas)\n\nActions:\n// move from X to Y\n _Move(X, Y)_\nPreconditions: At(X), Level(low)\nEffects: not At(X), At(Y)\n\n// climb up on the box\n_ClimbUp(Location)_\nPreconditions: At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions: At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions: At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n\n// take the bananas\n_TakeBananas(Location)_\nPreconditions: At(Location), BananasAt(Location), Level(high)\nEffects: Have(bananas)");
	
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i].actionType;
		for (int j = 0; j < answer[i].arguments.size(); j++)
			
			cout << answer[i].arguments[j];
		cout << endl << endl;
	}

	return 0;
}