#include <iostream>
#include "Entity.h"

using namespace std;

//-------------------
Entity::~Entity() 
{
	if (location != nullptr) 
	{
		location->entitiesContained.remove(this);
	}

};

//----------------------------------------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* location = nullptr) :
name(name), description(description), location(location)
{
	type = ENTITY;
	if (location != NULL) 
	{
		location->entitiesContained.push_back(this);
	}
};

//name and description of the entiry
//-----------------------------
void Entity::Look()
{
	cout << name << endl;
	cout << description << endl;

}

//changes the location of the entity ans also the list of entities containes of the previous and new location
//----------------------------------------------
void Entity::ChangeLocation(Entity* newLocation) 
{
	if (location != NULL)
		location->entitiesContained.remove(this);

	location = newLocation;

	newLocation->entitiesContained.push_back(this);
}