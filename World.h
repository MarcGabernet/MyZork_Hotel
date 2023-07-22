#ifndef _World
#define _World

#include <string>
#include <vector>
#include "Entity.h"
#include "Player.h"

#define DEFAULT_COLOR "\033[0m"
#define RED_TEXT "\033[31m"
#define YELLOW_TEXT "\033[33m"

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