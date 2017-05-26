# STRIPS-Planner

**Run the executable with Command Prompt

Stanford Research Institute Problem Solver
https://en.wikipedia.org/wiki/STRIPS

Implemented in Data Structures course

A STRIPS program is a vector of strings defined as follows: 
 
1.  comma, underscore, left paren, right paren are the tokens ",", "_","(", and ")". 
2.  A STRIPS keyword is one of the following identifiers: "Initial", "state", "Goal", "Actions", "Preconditions", "Effects", and "not". 
3.  A symbol is an identifier that is not a STRIPS keyword.
4.  An atomic statement consists of a symbol, followed by a left paren, followed by zero or more symbols separated by commas, followed by     a right paren. 
5.  A literal is either an atomic statement, or the identifier "not" followed by an atomic statement. 
6.  An initial state declaration consists of the tokens "Initial", "state", and ":", in order, followed by zero or more atomic statements     separated by commas. 
7.  A goal declaration consists of the tokens "Goal", and ":", in order, followed by zero or more literals separated by commas. 
8.  An action set consists of the tokens "Actions" and ":", in order, followed by one or more action declarations. 
9.  An action declaration consists of an action prototype, followed by a precondition declaration, followed by an effects declaration.
10. An action prototype consists of an underscore, followed by an atomic statement, followed by an underscore. 
11. A precondition declaration consist of the identifiers "Preconditions" and ":", in order, followed by zero or more literals separated       by commas. 
12. An effects declaration consist of the identifiers "Effects" and ":", in order, followed by zero or more literals separated by commas. 
13. A STRIPS program consists of an initial state declaration, followed by a  goal declaration, followed by an action set.


This is the example used in the main function:

   Initial state: At(A), Level(low), BoxAt(C), BananasAt(B)
   
   Goal:    Have(Bananas)
   
   
   Actions:    
               
               // move from X to Y
               _Move(X, Y)_
               Preconditions:  At(X), Level(low)
               Effects: not At(X), At(Y)
               
               // climb up on the box
               _ClimbUp(Location)_
               Preconditions:  At(Location), BoxAt(Location), Level(low)
               Effects: Level(high), not Level(low)
               
               // climb down from the box
               _ClimbDown(Location)_
               Preconditions:  At(Location), BoxAt(Location), Level(high)
               Effects: Level(low), not Level(high)
               
               // move monkey and box from X to Y
               _MoveBox(X, Y)_
               Preconditions:  At(X), BoxAt(X), Level(low)
               Effects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)
               
               // take the bananas
               _TakeBananas(Location)_
               Preconditions:  At(Location), BananasAt(Location), Level(high)
               Effects: Have(bananas)
