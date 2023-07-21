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
	cout << name << endl; 
	cout << "\n" << description;
	
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->description == "exit") 
			{
				cout << "\nTo the " << ex->GetDirection(this) << " there is the " << ex->GetDestination(this)->name;
			}
			else 
			{
				cout << "\nTo the " << ex->GetDirection(this) << " there is a " << ex->description << " that connects to the " << ex->GetDestination(this)->name;
			}
		}
		if ((*it)->type == ITEM)
		{
			//Exit* ex = (Exit*)*it;
			//cout << "\nTo the " << ex->GetDirection(this) << " there is the " << ex->GetDestination(this)->name;
		}
		if ((*it)->type == NPC)
		{
			//Exit* ex = (Exit*)*it;
			//cout << "\nTo the " << ex->GetDirection(this) << " there is the " << ex->GetDestination(this)->name;
		}
	}
	cout << "\n";
}