#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"

Player::Player(const char* name, const char* desc, Room* room) :
	Creature(name, desc, room)
{
	type = EntityType::PLAYER;
}

Player::~Player()
{

}

bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetThisExit(args[1]);

	if (exit == NULL)
	{
		cout << "There is no exit direction " << args[1] << "\n";
		return false;
	}

	if (exit->locked)
	{
		cout << "That exit is locked, try finding the key.\n";
		return false;
	}

	cout << "You take direction " << exit->GetNameDirection((Room*)thisParent) << "\n";
	
	ChangeParentObject(exit->GetDestinationFromRoom((Room*)thisParent));
	
	thisParent->Look();

	return true;
}

void Player::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{
		for each (Entity * object in thisParent->thisChildren)
		{
			if ((object->name == args[1]) || object->type == EntityType::EXIT && args[1] == ((Exit*)object)->GetNameDirection((Room*)thisParent))
			{
				object->Look();
				return;
			}
		}

		if (args[1] == "me")
		{
			cout << name << "\n";
			cout << desc << "\n";
		}
	}

	else
	{
		thisParent->Look();
	}
}