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

//---------------------------------------
void Player::NothingTo(const string verb)
{
	string nothing = "Nothing to ";
	string nameInRoom = " with that name in this room.\n";
	string ret = nothing + verb + nameInRoom;

	cout << ret;
}

//------------------------------------
bool Player::WhatTo(const string verb)
{
	bool valid = false;

	list<string> validVerbs;
	validVerbs.push_back("buy");	validVerbs.push_back("Buy");
	validVerbs.push_back("close");	validVerbs.push_back("Close");
	validVerbs.push_back("drink");	validVerbs.push_back("Drink");
	validVerbs.push_back("drop");	validVerbs.push_back("Drop");
	validVerbs.push_back("kick");	validVerbs.push_back("Kick");
	validVerbs.push_back("move");	validVerbs.push_back("Move");
	validVerbs.push_back("open");	validVerbs.push_back("Open");
	validVerbs.push_back("press");	validVerbs.push_back("Press");
	validVerbs.push_back("read");	validVerbs.push_back("Read");
	validVerbs.push_back("throw");	validVerbs.push_back("Throw");

	string what = "";
	for (list<string>::const_iterator it = validVerbs.begin(); it != validVerbs.cend(); ++it)
	{
		if ((*it) == verb) {
			what = "What do you want to " + verb + "?\n";
			valid = true;
			break;
		}
	}

	cout << what;
	return valid;
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

//-----------------------------------------------
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

//----------------------
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

//---------------------------------
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

//---------------------------------
void Player::Move(const string obj)
{
	bool moved = false;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == ITEM && (*it)->name == obj)
		{
			Item* item = (Item*)(*it);
			moved = true;
			if (item->movable) 
			{
				cout << "You moved the " << item->name << "!\n";
				if (item->entitiesContained.size() == 0) 
				{
					cout << "But nothing happened.\n";
				}
				else 
				{
					cout << "Some items seem to have fallen from the " << item->name << ":\n";
					list<Entity*>::const_iterator items = item->entitiesContained.begin();
					while (item->entitiesContained.size() != 0)
					{
						cout << "- A " << (*items)->name << "\n";
						(*items)->ChangeLocation(location);
					}
				}
			}
			else 
			{
				cout << "This " << item->name << " is impossible to move!\n";
			}
			moved = true;
			break;
		}
	}
	if (!moved)
	{
		NothingTo("move");
	}
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
void Player::Put(const string obj, const string container)
{
	bool objectPutInPlace = false;
	Item* object = nullptr;

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it) 
	{
		if ((*it)->type == ITEM) 
		{
			Item* item = (Item*)(*it);
			if (item->name == obj) 
			{
				object = item;
				if (!item->pickable)
				{
					cout << "The " << item->name << " can't be moved!\n";
					break;
				}
			}
		}
	}
	if (object == nullptr)
	{
		for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				Item* item = (Item*)(*it);
				if (item->name == obj)
				{
					object = item;
					break;
				}
			}
		}
	}
	if (object != nullptr && (container == "player" || container == "me"))
	{
		objectPutInPlace = true;
		if (object->name == "heart") 
		{
			hasHeart = true;
			description2 = "You feel complete. You found what was missing.";
			cout << "The heart fit right in. You feel much better now, more complete.\n";
			object->~Item();
		}
		else
		{
			if (!hasHeart) 
			{
				cout << "This won't fill the void you feel inside.\n";
			}
			else 
			{
				cout << "You are already complete, no need to fill any void.\n";
			}
		}
		object = nullptr;
	}
	if (object != nullptr)
	{
		for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				Item* item = (Item*)(*it);
				if (item->name == container) 
				{
					objectPutInPlace = true;
					if (!item->pickable && item->movable && object->pickable)
					{
						object->ChangeLocation(item);
						cout << "The " << object->name << " was put in the " << item->name << "\n";
					}
					else 
					{
						cout << "You can't place objects in or on the " << item->name << "!\n";
					}
				}
			}
		}
	}
	if (!objectPutInPlace) 
	{
		cout << "No object was moved. Either the object or the container doesn't exist.\n";
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

//-----------------------------------------------------------------------
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