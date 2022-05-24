#ifndef ExitClass
#define ExitClass

#include "entity.h"

class Room;

using namespace std;

class Exit : public Entity
{
public:
	Exit(const char* dir, const char* oppDir, const char* desc, Room* og, Room* dest);
	~Exit();

	void Look() const;

	bool locked;
	string oppName;
	Room* dest;
	Entity* key;
};

#endif // !ExitClass