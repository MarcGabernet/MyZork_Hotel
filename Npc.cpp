#include <iostream>
#include <string>
#include "Npc.h"

using namespace std;

//-------------------
Npc::~Npc() {};

//--------------------------------------------------------------------------------------------
Npc::Npc(const char* name, const char* description, Room* location) :
	Entity(name, description, (Entity*)location)
{
	type = NPC;
};