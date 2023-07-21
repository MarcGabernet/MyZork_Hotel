#include <iostream>
#include <list>
#include <string>
#include "Item.h"

using namespace std;

//---------------
Item::~Item() {};

//---------------
Item::Item(const char* name, const char* description, Entity* location, bool drinkable, bool pickable) :
	Entity(name, description, location),
	drinkable(drinkable), pickable(pickable)
{
	type = ITEM;
};
