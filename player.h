#ifndef PlayerClass
#define PlayerClass

#include "creature.h"

using namespace std;

class Player : public Creature
{
public:
	Player(const char* name, const char* desc, Room* room);
	~Player();

	bool Go(const vector<string>& args);
	void Look(const vector<string>& args) const;
	void Inventory() const;
	bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	bool Equip(const vector<string>& args);
	bool Unequip(const vector<string>& args);
	bool Lock(const vector<string>& args);
	bool Unlock(const vector<string>& args);
	bool Examine(const vector<string>& args);
	/*
	bool Attack(const vector<string>& args);
	bool Loot(const vector<string>& args);
	*/
};

#endif // !PlayerClass