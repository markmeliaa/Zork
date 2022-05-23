#include <iostream>
#include "world.h"

World::World()
{
	baseClock = clock();
}

World::~World()
{

}

// Send the written input into commands
bool World::Update(vector<string>& args)
{
	bool command = true;

	if (args.size() > 0 && args[0].length() > 0)
		command = SelectCommand(args);

	GameLoop();
	return command;
}

// Update the game each amount of time
void World::GameLoop()
{
	clock_t newClock = clock();

	if ((newClock - baseClock) / CLOCKS_PER_SEC > UPDATE_FREQUENCY)
	{
		baseClock = newClock;
	}
}

// Select the command from the list
bool World::SelectCommand(vector<string>& args)
{
	bool command = true;



	return command;
}