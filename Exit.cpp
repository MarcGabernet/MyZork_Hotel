#include <iostream>
#include "Exit.h"

using namespace std;

//-------------------
Exit::~Exit() {};

//-----------------------------------------------------------------------------------------------------------------------
Exit::Exit(Room* origin, Room* destination, const char* direction, const char* oppositeDirection, bool isOpen, bool isLocked) :
	Entity(direction, "exit", NULL),
	origin(origin), destination(destination), oppositeDirection(oppositeDirection), isOpen(isOpen), isLocked(isLocked)
{
	type = EXIT;
};

string Exit::GetDirection(Room* currentRoom)
{
	string currentDirection;
	if (currentRoom == origin) 
	{
		currentDirection = name;
	}
	else if (currentRoom == destination)
	{
		currentDirection = oppositeDirection;
	}
	return currentDirection;
}

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
}

