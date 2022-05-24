#include <iostream>
#include "world.h"
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"

World::World()
{
	baseClock = clock();

	// Create 5+ rooms
	Room* mountain = new Room("Mountain", "You see huge snowed peaks near you");
	Room* river = new Room("River", "You hear the course of the river running");
	Room* lake = new Room("Lake", "A small and calm lake with a pier");
	Room* bridge = new Room("Bridge", "Thanks to this bridge you can cross the river");
	Room* castle = new Room("Castle", "A huge and imponent castle stands before you");
	Room* crownRoom = new Room("Crown Room", "You see two golden thrones standing before you");
	Room* forest = new Room("Forest", "Around you there are multiple tall leafy trees");

	// Create the exits for those rooms
	Exit* exit1 = new Exit("up", "down", "Mountain slope", river, mountain);
	Exit* exit2 = new Exit("west", "east", "Little path", river, lake);
	Exit* exit3 = new Exit("up", "down", "White stone arch", bridge, river);
	Exit* exit4 = new Exit("west", "east", "Wall gate", castle, bridge);
	Exit* exit5 = new Exit("up", "down", "Large royal corridor", castle, crownRoom);
	exit5->locked = true;
	Exit* exit6 = new Exit("east", "west", "Sinister path", forest, castle);

	worldEntities.push_back(mountain);
	worldEntities.push_back(river);
	worldEntities.push_back(lake);
	worldEntities.push_back(bridge);
	worldEntities.push_back(castle);
	worldEntities.push_back(crownRoom);
	worldEntities.push_back(forest);

	worldEntities.push_back(exit1);
	worldEntities.push_back(exit2);
	worldEntities.push_back(exit3);
	worldEntities.push_back(exit4);
	worldEntities.push_back(exit5);
	worldEntities.push_back(exit6);

	// Create the Creatures
	Creature* king = new Creature("The King", "The abusive monarch of this realm", castle);
	king->health = 15;
	Creature* fisherman = new Creature("Fisherman", "A young guy that prevents you from fishing", lake);
	fisherman->health = 10;

	worldEntities.push_back(king);
	worldEntities.push_back(fisherman);

	// Create the key for the castle
	Item* castleKey = new Item("Brilliant Key", "A golden key, could be used to open something important", king);
	exit5->key = castleKey;

	// Create the Items
	Item* fishingRod = new Item("Basic Fishing Rod", "A rod made for fishing small fish", fisherman, ItemType::ATTACK);
	fishingRod->min_val = 2;
	fishingRod->max_val = 3;
	fisherman->AutoEquip();

	Item* treeBranch = new Item("Tree Branch", "A long, sharp branch that fell from a tree", mountain, ItemType::ATTACK);
	treeBranch->min_val = 1;
	treeBranch->max_val = 4;

	Item* royalShield = new Item("Royal Shield", "A shield with the royal family logo", king, ItemType::DEFENSE);
	royalShield->min_val = 1;
	royalShield->max_val = 3;
	king->AutoEquip();

	worldEntities.push_back(fishingRod);
	worldEntities.push_back(treeBranch);
	worldEntities.push_back(royalShield);
}

World::~World()
{
	for each (Entity* obj in worldEntities)
	{
		delete obj;
	}

	worldEntities.clear();
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

// Update the game objects each amount of time
void World::GameLoop()
{
	clock_t newClock = clock();

	if ((newClock - baseClock) / CLOCKS_PER_SEC > UPDATE_FREQUENCY)
	{
		for each (Entity* obj in worldEntities)
		{
			obj->Update();
		}

		baseClock = newClock;
	}
}

// Select the command from the list
bool World::SelectCommand(vector<string>& args)
{
	bool command = true;

	// Commands that can be performed

	return command;
}