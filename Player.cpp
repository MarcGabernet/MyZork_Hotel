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


