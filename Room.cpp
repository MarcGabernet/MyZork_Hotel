#include <iostream>
#include <list>
#include <string>
#include "Room.h"
#include "Item.h"

using namespace std;

//---------------
Room::~Room() {};

//---------------
Room::Room(const char* name, const char* description) :
	Entity(name, description, nullptr)
{
	type = ROOM;
};

//Description of the room and its entitites contained
void Room::Look() 
{
	Entity::Look();
	
	//The types are separated in different for-loops to organize the text better
	
	cout << "In this place there is:";
	bool itemsInRoom = false;

	//List of items
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			cout << "\n- A " << (*it)->name;
			itemsInRoom = true;
		}
	}
	if (!itemsInRoom) 
	{
		cout << "\nNothing";
	}
	cout << "\n";

	//List of NPC's
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		if ((*it)->type == NPC)
		{
			cout << "\nAlso, someone is here: The " << (*it)->name << "\n";
		}
	}

	//List of exits
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
	}

	cout << "\n";
}