#include <iostream>
#include "creature.h"
#include "exit.h"
#include "room.h"
#include "item.h"

Creature::Creature(const char* name, const char* desc, Room* room) :
	Entity(name, desc, (Entity*)room)
{
	type = EntityType::CREATURE;
	health = 5;
	min_dmg = max_dmg = min_protec = max_protec = 0;
	weaponEquiped = NULL;
	armourEquiped = NULL;
	fightTarget = NULL;
}

Creature::~Creature()
{

}

void Creature::Update()
{
	if (fightTarget != NULL)
	{
		// Real-time combat
	}
}

void Creature::Look() const
{
	if (IsAlive())
	{
		cout << "This creature name is: " << name << "\n";
		cout << desc << "\n";
	}

	else
	{
		cout << "Here lies the corpse of: " << name << "\n";
		cout << desc << "\n";
	}
}

bool Creature::Go(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetThisExit(args[1]);

	// There is no exit
	if (exit == NULL)
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " goes to " << args[1] << "\n";

	ChangeParentObject(exit->GetDestinationFromRoom((Room*)thisParent));
	return true;
}

bool Creature::Take(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	// Pick up an item from a room
	Item* item = (Item*)thisParent->FindObject(args[1], EntityType::ITEM);

	if (args.size() > 1)
	{
		// Or pick up an item from an item in the inventory
		if (item == NULL)
			item = (Item*)FindObject(args[1], EntityType::ITEM);

		if (item == NULL)
			return false;

		Item* item2 = (Item*)item->FindObject(args[3], EntityType::ITEM);

		if (item2 == NULL)
			return false;

		if (PlayerInRoom())
			cout << "The character " << name << " looks into " << item->name << ".\n";

		item = item2;
	}

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " takes " << item->name << ".\n";

	item->ChangeParentObject(this);

	return true;
}

void Creature::Inventory() const
{
	list<Entity*> carriedItems;
	FindAllByType(EntityType::ITEM, carriedItems);

	if (carriedItems.size() == 0)
	{
		cout << "The character " << name << " does not own any item\n";
		return;
	}

	cout << "The " << name << " owns:\n";
	for each (Entity * item in carriedItems)
	{
		if (item == weaponEquiped)
			cout << item->name << " (equiped as a weapon)\n";
		else if (item == armourEquiped)
			cout << item->name << " (equiped as armour)\n";
		else
			cout << item->name << "\n";
	}
}

bool Creature::Drop(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " drops " << item->name << "\n";

	item->ChangeParentObject(thisParent);

	return true;
}

bool Creature::AutoEquip()
{
	if (!IsAlive())
		return false;

	list<Entity*> creatureInventory;
	FindAllByType(EntityType::ITEM, creatureInventory);

	for each (Entity* item in creatureInventory)
	{
		Item* realItem = (Item*)item;

		if (realItem->itemType == ItemType::ATTACK)
			weaponEquiped = realItem;
		else if (realItem->itemType == ItemType::DEFENSE)
			armourEquiped = realItem;
	}

	return true;
}

bool Creature::Equip(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

	if (item == NULL)
		return false;

	switch (item->itemType)
	{
		case ItemType::ATTACK:
			weaponEquiped = item;
			break;

		case ItemType::DEFENSE:
			armourEquiped = item;
			break;

		default:
			return false;
	}

	if (PlayerInRoom())
		cout << "The character " << name << " equips " << item->name << ".\n";

	return true;
}

bool Creature::Unequip(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)FindObject(args[1], EntityType::ITEM);

	if (item == NULL)
		return false;

	if (item == weaponEquiped)
		weaponEquiped = NULL;

	else if (item == armourEquiped)
		armourEquiped = NULL;

	else
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " unequips " << item->name << ".\n";

	return true;
}

bool Creature::Lock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetThisExit(args[1]);

	if (exit == NULL || exit->locked == true)
		return false;

	Item* item = (Item*)FindObject(args[3], EntityType::ITEM);

	if (exit == NULL || exit->key != item)
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " locks " << exit->GetNameDirection((Room*)thisParent) << "\n";

	exit->locked = true;
	return true;
}

bool Creature::Unlock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetThisExit(args[1]);

	if (exit == NULL || exit->locked == true)
		return false;

	Item* item = (Item*)FindObject(args[3], EntityType::ITEM);

	if (exit == NULL || exit->key != item)
		return false;

	if (PlayerInRoom())
		cout << "The character " << name << " unlocks " << exit->GetNameDirection((Room*)thisParent) << "\n";

	exit->locked = false;
	return true;
}

Room* Creature::GetRoom() const
{
	return (Room*)thisParent;
}

bool Creature::PlayerInRoom() const
{
	return thisParent->FindObject(EntityType::PLAYER) != NULL;
}

bool Creature::IsAlive() const
{
	return health > 0;
}

void Creature::Die() const
{
	if (PlayerInRoom())
		cout << "The " << name << " died.\n";
}

void Creature::Stats() const
{
	//cout << name << "\n";
	cout << "Health: " << health << "\n";
	
	if (weaponEquiped != NULL) 
	{
		cout << "Attack values: (" << weaponEquiped->name
			<< "), Min Attack: " << weaponEquiped->min_val
			<< ", Max Attack: " << weaponEquiped->max_val << ".\n";
	}

	else
	{
		cout << "Attack values: Min Attack: " << min_dmg << ", Max Attack: " << max_dmg << ".\n";
	}

	if (armourEquiped != NULL)
	{
		cout << "Defense values: (" << armourEquiped->name
			<< "), Min Defense: " << armourEquiped->min_val
			<< ", Max Defense: " << armourEquiped->max_val << ".\n";
	}

	else
	{
		cout << "Defense values: Min Defense: " << min_protec << ", Max Defense: " << max_protec << ".\n";
	}
}