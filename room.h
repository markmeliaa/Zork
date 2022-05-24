#ifndef RoomClass
#define RoomClass

#include "entity.h"

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* desc);
	~Room();

	void Look() const;
};

#endif // !RoomClass