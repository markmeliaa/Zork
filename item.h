#ifndef ItemClass
#define ItemClass

#include "entity.h"

using namespace std;

enum class ItemType
{
	COMMON,
	ATTACK,
	DEFENSE,
	CROWN,
	CONTAINER,
	FISH,
	FOOD,
	FISHFOOD
};

class Item : public Entity
{
public:
	Item(const char* name, const char* desc, Entity* parent, ItemType itemType = ItemType::COMMON);
	~Item();

	void Look() const;
	int GetValue() const;

	int min_val;
	int max_val;
	ItemType itemType;
	int healthRestored;
};

#endif // !ItemClass
