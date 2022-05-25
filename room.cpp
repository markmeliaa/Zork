#include "room.h"
#include <iostream>
#include "exit.h"
#include "item.h"
#include "creature.h"

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
			Exit* exit = (Exit*)obj;
			cout << "To the " << exit->GetNameDirection(this) << ", a " << exit->GetDestinationFromRoom(this)->name << " stands.\n";
		}
	}

	// Items
	for each (Entity * obj in thisChildren)
	{
		if (obj->type == EntityType::ITEM)
		{
			Item* item = (Item*)obj;
			cout << "You can see an item on the floor, a " << item->name << "\n";
		}
	}

	// Creatures
	for each (Entity * obj in thisChildren)
	{
		if (obj->type == EntityType::CREATURE)
		{
			Creature* creature = (Creature*)obj;
			cout << "A person stands there, the " << creature->name;

			if (!creature->IsAlive())
				cout << ", but it's dead...\n";
			else
				cout << "\n";
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