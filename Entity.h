#ifndef _Entity
#define _Entity

#include <string>
#include <list>

using namespace std; 

enum entityType
{
	ENTITY,
	NPC,
	PLAYER,
	EXIT,
	ROOM,
	ITEM
};

class Entity 
{
public:
	Entity(const char* name, const char* description, Entity* location);
	~Entity();

	virtual void Look();

	void ChangeLocation(Entity* newLocation);
	//void ChangeLocationOfAll(list<Entity*> objects, Entity* location);

public:
	entityType type;

	string name;
	string description;

	Entity* location;
	list<Entity*> entitiesContained;
};

#endif