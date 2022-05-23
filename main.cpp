#include <iostream>
#include <conio.h>
#include <vector>
#include "general.h"
#include "world.h"

using namespace std;

#define BOLDYELLOW_ "\033[1m\033[33m"
#define ENDCOLORING "\033[0m"

// The main game loop
int main() 
{
	char typed;
	string player_input;

	vector<string> args;
	args.reserve(5);

	World newWorld;

	cout << BOLDYELLOW_ "WELCOME to Marc's personal ZORK!" ENDCOLORING << endl;

	while (1) 
	{
		if (_kbhit() != 0)
		{
			// Take record of what the user is typing
			typed = _getch();

			if (typed == '\b') // Delete what is typed
			{
				if (player_input.length() > 0) 
				{
					player_input.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}

			else if (typed != '\r') // Write everyting until enter is pressed
			{
				player_input += typed;
				cout << typed;
			}

			else
			{
				Split(player_input, args);
				cout << "\n";

				/*
				for each (string var in args) 
				{
					cout << "\n";
					cout << var;
				}
				cout << "\n";
				*/
			}
		}

		if (args.size() > 0 && args[0] == "quit")
			break;

		if (!newWorld.Update(args))
			cout << "Sorry, I did not understand you, please repeat again.\n";

		if (args.size() > 0)
		{
			player_input = "";
			args.clear();
		}
	}

	cout << "Thank you for playing, see you again!\n";
	return 0;
}