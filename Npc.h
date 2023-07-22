#ifndef _Npc
#define _Npc

#include <string>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Npc : public Entity
{
public:
	Npc(const char* name, const char* description, Room* location);
	~Npc();

public:
	string dialog1;
	string dialog2;
};

#endif
