#include <string>
#include <list>

using namespace std;

enum EntityTypes
{
	BASEENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity
{
public:
	Entity(const char* name, const char* desc, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Update();

	EntityTypes type;
	string name;
	string desc;

	Entity* thisParent;
	list<Entity*> thisChildren;
};