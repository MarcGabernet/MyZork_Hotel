#ifndef _Player
#define _Player

#include <string>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Item.h"
#include "Npc.h"

using namespace std;

class Player : public Entity
{
public:
	Player(const char* name, const char* description, string description2, Room* location);
	~Player();

	void NothingTo(const string verb);
	bool WhatTo(const string verb);
	Entity* FindInList(const string name, list<Entity*> entities, entityType objectType);

	void Buy(const string drink, const string paymentMethod, bool paying);
	void BuyWith(const string drink, const string obj);
	void Close(const string door);
	void Drink(const string drink);
	void Drop(const string obj, bool dropped, bool throwingAtSometing);
	void Inventory();
	void Kick(const string obj);
	void Look();
	void Look(const string obj);
	void Move(const string obj);
	void Open(const string door, bool gotKey);
	void OpenWith(const string door, const string key);
	void PickUp(const string obj);
	void Press(const string obj);
	void Put(const string obj, const string container);
	void Read(const string obj);
	void TalkTo(const string obj);
	bool ThrowingFrom(const string obj, list<Entity*> list, bool throwingAtSometing);
	bool Throw(const string obj, bool throwingAtSometing);
	void ThrowAt(const string obj, const string objective);
	void Travel(const char* direction);
	void Vomit();

public:
	bool hasHeart = false;
	string description2;
	int control = 10;
};

#endif
