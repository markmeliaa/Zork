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

	virtual bool Attack(const vector<string>& args);
	virtual int Attacking();
	virtual int Defending(const int& damage);

	virtual void Inventory() const;
	virtual bool AutoEquip();
	virtual void Die() const;
	virtual void Stats() const;

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
	int battleTurn;
};

#endif // !CreatureClass