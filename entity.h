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
	void ChangeParentObject(Entity* changeTo);

	bool FindObject(Entity* object) const;
	Entity* FindObject(EntityType type) const;
	Entity* FindObject(const string& name, EntityType type) const;
	void FindAllByType(EntityType type, list<Entity*>& objectContainer) const;
	

public :
	EntityType type;
	string name;
	string desc;

	Entity* thisParent;
	list<Entity*> thisChildren;
};

#endif // !EntityClass
