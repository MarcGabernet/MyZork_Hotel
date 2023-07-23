#include <iostream>
#include "Exit.h"
#include "Room.h"

using namespace std;

//-------------------
Exit::~Exit() {};

//-----------------------------------------------------------------------------------------------------------------------
Exit::Exit(Room* origin, Room* destination, const char* direction, const char* oppositeName, bool isOpen, bool isLocked, Item* key) :
	Entity(direction, "exit", nullptr),
	origin(origin), destination(destination), oppositeName(oppositeName), isOpen(isOpen), isLocked(isLocked), key(key)
{
	type = EXIT;
	origin->entitiesContained.push_back(this);
	destination->entitiesContained.push_back(this);
};

//Given a room next to you, gives the direction to take to get there
//------------------------------------------
string Exit::GetDirection(Room* currentRoom)
{
	string currentDirection;
	if (currentRoom == origin) 
	{
		currentDirection = name;
	}
	else if (currentRoom == destination)
	{
		currentDirection = oppositeName;
	}
	return currentDirection;
}

//Returns the destination of the room that connects to the room you're in
//-------------------------------------------
Room* Exit::GetDestination(Room* currentRoom)
{
	if (currentRoom == origin)
	{
		return destination;
	}
	else if (currentRoom == destination)
	{
		return origin;
	}
	else 
	{
		return nullptr;
	}
}

