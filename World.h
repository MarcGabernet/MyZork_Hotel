#ifndef _World
#define _World

#include <string>
#include <vector>
#include "Entity.h"
#include "Player.h"

using namespace std;

class World
{
public:
	World();
	~World();

	bool ExecuteCommand(const vector<string>& args);

public:
	vector<Entity*> things;
	Player* player;
};

#endif