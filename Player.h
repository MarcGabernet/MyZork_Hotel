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
	Player(const char* name, const char* description, Room* location);
	~Player();

	void Buy(const vector<string>& args);
	void Close();
	void Close(const string door);
	void Drink(const vector<string>& args);
	void Drop(const vector<string>& args);
	void Insert(const vector<string>& args);
	void Inventory();
	void Kick(const string obj);
	void Look(const vector<string>& args);
	void Move(const vector<string>& args);
	void Open();
	void Open(const string door);
	void PickUp(const string obj);
	void Press(const vector<string>& args);
	void Read(const vector<string>& args);
	void Talk(const vector<string>& args);
	void Throw(const vector<string>& args);
	void Travel(const char* direction);

public:
	bool hasHeart = false;
};

#endif
