#include <iostream>

#include "World.h"
#include "Exit.h"
#include "Entity.h"
#include "Room.h"

using namespace std;

//-----------------
World::~World() {};

//------------
World::World() 
{
	//Rooms: Outside

	const char* outsideDescription = "Outside of the Hotel: You see the building stand tall in front of you, so tall you can't see the top.\nIt's the only thing that breaks the monotony of the void that surrounds you.\n";

	Room* southOfHotel = new Room("South Of Hotel", outsideDescription);
	Room* eastOfHotel = new Room("East Of Hotel", outsideDescription);
	Room* westOfHotel = new Room("West Of Hotel", outsideDescription);
	Room* northOfHotel = new Room("West Of Hotel", outsideDescription);

	things.push_back(southOfHotel);
	things.push_back(eastOfHotel);
	things.push_back(westOfHotel);
	things.push_back(northOfHotel);

	//Rooms:Inside

	Room* kitchen = new Room("Kitchen", "The Hotel's kitchen: It looks like it has never been cleaned.\nThe walls of this room have been impregnated with the smells of a thousand types of food.\n");
	Room* bar = new Room("Bar", "A dimly lit room with a depressing song playing on the backround.\n");
	Room* bathroom = new Room("Bathroom", "The worst smelling place you have ever experienced.\nIt feels like the toilets are only for decoration, since the whole floor is sticky not exactly dry.\n");
	Room* entranceHall = new Room("Entrance Hall", "The maginficent entrace of the Hotel: Its tall ceiling combined with the ornaments on the wall give it a sense of importance.\nIt's now an old room filled with spiderwebs but feels like it was once a place where important people met.\n");
	Room* diningRoom = new Room("Dining Room", "The dining room of the Hotel: A place that hides one of the fanciest eating experiences ever under layers and layers of dust.\nEven though all the talbes are set very meticulously it feels abandoned.\n");
	Room* hallway = new Room("Hallway", "A Hallway that connects the entrace hall with the dining room and the elevators that go to the rooms.\nIt's a very dark place with a single broken light bulb that ocasonally sheds a snippet of light.\n");
	Room* elevator = new Room("Elevator", "A claustrophobic metallic box that seems too old to be working.\n");

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
	
	Exit* exitSW = new Exit(southOfHotel, westOfHotel, w, s, true, false);
	Exit* exitNW = new Exit(westOfHotel, northOfHotel, n, w, true, false);
	Exit* exitNE = new Exit(northOfHotel, eastOfHotel, e, n, true, false);
	Exit* exitSE = new Exit(eastOfHotel, southOfHotel, s, e, true, false);

	things.push_back(exitSW);
	things.push_back(exitNW);
	things.push_back(exitNE);
	things.push_back(exitSE);
	
	//Exits: Outside to Inside

	Exit* exitMainDoor = new Exit(southOfHotel, entranceHall, n, s, false, true);
	Exit* exitWindow = new Exit(eastOfHotel, diningRoom, w, e, false, false);
	Exit* exitBackDoor = new Exit(northOfHotel, kitchen, s, n, false, false);

	things.push_back(exitMainDoor);
	things.push_back(exitWindow);
	things.push_back(exitBackDoor);

	//Exits: Inside
	Exit* exitHallBar = new Exit(entranceHall, bar, w, e, true, false);
	Exit* exitBarBathroom = new Exit(bar, bathroom, s, n, true, false);
	Exit* exitBarKitchen = new Exit(bar, kitchen, n, s, true, false);
	Exit* exitKitchenDining = new Exit(kitchen, diningRoom, e, w, true, false);
	Exit* exitDiningHallway = new Exit(diningRoom, hallway, s, n, true, false);
	Exit* exitHallwayHall = new Exit(hallway, entranceHall, w, e, true, false);

	Exit* exitHallwayElevator = new Exit(hallway, elevator, s, n, false, true);

	things.push_back(exitHallBar);
	things.push_back(exitBarBathroom);
	things.push_back(exitBarKitchen);
	things.push_back(exitKitchenDining);
	things.push_back(exitDiningHallway);
	things.push_back(exitHallwayHall);

	things.push_back(exitHallwayElevator);

}