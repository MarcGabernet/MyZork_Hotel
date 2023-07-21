#include <iostream>
#include <list>
#include <string>
#include "Item.h"

using namespace std;

//---------------
Item::~Item() {};

//---------------
Item::Item(const char* name, const char* description, Entity* location, bool drinkable, bool pickable, bool movable) :
	Entity(name, description, location),
	drinkable(drinkable), pickable(pickable), movable(movable)
{
	type = ITEM;
};
