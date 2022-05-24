#include <iostream>
#include "general.h"
#include "entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* desc, Entity* parent = NULL) :
name(name), desc(desc), thisParent(parent)
{
	type = EntityType::BASEENTITY;

	if(parent != NULL)
		parent->thisChildren.push_back(this);
}

// ----------------------------------------------------
Entity::~Entity()
{}

// ----------------------------------------------------
void Entity::Look() const
{
	cout << name << "\n";
	cout << desc << "\n";
}

// ----------------------------------------------------
void Entity::Update()
{

}

// Change one object to one parent to other
void Entity::ChangeParentObject(Entity* changeTo)
{
	if (thisParent != NULL)
		thisParent->thisChildren.remove(this);

	thisParent = changeTo;

	if (thisParent != NULL)
		thisParent->thisChildren.push_back(this);
}

// Search objects in several situations
bool Entity::FindObject(Entity* object) const
{
	bool returned = false;

	for each (Entity* child in thisChildren) 
	{
		if (child == object)
			returned = true;
	}

	return returned;
}

Entity* Entity::FindObject(EntityType type) const
{
	for each (Entity* child in thisChildren)
	{
		if (child->type == type)
			return child;
	}

	return NULL;
}

Entity* Entity::FindObject(const string& name, EntityType type) const
{
	for each (Entity* child in thisChildren)
	{
		if (child->type == type && child->name == name)
			return child;
	}

	return NULL;
}

void Entity::FindAllByType(EntityType type, list<Entity*>& objectContainer) const
{
	for each (Entity* child in thisChildren)
	{
		if (child->type == type)
			objectContainer.push_back(child);
	}
}