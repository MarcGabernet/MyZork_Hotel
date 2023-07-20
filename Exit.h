#ifndef _Exit
#define _Exit

#include <string>
#include <vector>

#include "Entity.h"

using namespace std;

class Room;

class Exit: public Entity
{
public:
	Exit(Room* origin, Room* destination, const char* direction, const char* oppositeName, bool isOpen, bool isLocked);
	~Exit();

	string GetDirection(Room* currentRoom);
	Room* GetDestination(Room* currentRoom);

public:
	Room* origin;
	Room* destination;
	string oppositeName;

	bool isOpen = true;
	bool isLocked = false;
};

#endif
