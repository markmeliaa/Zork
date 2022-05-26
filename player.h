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
	virtual void Inventory() const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual bool Equip(const vector<string>& args);
	virtual bool Unequip(const vector<string>& args);
	/*
	virtual bool Lock(const vector<string>& args);
	virtual bool Unlock(const vector<string>& args);
	*/
};

#endif // !PlayerClass