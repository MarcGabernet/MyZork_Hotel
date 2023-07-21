#ifndef _Exit
#define _Exit

#include <string>
#include <vector>

#include "Entity.h"
#include "Item.h"

using namespace std;

class Room;

class Exit: public Entity
{
public:
	Exit(Room* origin, Room* destination, const char* direction, const char* oppositeName, bool isOpen, bool isLocked, Item* key);
	~Exit();

	string GetDirection(Room* currentRoom);
	Room* GetDestination(Room* currentRoom);

public:
	Room* origin;
	Room* destination;
	string oppositeName;

	bool isOpen = true;
	bool isLocked = false;

	//necessary key to open the exit if locked
	Item* key;
};

#endif
