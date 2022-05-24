#include <iostream>
#include "exit.h"
#include "room.h"

Exit::Exit(const char* dir, const char* oppDir, const char* desc, Room* og, Room* dest) :
	Entity(dir, desc, (Entity*)og), locked(false), oppName(oppDir), dest(dest), key(NULL)
{
	type = EntityType::EXIT;

	dest->thisChildren.push_back(this);
}

Exit::~Exit()
{

}

void Exit::Look() const
{
	cout << "You look from " << name << " to " << oppName << "\n";
	cout << "You see a " << desc << "\n";
}

const string& Exit::GetNameDirection(const Room* roomObj) const
{
	if (roomObj == dest)
		return oppName;

	else
		return name;
}