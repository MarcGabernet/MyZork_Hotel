#include <iostream>
#include "Entity.h"

using namespace std;

//-------------------
Entity::~Entity() {};

//----------------------------------------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* location = NULL) :
name(name), description(description), location(location)
{
	type = ENTITY;
	if (location != NULL) 
	{
		location->entitiesContained.push_back(this);
	}
};

//-----------------------------
void Entity::Look()
{
	cout << name << endl;
	cout << description << endl;

}

//----------------------------------------------
void Entity::ChangeLocation(Entity* newLocation) 
{
	if (location != NULL)
		location->entitiesContained.remove(this);

	location = newLocation;

	newLocation->entitiesContained.push_back(this);
}
