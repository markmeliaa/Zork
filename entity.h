#include <string>
#include <list>

using namespace std;

enum EntityTypes
{
	BASEENTITY,
	ROOM
};

class Entity
{
public:
	Entity(const char* name, const char* desc, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Update();

private:
	EntityTypes type;
	string name;
	string desc;

	Entity* thisParent;
	list<Entity*> thisChildren;
};