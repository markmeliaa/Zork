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
{}