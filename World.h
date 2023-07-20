#ifndef _World
#define _World

#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

class World
{
public:
	World();
	~World();

public:
	vector<Entity*> things;
};

#endif