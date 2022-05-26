#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

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
	if (!IsAlive())
		return false;

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
	if (!IsAlive())
		return;

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

void Player::Inventory() const
{
	if (!IsAlive())
		return;

	list<Entity*> inventoryItems;
	FindAllByType(EntityType::ITEM, inventoryItems);

	if (inventoryItems.size() == 0)
	{
		cout << "You don't own any item\n";
		return;
	}

	cout << "You own the following:\n";
	for each (Entity* item in inventoryItems)
	{
		if ((Item*)item == weaponEquiped)
			cout << item->name << " equiped as weapon\n";

		else if ((Item*)item == armourEquiped)
			cout << item->name << " equiped as armour\n";

		else
			cout << item->name << "\n";
	}
}

bool Player::Take(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	if (args.size() == 4)
	{
		// Pick something inside the room
		Item* item = (Item*)thisParent->FindObject(args[3], EntityType::ITEM);

		// Or pick something from inside an object that is inside the inventory
		if (item == NULL)
			item = (Item*)FindObject(args[3], EntityType::ITEM);

		if (item == NULL)
		{
			cout << "That object could not be found in either the room or the inventory, try again.\n";
			return false;
		}

		if (item->itemType != ItemType::CONTAINER)
		{
			cout << item->name << " is not a container, there can't be anything inside it.\n";
			return false;
		}

		Item* item2 = (Item*)item->FindObject(args[1], EntityType::ITEM);

		if (item2 == NULL)
		{
			cout << "That object could not be found inside " << item->name << ".\n";
			return false;
		}

		cout << "You took " << item2->name << " from " << item->name << ".\n";
		item2->ChangeParentObject(this);

		return true;
	}

	if (args.size() == 2)
	{
		Item* item = (Item*)thisParent->FindObject(args[1], EntityType::ITEM);

		if (item == NULL)
		{
			cout << "That object could not be found in the room.\n";
			return false;
		}

		cout << "You took " << item->name << " from the floor.\n";
		item->ChangeParentObject(this);

		return true;
	}

	return false;
}

bool Player::Drop(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	if (args.size() == 4)
	{
		Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

		if (item == NULL)
		{
			cout << "That object was not found in your inventory, try again\n";
			return false;
		}

		Item* destiny = (Item*)item->FindObject(args[3], EntityType::ITEM);

		if (destiny == NULL)
			destiny = (Item*)FindObject(args[3], EntityType::ITEM);

		if (destiny == NULL) 
		{
			cout << "The item where you try to deploy " << item->name << " was not found.\n";
			return false;
		}

		if (destiny->itemType != ItemType::CONTAINER) 
		{
			cout << "You can't throw anything inside " << destiny->name << ", it is not a container.\n";
			return false;
		}

		cout << "You threw the item " << item->name << " into " << destiny->name << ".\n";
		item->ChangeParentObject(destiny);

		return true;
	}

	if (args.size() == 2)
	{
		Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

		if (item == NULL)
		{
			cout << "That item was not found inside your inventory.\n";
			return false;
		}

		cout << "You threw " << item->name << " to the floor.\n";
		item->ChangeParentObject(thisParent);

		return true;
	}

	return false;
}

bool Player::Equip(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

	if (item == NULL)
	{
		cout << "You do not have that item, so you can't equip it.\n";
		return false;
	}

	switch (item->itemType)
	{
		case ItemType::ATTACK:
			weaponEquiped = item;
			break;

		case ItemType::DEFENSE:
			armourEquiped = item;
			break;

		default:
			cout << "That is not an equipable item.\n";
			return false;
	}

	cout << "You equiped " + item->name << " successfully.\n";
	return true;
}

bool Player::Unequip(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

	if (item == NULL)
	{
		cout << "You do not have that item, so you can't unequip it.\n";
		return false;
	}

	if (item == weaponEquiped)
	{
		weaponEquiped = NULL;
	}

	else if (item == armourEquiped)
	{
		armourEquiped = NULL;
	}

	else
	{
		cout << "You do not have that item equipped.\n";
		return false;
	}

	cout << "You unequip " << item->name << " successfully.\n";
	return true;
}