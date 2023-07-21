#include <iostream>
#include "Player.h"

using namespace std;

//-------------------
Player::~Player() {};

//-----------------------------------------------------------------------------------------------------------------------
Player::Player(const char* name, const char* description, Room* location) :
	Entity(name, description, (Entity*) location)
{
	type = PLAYER;
};

//--------------------------------------
void Player::Open(const string door)
{
	bool validName = false;

	if (door == " ") 
	{
		cout << "What do you want to open?\n";
		validName = true;
	}

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (!ex->isOpen && ex->description == door) 
			{
				if (!ex->isLocked) 
				{
					ex->isOpen = true;
					cout << "You opened the " << ex->description << "!\n";
				}
				else 
				{
					cout << "You can't open the " << ex->description << ", it's locked!\n";
				}
				validName = true;
				break;
			}
		}
	}
	if (!validName) 
	{
		cout << "This can't be opened\n";
	}
}

//----------------------------------------
void Player::Travel(const char* direction) 
{
	bool exitFound = false;
	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (direction == ex->GetDirection((Room*)location))
			{
				if (ex->isOpen)
				{
					ChangeLocation(ex->GetDestination((Room*)location));
					cout << location->name << "\n";
					exitFound = true;
				}
				else
				{
					cout << "The " << ex->description << " is closed!\n";
				}
				break;
			}
			
		}
	}
	if (!exitFound) 
	{
		cout << "You can't go this way!\n";
	}
}