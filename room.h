#ifndef RoomClass
#define RoomClass

#include "entity.h"

using namespace std;

class Exit;

class Room : public Entity
{
public:
	Room(const char* name, const char* desc);
	~Room();

	void Look() const;
	Exit* GetThisExit(const string& exitName) const;
};

#endif // !RoomClass