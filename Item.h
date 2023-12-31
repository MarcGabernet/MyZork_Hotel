#ifndef _Item
#define _Item

#include <string>
#include <list>

#include "Entity.h"

using namespace std;

class Item : public Entity
{
public:
	Item(const char* name, const char* description, const char* readableInfo, Entity* location, bool drinkable, bool pickable, bool movable);
	~Item();

public:
	bool drinkable;
	bool pickable;
	bool movable;
	const char* readableInfo;

	int drinkingEffect = 0;
};

#endif

