#include <iostream>
#include <string>

#include "World.h"
#include "Exit.h"
#include "Room.h"

using namespace std;

//-----------------
World::~World() {};

//------------
World::World() 
{
	//Rooms: Outside

	const char* outsideDescription = "You are outside of the Hotel. You see the building standing tall in front of you, so tall you can't see the top.\nIt's the only thing that breaks the monotony of the void that surrounds you.\n";

	Room* southOfHotel = new Room("South Of the Hotel", outsideDescription);
		//Items in southOfHotel
		//Sign
		const char* gameInfo = "Welcome to the Hotel!\nYou don't know why you are here, nobody does when they arrive. Believe it or not this hotel will be where you live from now on.\nSo don't be afraid to enter and go to your room. To do that take the elevator: IT will guide you to your \"resting place\"";
		Item* sign = new Item("sign", "A sign with text on it", gameInfo, southOfHotel, false, false, false);
		things.push_back(sign); 
	
	Room* eastOfHotel = new Room("East Of the Hotel", outsideDescription);

	Room* westOfHotel = new Room("West Of the Hotel", outsideDescription);
		//Items in westOfHotel
		//Garbage container
		Item* garbage = new Item("garbage", "A garbage container. Where the Hotel throws away their waste", nullptr, westOfHotel, false, false, true);
		things.push_back(garbage);
		//Heart
		Item* heart = new Item("heart", "A human heart... How is it still pumping?", nullptr, garbage, false, true, true);
		things.push_back(heart);

	Room* northOfHotel = new Room("North Of the Hotel", outsideDescription);

	things.push_back(southOfHotel);
	things.push_back(eastOfHotel);
	things.push_back(westOfHotel);
	things.push_back(northOfHotel);

	//Rooms:Inside

	Room* kitchen = new Room("Kitchen", "The Hotel's kitchen: It looks like it has never been cleaned.\nThe walls of this room have been impregnated with the smells of a thousand types of food.\n");
	Room* bar = new Room("Bar", "A dimly lit room with a depressing song playing on the backround.\n");
	Room* bathroom = new Room("Bathroom", "The worst smelling place you have ever experienced. Get out!\nIt feels like the toilets are only for decoration, since the whole floor is sticky not exactly dry.\n");
	Room* entranceHall = new Room("Entrance Hall", "The maginficent entrace of the Hotel: Its tall ceiling combined with the ornaments on the wall give it a sense of importance.\nIt's now an old room filled with spiderwebs but feels like it was once a place where important people met.\n");
	
		Item* chandelier = new Item("chandelier", "A key that looks like it open a door", nullptr, entranceHall, false, false, false);
		things.push_back(chandelier);
		Item* key = new Item("key", "A key that looks like it open a door", nullptr, chandelier, false, true, false);
		things.push_back(key);

	Room* diningRoom = new Room("Dining Room", "The dining room of the Hotel: A place that hides one of the fanciest eating experiences ever under layers and layers of dust.\nEven though all the talbes are set very meticulously it feels abandoned.\n");
	Room* hallway = new Room("Hallway", "A Hallway that connects the entrace hall with the dining room and the elevators that go to the rooms.\nIt's a very dark place with a single broken light bulb that ocasonally sheds a snippet of light.\n");
	Room* elevator = new Room("Elevator", "A claustrophobic metallic box that seems too old to be working.\n\nIt closed shut behind you. There is no way to get out.");

	things.push_back(kitchen);
	things.push_back(bar);
	things.push_back(bathroom);
	things.push_back(entranceHall);
	things.push_back(diningRoom);
	things.push_back(hallway);
	things.push_back(elevator);
	
	const char* n = "north";
	const char* s = "south";
	const char* w = "west";
	const char* e = "east";

	//Exits: Outside
	Exit* exitSW = new Exit(southOfHotel, westOfHotel, w, s, true, false, NULL);
	Exit* exitNW = new Exit(westOfHotel, northOfHotel, n, w, true, false, NULL);
	Exit* exitNE = new Exit(northOfHotel, eastOfHotel, e, n, true, false, NULL);
	Exit* exitSE = new Exit(eastOfHotel, southOfHotel, s, e, true, false, NULL);

	things.push_back(exitSW);
	things.push_back(exitNW);
	things.push_back(exitNE);
	things.push_back(exitSE);
	
	//Exits: Outside to Inside
	Exit* exitMainDoor = new Exit(southOfHotel, entranceHall, n, s, false, true, NULL);
	exitMainDoor->description = "door";

	Exit* exitWindow = new Exit(eastOfHotel, diningRoom, w, e, false, false, NULL);
	exitWindow->description = "window";

	Exit* exitBackDoor = new Exit(northOfHotel, kitchen, s, n, false, false, NULL);
	exitBackDoor->description = "door";

	things.push_back(exitMainDoor);
	things.push_back(exitWindow);
	things.push_back(exitBackDoor);

	//Exits: Inside
	Exit* exitHallBar = new Exit(entranceHall, bar, w, e, true, false, NULL);
	Exit* exitBarBathroom = new Exit(bar, bathroom, s, n, true, false, NULL);
	Exit* exitBarKitchen = new Exit(bar, kitchen, n, s, true, false, NULL);
	Exit* exitKitchenDining = new Exit(kitchen, diningRoom, e, w, true, false, NULL);
	Exit* exitDiningHallway = new Exit(diningRoom, hallway, s, n, true, false, NULL);
	Exit* exitHallwayHall = new Exit(hallway, entranceHall, w, e, true, false, NULL);

	Exit* exitHallwayElevator = new Exit(hallway, elevator, s, n, false, true, NULL);
	exitHallwayElevator->description = "elevator";


	things.push_back(exitHallBar);
	things.push_back(exitBarBathroom);
	things.push_back(exitBarKitchen);
	things.push_back(exitKitchenDining);
	things.push_back(exitDiningHallway);
	things.push_back(exitHallwayHall);
	things.push_back(exitHallwayElevator);

	player = new Player("...", "you... who are you? ... who WERE you?", "You feel an emptiness in your chest. Something is off.", southOfHotel);
		southOfHotel->entitiesContained.push_back(player);

	things.push_back(player);
}

bool World::ExecuteCommand(const vector<string>& args) 
{
	bool executed = true;
	switch (args.size()) 
	{
		case 1:
			if (args[0] == "w" || args[0] == "W" || args[0] == "west" || args[0] == "West")
			{
				player->Travel("west");
			}
			else if (args[0] == "s" || args[0] == "S" || args[0] == "south" || args[0] == "South")
			{
				player->Travel("south");
			}
			else if (args[0] == "e" || args[0] == "E" || args[0] == "east" || args[0] == "East")
			{
				player->Travel("east");
			}
			else if (args[0] == "n" || args[0] == "N" || args[0] == "north" || args[0] == "North")
			{
				player->Travel("north");
			}
			else if (args[0] == "look")
			{
				player->location->Look();
			}
			else if (args[0] == "close" || args[0] == "Close")
			{
				player->Close();
			}
			else if (args[0] == "open" || args[0] == "Open")
			{
				player->Open();
			}
			else if (args[0] == "inventory" || args[0] == "Inventory")
			{
				player->Inventory();
			}
			else 
			{
				executed = false;
			}
			break;

		case 2:
			if (args[0] == "close" || args[0] == "Close")
			{
				player->Close(args[1]);
			}
			else if (args[0] == "open" || args[0] == "Open")
			{
				player->Open(args[1]);
			}
			else if (args[0] == "kick" || args[0] == "Kick")
			{
				player->Kick(args[1]);
			}
			else
			{
				executed = false;
			}
			break;
		case 3: 
			if ((args[0] == "pick" || args[0] == "Pick") && args[1] == "up")
			{
				player->PickUp(args[2]);
			}
			else if ((args[0] == "look" || args[0] == "Look") && args[1] == "at" && args[2] == "myself")
			{
				player->Look();
			}
			break;
		default:
			executed = false;
			break;
	}

	
	return executed;
}