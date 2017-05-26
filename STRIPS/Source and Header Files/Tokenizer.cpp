#include "libs.h"
#include "Structs.h"
#include "Helpers.h"

//TOP level function which will tokenize the STRIPS program passed in main.
vector<string> tokenize(string str)
{

	list<string> l;

	while (!isEmpty(str)) {
		if (commentChecker(str))
		{
			while ((str.at(0) != '\n') && (str.at(0) != '\r')) {  //Will delete comment until reaches EOL
				pop(str);
				if (isEmpty(str))
				{
					break;
				}
			}
			pop(str); //Once EOL is reached, the EOL characters are popped
			continue;
		}

		else if (tokenChecker(str))
		{ //Checks for tokens
			stringstream ss1, ss2;
			string temp;

			for (int i = 0; i < str.size();)
			{
				if (head(str))//If a white space, breaks from for loop
				{
					break;
				}

				else if (commentChecker(str))//If a comment, breaks from for loop
				{
					break;
				}

				else if ((str.at(0) == 40) || (str.at(0) == 41) || (str.at(0) == 44) || (str.at(0) == 95) || (str.at(0) == 58))
				{
					//This else-if checks for special tokens
					if (!isEmpty(temp))//If temp is not empty, then the current token stored in temp is pushed onto the list
					{
						l.push_back(temp);
					}

					ss2 << str.at(0); //Temps
					temp = ss2.str();
					pop(str);
					break;
				}
				else //Assumes is a token that is not special
				{
					ss1 << str.at(0);
					temp = ss1.str();
					pop(str);
				}

			}

			l.push_back(temp);
		}

		else if (head(str))
		{ //If the head is a whitespace character, it is popped
			whitespacePopper(str);
		}
	}

	vector<string> tokens{ begin(l), end(l) };  //Returns a vector of strings, as specified in instructions
	return tokens;
}

//If the head of the string is a whitespace character
bool head(string s)
{
	if (((9 <= s.at(0)) && (s.at(0) <= 13)) || (s.at(0) == 32))
	{
		return true;
	}

	return false;
}

//Pops the character at the 0th position from the input string.
void pop(string &s)
{
	s.erase(0, 1);
}

//Pops whitespace characters from string at 0th position
void whitespacePopper(string &s)
{
	if ((((9 <= s.at(0)) && (s.at(0) <= 13))) || (s.at(0) == 32))
	{
		pop(s);
	}
}

//Checks that the string at 0th position is a token
bool tokenChecker(string s)
{
	if ((s.at(0) == 40) || (s.at(0) == 41) || (s.at(0) == 44) || (s.at(0) == 95) || (s.at(0) == 58) || ((65 <= s.at(0)) && (s.at(0) <= 90)) || ((97 <= s.at(0)) && (s.at(0) <= 122)))
	{
		return true;
	}

	return false;
}

//Checks that the string at 0th position is a comment
bool commentChecker(string s)
{
	if (s.at(0) == '/')
	{
		return true;
	}

	return false;
}

//Checks if string is empty or not
bool isEmpty(string s)
{
	if (s.empty())
	{
		return true;
	}

	return false;
}