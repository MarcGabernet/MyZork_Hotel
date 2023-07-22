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

	void Buy(const vector<string>& args);
	void Close();//------------------------
	void Close(const string door);//------------------------
	void Drink(const vector<string>& args);
	void Drop(const string obj);//------------------------
	void Insert(const vector<string>& args);
	void Inventory();//------------------------
	void Kick(const string obj);
	void Look();//------------------------
	void Look(const string obj);//------------------------
	void Move(const vector<string>& args);
	void Open();//------------------------
	void Open(const string door);//------------------------
	void PickUp(const string obj);//------------------------
	void Press(const string obj);
	void Read(const string obj);//------------------------
	void TalkTo(const vector<string>& args);
	void Throw(const string obj);
	void Travel(const char* direction);//------------------------

public:
	bool hasHeart = false;
	string description2;
};

#endif
