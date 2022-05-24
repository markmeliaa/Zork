#include "item.h"
#include <iostream>
#include "general.h"

Item::Item(const char* name, const char* desc, Entity* parent, ItemType itemType) :
	Entity(name, desc, parent), itemType(itemType)
{
	type = EntityType::ITEM;
	min_val = 0;
	max_val = 0;
}

Item::~Item()
{

}

void Item::Look() const
{
	cout << "Item named: " << name << "\n";
	cout << desc << "\n";
}

int Item::GetValue() const
{
	return Random(min_val, max_val);
}