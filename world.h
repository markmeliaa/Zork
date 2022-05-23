#ifndef WorldClass
#define WorldClass

#include <string>
#include <vector>
#include <time.h>
#include <list>

#define UPDATE_FREQUENCY 0.5f

using namespace std;

class Entity;

class World
{
public:
	World();
	~World();

	bool Update(vector<string>& args);
	bool SelectCommand(vector<string>& args);
	void GameLoop();

private:
	clock_t baseClock;
	list<Entity*> worldEntities;
};

#endif //WorldClass