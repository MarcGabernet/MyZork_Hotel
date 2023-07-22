#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

//-------------------
Player::~Player() {};

//--------------------------------------------------------------------------------------------
Player::Player(const char* name, const char* description, string description2, Room* location) :
	Entity(name, description, (Entity*) location), 
	description2(description2)
{
	type = PLAYER;
};

//-------------------------------
void Player::NothingTo(const string verb)
{
	string nothing = "Nothing to ";
	string nameInRoom = " with that name in this room";
	string ret = nothing + verb + nameInRoom;

	cout << ret << "\n";
}

//------------------
void Player::Close()
{
	cout << "What do you want to close?\n";
}

//----------------------------------
void Player::Close(const string door)
{
	bool validName = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->isOpen && ex->description == door && door != "exit")
			{
				ex->isOpen = false;
				cout << "You closed the " << ex->description << "!\n";
				validName = true;
				break;
			}
		}
	}
	if (!validName)
	{
		NothingTo("close");
	}
}

//---------------------------------
void Player::Drop(const string obj, bool dropped)
{
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		if ((*it)->name == obj) 
		{
			Item* item = (Item*)(*it);
			item->ChangeLocation((Entity*)location);
			cout << "The " << item->name << " is now in the " << location->name << "\n";
			dropped = true;
			break;
		}
	}
	if (!dropped) 
	{
		cout << "There is nothig with that name in your inventory to be dropped!\n";
	}
}

//----------------------------------
void Player::Inventory()
{
	cout << "In you inventory you currently have:\n";
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
	{
		cout << "- " << (*it)->name << "\n";
	}
	if (entitiesContained.size() == 0) {
		cout << "- Nothing\n";
	}
	if (!hasHeart) 
	{
		cout << "\nYou seem to lack a more important thing than mateiral objects.\n";
	}
	else 
	{
		cout << "\nYou have also found your heart and returned it to its place. You don't feel so empty.\n";
	}
}

//----------------------------------
void Player::Kick(const string obj)
{
	bool kicked = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->description == obj)
			{
				kicked = true;
				if (ex->isOpen == true)
				{
					cout << "Why would you kick the " << ex->description << "? It's already open!\n";
					break;
				}
				else if(ex->isLocked == false || (ex->isLocked == true && ex->key == NULL))
				{
					cout << "You kicked the " << ex->description << " so hard it opened!\n";
					ex->isLocked = false;
					ex->isOpen = true;
					break;
				}
				else if(ex->isLocked == true && ex->key != NULL)
				{
					cout << "Even kicking the " << ex->description << " won't open it! It looks like you need a key.\n";
					break;
				}
			}
		}
		else 
		{
			if ((*it)->name == obj) 
			{
				cout << "Kicking the " << (*it)->name << " won't do anything.\n";
				kicked = true;
				break;
			}
		}
	}
	if (!kicked) 
	{
		NothingTo("kick");
	}
}

//-----------------
void Player::Look() 
{
	Entity::Look();
	cout << description2 << "\n";
}

//-----------------
void Player::Look(const string obj)
{
	bool looked = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type != EXIT && (*it)->name == obj)
		{
			(*it)->Look();
			looked = true;
			break;
		}
	}
	if (!looked) 
	{
		NothingTo("look at");
	}
}

//-------------------
void Player::Open()
{
	cout << "What do you want to open?\n";
}

//----------------------------------
void Player::Open(const string door)
{
	bool validName = false;

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
		NothingTo("open");
	}
}

//-----------------------------------
void Player::PickUp(const string obj) 
{
	bool pickedUp = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			if (item->name == obj) {
				pickedUp = true;
				if (item->pickable == true)
				{
					cout << "You picked up the " << item->name << "!\n";
					item->ChangeLocation(this);
					break;
				}
				else 
				{
					cout << "How are you going to pick up a " << item->name << "? Can't be done.\n";
					break;
				}
			}
			
		}
	}
	if (!pickedUp) 
	{
		NothingTo("pick up");
	}
}

//---------------------------------
void Player::Read(const string obj)
{
	bool red = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			if (item->name == obj)
			{
				red = true;
				if (item->readableInfo == nullptr) 
				{
					cout << "There is nothing to read on the " << item->name << "\n";
					break;
				}
				else 
				{
					cout << item->readableInfo << "\n";
					break;
				}
			}
		}
	}
	if (!red)
	{
		NothingTo("read");
	}
}


bool Player::ThrowingFrom(const string obj, list<Entity*> listOfEntities)
{
	bool thrown = false;

	for (list<Entity*>::const_iterator it = listOfEntities.begin(); it != listOfEntities.cend(); ++it)
	{
		if ((*it)->name == obj)
		{
			Item* item = (Item*)(*it);
			cout << "You threw the " << item->name << " across the room!\n";
			thrown = true;
			if (!item->drinkable)
			{
				cout << "Nothing nappened.\n";
			}
			else
			{
				cout << "The " << item->name << " broke!\n";
				item->~Item();
			}
			break;
		}
	}
	return thrown;
}

//----------------------------------
void Player::Throw(const string obj) 
{
	bool thrown = false;

	thrown = ThrowingFrom(obj,location->entitiesContained);
	if (!thrown) 
	{
		thrown = ThrowingFrom(obj, entitiesContained);
		if (thrown)
		{
			Drop(obj,true);
		}
		else 
		{
			NothingTo("throw");
		}
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