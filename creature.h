#ifndef CreatureClass
#define CreatureClass

#include "entity.h"
#include <vector>

using namespace std;

class Room;
class Item;

class Creature : public Entity
{
public:
	Creature(const char* name, const char* desc, Room* room);
	~Creature();

	virtual bool Go(const vector<string>& args);
	virtual void Look() const;
	virtual void Inventory() const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual bool Equip(const vector<string>& args);
	virtual bool Unequip(const vector<string>& args);
	virtual bool AutoEquip();
	virtual bool Lock(const vector<string>& args);
	virtual bool Unlock(const vector<string>& args);

	virtual void Update();
	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

	int health;
	int min_dmg;
	int max_dmg;
	int min_protec;
	int max_protec;
	Creature* fightTarget;
	Item* weaponEquiped;
	Item* armourEquiped;
};

#endif // !CreatureClass