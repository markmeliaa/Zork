#include "room.h"
#include <iostream>
#include "exit.h"

Room::Room(const char* name, const char* desc) :
	Entity(name, desc, NULL)
{
	type = EntityType::ROOM;
}

Room::~Room()
{

}

// When looking a room, its exits, items and creatures are shown
void Room::Look() const
{
	cout << "You are now in: " << name << "\n";
	cout << desc << "\n";

	// Exits
	for each (Entity* obj in thisChildren)
	{
		if (obj->type == EntityType::EXIT)
		{

		}
	}

	// Items
	for each (Entity * obj in thisChildren)
	{
		if (obj->type == EntityType::ITEM)
		{

		}
	}

	// Creatures
	for each (Entity * obj in thisChildren)
	{
		if (obj->type == EntityType::CREATURE)
		{

		}
	}
}

// Retrieve the exit/s of a certain room
Exit* Room::GetThisExit(const string& exitName) const
{
	for each (Entity* object in thisChildren)
	{
		if (object->type == EntityType::EXIT)
		{
			Exit* exit = (Exit*) object;

			if (exit->GetNameDirection(this) == exitName)
				return exit;
		}
	}

	return NULL;
}