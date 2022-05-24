#ifndef EntityClass
#define EntityClass

#include <string>
#include <list>

using namespace std;

enum class EntityType
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
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Update();

public :
	EntityType type;
	string name;
	string desc;

	Entity* thisParent;
	list<Entity*> thisChildren;
};

#endif // !EntityClass
