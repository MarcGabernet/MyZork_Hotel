#include <iostream>
//#include<cstdio>
//#include<ctime>
#include <string>
#include <random>

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
			cout << "What do you want to " + verb + "?\n";
			valid = true;
			break;
		}
	}
	return valid;
}

//------------------------------------------------------------------------------------------
Entity* Player::FindInList(const string name, list<Entity*> entities, entityType objectType)
{
	for (list<Entity*>::const_iterator it = entities.begin(); it != entities.cend(); ++it)
	{
		if (((*it)->name == name && ((*it)->type == objectType || (*it)->type == ENTITY)) || ((*it)->description == name && (*it)->type == EXIT))
		{
			return (*it);
		}
	}
	return nullptr;
}

void Player::Timer(float seconds) 
{
	seconds *= CLOCKS_PER_SEC;

	clock_t now = clock();

	while (clock() - now < seconds);
}

//-----------------------------------------------
void Player::Buy(const string drink, const string paymentMethod, bool paying) 
{
	Npc* bartender = (Npc*)FindInList("bartender", location->entitiesContained, NPC);
	if (bartender != nullptr && drink == "drink")
	{
		cout << "\033[31mBartender:\033[0m ";
		if (bartender->entitiesContained.size() == 0)
		{
			cout << "You already bought a drink, why would you want more?\n";
		}
		else if(!paying)
		{
			cout << "How are you going to pay? Do you think this is free?\n";
		}
		else 
		{
			if (paymentMethod == "card") 
			{
				cout << "Very well. Here's your drink, take it if you want.\n";
				cout << "The bartender left the drink on the counter.\n";
				Item* item = (Item*)FindInList(drink, bartender->entitiesContained, ITEM);
				item->ChangeLocation(location);
			}
			else 
			{
				cout << "What do you think this establishment is? I'm not going to accept a " << paymentMethod << " as payment method!\n";
			}
		}
	}
	else 
	{
		NothingTo("buy");
	}
}

//--------------------------------------------------------
void Player::BuyWith(const string drink, const string obj)
{
	Item* paymentMethod = (Item*)FindInList(obj, entitiesContained, ITEM);
	if (paymentMethod == nullptr)
	{
		paymentMethod = (Item*)FindInList(obj, location->entitiesContained, ITEM);
	}
	if (paymentMethod != nullptr) 
	{
		Buy(drink, paymentMethod->name, true);
	}
	else 
	{
		cout << "The item you are trying to use as payment method doesn't exist!\n";
	}
}

//----------------------------------
void Player::Close(const string door)
{
	Exit* ex = (Exit*)FindInList(door, location->entitiesContained, EXIT);
	if (ex != nullptr)
	{
		if (door != "exit") 
		{
			if (ex->isOpen)
			{
				ex->isOpen = false;
				cout << "You closed the " << door << "!\n";
			}
			else 
			{
				cout << "The " << door << " is already closed!\n";
			}
		}
		else 
		{
			NothingTo("close");
		}
	}
	else
	{
		NothingTo("close");
	}

	for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			
		}
	}
}

//------------------------------------
void Player::Drink(const string drink)
{
	Item* item = (Item*)FindInList(drink, entitiesContained,ITEM);
	if (item == nullptr) 
	{
		item = (Item*)FindInList(drink, location->entitiesContained, ITEM);
	}
	if (item != nullptr)
	{
		if (item->drinkable)
		{
			int result = item->drinkingEffect + control;
			if (result <= 10 && result >= 1)
			{
				cout << "You took a sip of the " << drink << "!\nIt had some effect on you.\n";
				control = result;
			}
			else if (result == 0)
			{
				cout << "If you take another sip you might collapse.\n";
			}
			else
			{
				cout << "No need to drink more, you feel great.\n";
			}
		}
		else
		{
			cout << "You can't drink that!\n";
		}
	}
	else
	{
		NothingTo("drink");
	}
}

//------------------------------------------------------------------------
void Player::Drop(const string obj, bool dropped, bool throwingAtSometing)
{
	Item* item = (Item*)FindInList(obj, entitiesContained, ITEM);
	if (item != nullptr) 
	{
		item->ChangeLocation((Entity*)location);
		if (!throwingAtSometing && !dropped)
		{
			cout << ".\n";
		}
		if (!dropped)
		{
			cout << "The " << obj << " is now in the " << location->name << ".\n";
		}
	}
	else
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
	Exit* ex = (Exit*)FindInList(obj, location->entitiesContained, EXIT);
	if (ex != nullptr)
	{
		if (ex->isOpen == true)
		{
			cout << "Why would you kick the " << ex->description << "? It's already open!\n";
		}
		else if (ex->isLocked == false || (ex->isLocked == true && ex->key == NULL))
		{
			cout << "You kicked the " << ex->description << " so hard it opened!\n";
			ex->isLocked = false;
			ex->isOpen = true;
		}
		else if (ex->isLocked == true && ex->key != NULL)
		{
			cout << "Even kicking the " << ex->description << " won't open it! It looks like you need a key.\n";
		}
	}
	else
	{
		Item* ex = (Item*)FindInList(obj, location->entitiesContained, ITEM);
		if (ex != nullptr)
		{
			cout << "Kicking the " << obj << " won't do anything.\n";
		}
		else
		{
			Npc* ex = (Npc*)FindInList(obj, location->entitiesContained, NPC);
			if (ex != nullptr)
			{
				cout << "You kicked the " << obj <<" (rude, by the way).\nYour foot went through him like if he was a mirage.\n";
			}
			else
			{
				NothingTo("kick");
			}
		}
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

	//We don't use FindInList() here because the target Entity is not a specific class but all except Exit
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
	Item* item = (Item*)FindInList(obj, location->entitiesContained, ITEM); 
	if (item != nullptr) 
	{
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
	}
	else 
	{
		NothingTo("move");
	}
}

//-----------------------------------------------
void Player::Open(const string door, bool gotKey)
{
	Exit* ex = (Exit*)FindInList(door, location->entitiesContained, EXIT);
	if (ex != nullptr) 
	{
		if (!ex->isOpen)
		{
			if (!ex->isLocked || (ex->isLocked && gotKey))
			{
				ex->isOpen = true;
				ex->isLocked = false;
				cout << "You opened the " << ex->description;
				if (gotKey) 
				{
					cout << " using the key!\n";
					cout << "After using it, it disappeared into thin air";
				}
				cout << "!\n";
			}
			else
			{
				cout << "You can't open the " << ex->description << ", it's locked!\n";
			}
		}
		else 
		{
			cout << "The " << door << " is already open!\n";
		}
	}
	else 
	{
		NothingTo("open");
	}
}

//--------------------------------------------------------
void Player::OpenWith(const string door, const string key)
{
	if (key == "foot") 
	{
		Kick(door);
	}
	else
	{
		Item* item = (Item*)FindInList(key, entitiesContained, ITEM);
		Exit* ex = (Exit*)FindInList(door, location->entitiesContained, EXIT);
		if (item == nullptr) 
		{
			Item* item = (Item*)FindInList(key, location->entitiesContained, ITEM);
		}
		if (item != nullptr && ex != nullptr)
		{
			if (ex->key == item)
			{
				Open(door, true);
				item->~Item();
			}
			else
			{
				cout << "This " << key << " doesn't open the " << door << ".\n";
				Open(door, false);
			}
		}
		else if(ex == nullptr)
		{
			NothingTo("open");
		}
		else 
		{
			cout << "There isn't any item with that name in this room or your inventory.\n";
			Open(door, false);
		}
	}
}

//-----------------------------------
void Player::PickUp(const string obj) 
{
	Item* item = (Item*)FindInList(obj, location->entitiesContained, ITEM);
	if (item != nullptr)
	{
		if (item->pickable == true)
		{
			cout << "You picked up the " << item->name << "!\n";
			item->ChangeLocation(this);
		}
		else
		{
			cout << "How are you going to pick up a " << item->name << "? Can't be done.\n";
		}
	}
	else
	{
		NothingTo("pick up");
	}
}

//-----------------------------------
void Player::Press(const string obj)
{
	Item* item = (Item*)FindInList(obj, location->entitiesContained, ITEM);
	if (item != nullptr) 
	{
		if (item->name != "button") 
		{
			cout << "Pressing the " << obj << " doesn't seem to do anything.\n";
		}
		else
		{
			const char* ending = "The elevator is SHAKING!\nYou hear an ominous voice coming from ";
			const char* outcome;
			if (hasHeart) 
			{
				outcome = "above.\n\n\033[36mYou... you have explored this place and found yourself.\nIt is time to go. I will guide you to your resting place,\nwhere all corporeal worries will disapear. Do not be afraid.\033[0m\n\nThe voice stopped. The elevator is accelerating upwards!\n\nIn a blink of an eye you find yourself somewhere new, it looks like paradise.\nYou could stay here for eternity.\n\n";
			}
			else 
			{
				outcome = "under you.\n\n\033[31mLook what we have here! A sinner!\nIt's too late now to make ammends and find closure.\nYou are coming with me to the bottom of HELL!\nPrepare for an eternity of pain MWAHAHAHA...\033[0m\n\nBefore you could process that information the bottom of the elevator breaks,\nleaving exposed a bottomless hole.\nShadowy hands appear from the pit, grab your legs and pull you to the bottom.\n\nOnly despair awaits you.\n\n";
			}
			for (int i = 0; ending[i] != '\0'; ++i) {
				cout << ending[i];
				Timer(0.05f);
			}
			for (int i = 0; outcome[i] != '\0'; ++i) {
				cout << outcome[i];
				Timer(0.05f);
			}
			Timer(5.0f);
			exit(666);
		}
	}
	else 
	{
		NothingTo("press");
	}
}

//--------------------------------------------------------
void Player::Put(const string obj, const string container)
{
	bool objectPutInPlace = false;

	Item* item = (Item*)FindInList(obj, location->entitiesContained, ITEM);
	if (item == nullptr) 
	{
		item = (Item*)FindInList(obj, entitiesContained, ITEM);
	}
	else 
	{
		if (!item->pickable)
		{
			cout << "The " << obj << " can't be moved!\n";
		}
	}
	if (item != nullptr && (container == "player" || container == "me"))
	{
		objectPutInPlace = true;
		if (item->name == "heart")
		{
			hasHeart = true;
			description2 = "You feel complete. You found what was missing.";
			cout << "The heart fit right in. You feel much better now, more complete.\n";
			item->~Item();
		}
		else if(!item->drinkable)
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
		else 
		{
			Drink(item->name);
		}
		item = nullptr;
	}
	if (item != nullptr)
	{
		Item* cont = (Item*)FindInList(container, location->entitiesContained, ITEM);
		if (cont != nullptr) 
		{
			objectPutInPlace = true;
			if (!cont->pickable && item->movable && item->pickable)
			{
				item->ChangeLocation(cont);
				cout << "The " << item->name << " was put in the " << container << "\n";
			}
			else
			{
				cout << "You can't place objects in or on the " << container << "!\n";
			}
		}
	}
	if (!objectPutInPlace) 
	{
		cout << "No object was moved. Either the object or the container don't exist or aren't in this room.\n";
	}
}

//---------------------------------
void Player::Read(const string obj)
{
	Item* item = (Item*)FindInList(obj, location->entitiesContained, ITEM);
	if (item != nullptr)
	{
		if (item->readableInfo == nullptr)
		{
			cout << "There is nothing to read on the " << item->name << "\n";
		}
		else
		{
			cout << item->readableInfo << "\n";
		}
	}
	else
	{
		NothingTo("read");
	}
}

//-----------------------------------
void Player::TalkTo(const string person) 
{
	Npc* npc = (Npc*)FindInList(person, location->entitiesContained, NPC);
	if (npc != nullptr) 
	{
		cout << "\033[31m" << person << ":\033[0m ";

		if (!npc->introduced)
		{
			cout << npc->presentationDialog << "\n";
			npc->introduced = true;
		}
		else 
		{
			random_device rd;
			mt19937 generator(rd());
			uniform_int_distribution<int> distribution(1, 3);

			int randomNumber = distribution(generator);

			switch (randomNumber)
			{
			case 1:
				cout << npc->dialog1 << "\n";
				break;
			case 2:
				cout << npc->dialog2 << "\n";
				break;
			case 3:
				cout << npc->dialog3 << "\n";
				break;
			}
		}
	}
	else 
	{
		if (person == "me" || person == "player" || person == "myself")
		{
			cout << "Are you that lonely?\n";
		}
		else
		{
			cout << "There is no one here that fits that description. Are you seeing ghosts?\n";
		}
	}
}

//------------------------------------------------------------------------------------------------
bool Player::ThrowingFrom(const string obj, list<Entity*> listOfEntities, bool throwingAtSometing)
{
	bool thrown = false;

	Item* item = (Item*)FindInList(obj, listOfEntities, ITEM);
	if (item != nullptr) 
	{
		cout << "You threw the " << item->name;
		if (!throwingAtSometing)
		{
			cout << " across the room!\n";
		}
		thrown = true;
		if (!item->drinkable && !throwingAtSometing)
		{
			cout << "Nothing happened.\n";
		}
		else if (item->drinkable)
		{
			cout << ".\nThe " << item->name << " broke!\n";
			item->~Item();
		}
	}
	return thrown;
}

//-----------------------------------------------------------
bool Player::Throw(const string obj, bool throwingAtSometing)
{
	bool thrown = false;

	thrown = ThrowingFrom(obj,location->entitiesContained, throwingAtSometing);
	if (!thrown) 
	{
		thrown = ThrowingFrom(obj, entitiesContained, throwingAtSometing);
		if (thrown)
		{
			Drop(obj, true, throwingAtSometing);
		}
		else 
		{
			NothingTo("throw");
		}
	}
	return thrown;
}

//------------------------------------------------------------
void Player::ThrowAt(const string obj, const string objective)
{
	bool objectiveHit = false;

	if (Throw(obj, true)) 
	{
		for (list<Entity*>::const_iterator it = location->entitiesContained.begin(); it != location->entitiesContained.cend(); ++it)
		{
			if ((*it)->name == objective || (objective != "exit" && (*it)->description == objective && (*it)->type == EXIT))
			{
				if (obj != "coffee" && obj != "drink")
				{
					cout << " at the " << objective << "!\n";
				}

				objectiveHit = true;
				if ((*it)->type == NPC)
				{

					cout << "The " << obj << " passed through the " << objective << " like he wasn't there. Is he a ghost?\n";
					break;
				}
				if ((*it)->type == ITEM)
				{
					Item* item = (Item*)(*it);
					if (!item->movable && !item->pickable && item->entitiesContained.size() != 0) 
					{
						cout << "From the " << objective << " something fell and now it's in the room:\n";
						list<Entity*>::const_iterator items = item->entitiesContained.begin();
						while (item->entitiesContained.size() != 0)
						{
							cout << "- A " << (*items)->name << "\n";
							(*items)->ChangeLocation(location);
						}
					}
					else 
					{
						cout << "Nothing happened.\n";
					}
					break;
				}
				if ((*it)->type == EXIT && (obj != "drink" && obj != "coffee"))
				{
					cout << "You hit the " << objective << " and now the " << obj << " is on the floor.\n";
					break;
				}
			}
		}
		if (!objectiveHit) 
		{
			if (obj != "coffee" && obj != "drink") 
			{
				cout << ".\n";
			}
			cout << "There isn't anything in this room with that name so it didn't hit anyting.\n";
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

//------------------
void Player::Vomit() 
{
	if (location->name != "Bathroom") 
	{
		cout << "You can't do that here!\n";
	}
	else if(control < 10)
	{
		cout << "You threw up in the toilet. That drink didn't sit right with you.\nYou feel a little better now.\n";
		control++;
	}
	else 
	{
		cout << "You don't feel sick, there is no reason to throw up!\nAltough the smell of this room... it will make you sick.\n";
	}
}