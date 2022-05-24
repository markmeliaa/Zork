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

	// Look also the items inside items
	list<Entity*> itemsInObject;
	FindAllByType(EntityType::ITEM, itemsInObject);

	if (itemsInObject.size() > 0)
	{
		cout << "This object contains: " << "\n";
		for each (Entity* item in itemsInObject)
		{
			cout << item->name << "\n";
		}
	}
}

// Decide de value of the item (damage or defense) in a certain point
int Item::GetValue() const
{
	return Random(min_val, max_val);
}