#ifndef _Room
#define _Room

#include <string>
#include <list>

#include "Entity.h"
#include "Exit.h"

using namespace std;

class Room : public Entity 
{
public:
	Room(const char* name, const char* description);
	~Room();
	
	void Look();

	//Exit* GetExit();
};

#endif
