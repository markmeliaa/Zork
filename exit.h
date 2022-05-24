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

	const string& GetNameDirection(const Room* roomObj) const;
	Room* GetDestinationFromRoom(const Room* roomObj) const;

	bool locked;
	string oppName;
	Room* dest;
	Entity* key;
};

#endif // !ExitClass