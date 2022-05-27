#include <iostream>
#include "creature.h"
#include "exit.h"
#include "room.h"
#include "item.h"
#include "general.h"

Creature::Creature(const char* name, const char* desc, Room* room) :
	Entity(name, desc, (Entity*)room)
{
	type = EntityType::CREATURE;
	health = 5;
	min_dmg = max_dmg = min_protec = max_protec = 0;
	weaponEquiped = NULL;
	armourEquiped = NULL;
	fightTarget = NULL;
	battleTurn = 1;
}

Creature::~Creature()
{

}

void Creature::Update()
{
	if (fightTarget != NULL)
	{
		// Real-time combat

		if (thisParent->FindObject(fightTarget) == true && IsAlive() && fightTarget->IsAlive())
		{
			cout << "------------------ TURN " << battleTurn << " ------------------\n";
			Attacking();
			battleTurn++;
		}

		else
		{
			fightTarget = NULL;
			battleTurn = 1;
		}
	}
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

bool Creature::Attack(const vector<string>& args)
{
	Creature* creat = (Creature*)thisParent->FindObject(args[1], EntityType::CREATURE);

	if (creat == NULL)
		return false;

	fightTarget = creat;
	cout << name << " starts attacking " << creat->name << ".\n";

	return true;
}

int Creature::Attacking()
{
	if (!IsAlive() || !fightTarget->IsAlive())
	{
		fightTarget = fightTarget->fightTarget = NULL;
		return false;
	}

	int attackVal = weaponEquiped ? weaponEquiped->GetValue() : Random(min_dmg, max_dmg);

	if (PlayerInRoom())
		cout << name << " attacks " << fightTarget->name << " and inflicts " << attackVal << " points of damage.\n";

	fightTarget->Defending(attackVal);

	if (fightTarget->fightTarget == NULL)
		fightTarget->fightTarget = this;

	return attackVal;
}

int Creature::Defending(const int& damage)
{
	int defenseVal = armourEquiped ? armourEquiped->GetValue() : Random(min_protec, max_protec);
	cout << name << " defends himself with " << defenseVal << " points of protection.\n";

	int finalDamage = damage - defenseVal;
	if (finalDamage < 0)
		finalDamage = 0;

	health -= finalDamage;
	if (health < 0)
		health = 0;

	if (PlayerInRoom())
		cout << name << " finally gets attacked with " << finalDamage << " points of damage.\n";

	if (!IsAlive())
		Die();

	return finalDamage;
}