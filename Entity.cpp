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
/*
void ChangeLocationOfAll(list<Entity*> objects, Entity* location) 
{
	list<Entity*>::const_iterator items = objects.begin();
	while (objects.size() != 0)
	{
		cout << "- A " << (*items)->name << "\n";
		(*items)->ChangeLocation(location);
	}
}*/