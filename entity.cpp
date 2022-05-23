#include <iostream>
#include "entity.h"

Entity::Entity(const char* name, const char* desc, Entity* thisParent = NULL) :
	name(name), desc(desc), thisParent(thisParent)
{
	type = BASEENTITY;

	// If this object has a parent, add it this to the parent's children
	if (thisParent != NULL)
		thisParent->thisChildren.push_back(this);
}

Entity::~Entity() 
{

}

void Entity::Look() const
{
	cout << "Name: " << name << "\n";
	cout << "Description: " << desc << "\n";
}

// Normally, an Entity does nothing on Update
void Entity::Update()
{

}