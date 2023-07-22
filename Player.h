#ifndef _Player
#define _Player

#include <string>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Player : public Entity
{
public:
	Player(const char* name, const char* description, string description2, Room* location);
	~Player();

	void NothingTo(const string verb);
	bool WhatTo(const string verb);

	void Buy(const vector<string>& args);
	void Close(const string door);
	void Drink(const vector<string>& args);
	void Drop(const string obj, bool dropped);
	void Insert(const vector<string>& args);
	void Inventory();
	void Kick(const string obj);
	void Look();
	void Look(const string obj);
	void Move(const string obj);
	void Open(const string door);
	void PickUp(const string obj);
	void Press(const string obj);
	void Put(const string obj, const string container);
	void Read(const string obj);
	void TalkTo(const vector<string>& args);
	bool ThrowingFrom(const string obj, list<Entity*> list);
	void Throw(const string obj);
	void Travel(const char* direction);

public:
	bool hasHeart = false;
	string description2;
	int control = 10;
};

#endif
