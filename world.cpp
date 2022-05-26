#include <iostream>
#include "world.h"
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "player.h"

World::World()
{
	baseClock = clock();

	// Create 5+ rooms
	Room* mountain = new Room("Mountain", "You see huge snowed peaks around you");
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
	Exit* exit6 = new Exit("west", "east", "Sinister path", forest, castle);

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
	Creature* king = new Creature("king", "The abusive monarch of this realm", castle);
	king->health = 15;
	Creature* fisherman = new Creature("fisherman", "A young guy that prevents you from fishing", lake);
	fisherman->health = 10;

	worldEntities.push_back(king);
	worldEntities.push_back(fisherman);

	// Create the key for the castle
	Item* castleKey = new Item("key", "A golden key, could be used to open something important", bridge);
	exit5->key = castleKey;

	// Create the Items
	Item* rod = new Item("rod", "Made for fishing small fish", fisherman, ItemType::ATTACK);
	rod->min_val = 2;
	rod->max_val = 3;
	fisherman->AutoEquip();

	Item* branch = new Item("branch", "A long, sharp branch that fell from a tree", mountain, ItemType::ATTACK);
	branch->min_val = 1;
	branch->max_val = 4;

	Item* shield = new Item("shield", "A shield with the royal family logo", king, ItemType::DEFENSE);
	shield->min_val = 1;
	shield->max_val = 3;
	king->AutoEquip();

	worldEntities.push_back(rod);
	worldEntities.push_back(branch);
	worldEntities.push_back(shield);

	// Create the Player
	mainChar = new Player("Hero", "The one chosen by the legend", mountain);
	mainChar->health = 20;
	worldEntities.push_back(mainChar);
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
	switch (args.size())
	{
		case 1:
		{
			if (args[0] == "look" || args[0] == "l")
				mainChar->Look(args);

			else if (args[0] == "north" || args[0] == "n")
			{
				args.push_back("north");
				mainChar->Go(args);
			}

			else if (args[0] == "east" || args[0] == "e")
			{
				args.push_back("east");
				mainChar->Go(args);
			}

			else if (args[0] == "south" || args[0] == "s")
			{
				args.push_back("south");
				mainChar->Go(args);
			}

			else if (args[0] == "west" || args[0] == "w")
			{
				args.push_back("west");
				mainChar->Go(args);
			}

			else if (args[0] == "down" || args[0] == "d")
			{
				args.push_back("down");
				mainChar->Go(args);
			}

			else if (args[0] == "up" || args[0] == "u")
			{
				args.push_back("up");
				mainChar->Go(args);
			}

			else if (args[0] == "inventory")
				mainChar->Inventory();

			else
				command = false;
			break;
		}

		case 2: 
		{
			if (args[0] == "look" || args[0] == "l")
				mainChar->Look(args);

			else if (args[0] == "go")
				mainChar->Go(args);

			else if (args[0] == "take" || args[0] == "grab")
				mainChar->Take(args);

			else if (args[0] == "drop" || args[0] == "throw")
				mainChar->Drop(args);

			else if (args[0] == "equip")
				mainChar->Equip(args);

			else if (args[0] == "unequip")
				mainChar->Unequip(args);

			else
				command = false;
			break;
		}

		case 3:
		{
			command = false;
			break;
		}

		case 4:
		{
			if (args[0] == "take" || args[0] == "grab")
				mainChar->Take(args);

			else if (args[0] == "drop" || args[0] == "throw")
				mainChar->Drop(args);

			else
				command = false;
			break;
		}

		default:
			command = false;
			break;
	}

	return command;
}