#include <iostream>
#include <list>
#include <string>
#include "Room.h"

using namespace std;

//---------------
Room::~Room() {};

//---------------
Room::Room(const char* name, const char* description) :
	Entity(name, description, NULL)
{
	type = ROOM;
};

void Room::Look() 
{
	cout << "\n" << name << endl; 
	cout << "\n" << description << endl;
	/*
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nTo the" << ex->GetDirection(this) << "there is " << ex->GetDestination(this)->name;
		}
	}*/
}