#include <string>
#include <vector>
#include <time.h>

#define UPDATE_FREQUENCY 0.5f

using namespace std;

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
};