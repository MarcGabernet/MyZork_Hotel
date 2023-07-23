#include <iostream>
#include <string>
#include <random>

#include "World.h"
#include "Exit.h"
#include "Room.h"
#include "Npc.h"

using namespace std;

//-----------------
World::~World() {};

//------------
World::World() 
{
	//Rooms: Outside

	const char* outsideDescription = "You are outside of the Hotel. You see the building standing tall in front of you, so tall you can't see the top.\nIt's the only thing that breaks the monotony of the void that surrounds you.\n";

	Room* southOfHotel = new Room("South Of the Hotel", outsideDescription);
	Room* eastOfHotel = new Room("East Of the Hotel", outsideDescription);
	Room* westOfHotel = new Room("West Of the Hotel", outsideDescription);
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
	Room* diningRoom = new Room("Dining Room", "The dining room of the Hotel: A place that hides one of the fanciest eating experiences ever under layers and layers of dust.\nEven though the large talbe is set very meticulously, the room feels abandoned.\n");
	Room* hallway = new Room("Hallway", "A Hallway that connects the entrace hall with the dining room and the elevators that go to the rooms.\nIt's a very dark place with a single broken light bulb that ocasonally sheds a snippet of light into the room.\n");
	Room* elevator = new Room("Elevator", "A claustrophobic metallic box that seems too old to be working.\nIt closed shut behind you. There is no way to get out.\nThere is only one button, there is no way to choose what floor you want to go to.\n");

	things.push_back(kitchen);
	things.push_back(bar);
	things.push_back(bathroom);
	things.push_back(entranceHall);
	things.push_back(diningRoom);
	things.push_back(hallway);
	things.push_back(elevator);
	
	//NPC's

	Npc* receptionist = new Npc("receptionist", "A well dressed man with a disturbing smile on his face. He seems to be staring at you.", entranceHall);
	receptionist->presentationDialog = "Welcome to the Grand Hotel Basinski! The hotel where you can check out any time you like!\n...\n...\nBut you can never leave.";
	receptionist->dialog1 = "Excuse the mess this hotel is in!\nIt's actually off-season right now so the cleaning workers don't come as often.";
	receptionist->dialog2 = "Did you see the chandelier he have hanging in this room? Beautiful isn't it?\nToo bad sometimes things get stuck in it.\nAt least they are easy to get back, usually THROWING something at it does the trick.";
	receptionist->dialog3 = "We accept all kinds of people in this hotel, but only the ones with a good HEART get the better rooms.";
	Npc* bartender = new Npc("bartender", "A shady man that looks tired of working. He keeps claning the same part of the counter.", bar);
	bartender->presentationDialog = "Good day sir! Would you like to buy something? If not, get out of here prick!";
	bartender->dialog1 = "By the way, I was just kidding with what I first told you.\nWe actually don't recieve lots of clients so feel free to stick around.";
	bartender->dialog2 = "I'm running low on things to sell, the only decent thing I have is a big bottle.\nI don't even know what kind of DRINK it is.";
	bartender->dialog3 = "Be careful with alcohol, it could make you want to throw up!\nLuckly for you I just cleaned the bathrooms so if you want to do it, do it there.";
	Npc* cook = new Npc("cook", "A greasy-looking man that seems to be busy cooking somthing that smells even worse than him.", kitchen);
	cook->presentationDialog = "Hey you! This is the kitchen! Don't you see that I'm busy?\nI'm cooking in case clients come to the restaurant of the hotel.";
	cook->dialog1 = "Who am I lying to? Nobody comes to my restuarant!\nThe few client of this hotel never seem to be hungry.\nI'm going to have to eat all of this so it doesn't spoil.";
	cook->dialog2 = "I made some coffee if you want some, it usualy helps me stay awake and DO WHAT I WANT TO DO.\nAt least it's healthier that anything that the stupid bartender tries to sell to you.";
	cook->dialog3 = "Recently someone ate here at my restaurant but had to leave urgently.\nI think he left SOMETHING AT THE TABLE where he ate.\nIt probably fell under it so I didn't bother picking it up.";

	things.push_back(receptionist);
	things.push_back(bartender);
	things.push_back(cook);

	//Items

	//Items: Outside
	const char* gameInfo = "Welcome to the Hotel Basinski!\n\nYou don't know why you are here, nobody does when they arrive.\nBelieve it or not this hotel will be where you live from now on.\nSo don't be afraid to enter and go to your room.\nTo do that take the elevator: It will guide you to your \"resting place\".";
	
	Item* sign = new Item("sign", "A sign with text on it.", gameInfo, southOfHotel, false, false, false);
	Item* garbage = new Item("container", "A garbage container. Where the Hotel throws away their waste.", nullptr, westOfHotel, false, false, true);
	Item* heart = new Item("heart", "A human heart... How is it still pumping?", nullptr, garbage, false, true, true);
	Item* rock = new Item("rock", "Just a rock. Pretty useless, THROW it away.", nullptr, northOfHotel, false, true, true);

	things.push_back(sign);
	things.push_back(garbage);
	things.push_back(heart);
	things.push_back(rock);

	//Items: Inside
	
	const char* drinkText = "ABSINTHE\n\033[32mCalavera Verde\n\033[0mAlcohol: 89.9%\nWARNING: May cause the loss of control over one self";
	const char* coffeeText = "\033[34mDon't\n\033[36mtalk to\n\033[32mme before\n\033[33mmy moring\n\033[31mCOFFEE\033[0m";
	const char* creditCardText = "Unity National Bank\n-------------------\nLogan Roy\n4716 8755 1191 9591\nEXP DATE: 11/2030";

	Item* chandelier = new Item("chandelier", "A big chandelier hanging from the ceiling. It's made of lots of glass parts and very fancy.", nullptr, entranceHall, false, false, false);
	Item* key = new Item("key", "A key that looks like it open a door.", "Elevator", chandelier, false, true, false);
	Item* drink = new Item("drink", "A bottle of some kind of destilled alcohol, it has a sticker in the back with some text.\nIt smells like sanitary alcohol and looks like an evil potion.", drinkText, bartender, true, true, true);
	drink->drinkingEffect = -1;
	Item* coffee = new Item("coffee", "A cup of hot coffee. Steam is coming out of the cup.\nThere is text written in the cup.", coffeeText, kitchen, true, true, true);
	coffee->drinkingEffect = 1;
	Item* table = new Item("table", "A very well set table. The tablecloth reaches the floor.", nullptr, diningRoom, false, false, true);
	Item* creditCard = new Item("card", "A credit card. It's black with platinum highlights.\nIt has the name of someone you don't know.", creditCardText, table, false, true, true);
	Item* button = new Item("button", "An ominous button. You can't get out of the elevator so you might as well press it.", "JUDGEMENT", elevator, false, false, false);

	things.push_back(chandelier);
	things.push_back(key);
	things.push_back(drink);
	things.push_back(coffee);
	things.push_back(table);
	things.push_back(creditCard);
	things.push_back(button);

	//Exits
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

	Exit* exitHallwayElevator = new Exit(hallway, elevator, s, n, false, true, key);
	exitHallwayElevator->description = "gate";
	elevator->entitiesContained.remove(exitHallwayElevator);


	things.push_back(exitHallBar);
	things.push_back(exitBarBathroom);
	things.push_back(exitBarKitchen);
	things.push_back(exitKitchenDining);
	things.push_back(exitDiningHallway);
	things.push_back(exitHallwayHall);
	things.push_back(exitHallwayElevator);

	player = new Player("me", "You... who are you? ... who WERE you?", "You feel an emptiness in your chest. Something is off.", elevator);

	things.push_back(player);
}

bool World::Execute(const vector<string>& args) {

	bool executed = true;

	//Ranom number from 1 to 10
	random_device rd;
	mt19937 generator(rd()); // Mersenne Twister 19937 engine
	uniform_int_distribution<int> distribution(1, 10);

	int randomNumber = distribution(generator); 

	if (randomNumber > player->control) 
	{
		if (player->control >= 7) 
		{
			cout << "You are little drunk.\n";
		}
		else if (player->control >= 4)
		{
			cout << "You are very drunk, you feel like vomiting.\n";
		}
		else if (player->control >= 1)
		{
			cout << "You are extremly drunk, everything is spinning around you.\n";
		}
		cout << "You slipped and fell to the ground so you didn't do what you wanted to!\n";
	}
	else 
	{
		executed = ExecuteCommand(args);
	}
	return executed;
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
			else if (args[0] == "inventory" || args[0] == "Inventory")
			{
				player->Inventory();
			}
			else if (args[0] == "vomit" || args[0] == "Vomit")
			{
				player->Vomit();
			}
			else if (player->WhatTo(args[0]) == false)
			{
				executed = false;
			}
			break;

		case 2:
			if (args[0] == "buy" || args[0] == "Buy")
			{
				player->Buy(args[1], " ", false);
			}
			else if (args[0] == "close" || args[0] == "Close")
			{
				player->Close(args[1]);
			}
			else if (args[0] == "open" || args[0] == "Open")
			{
				player->Open(args[1], false);
			}
			else if (args[0] == "kick" || args[0] == "Kick")
			{
				player->Kick(args[1]);
			}
			else if (args[0] == "drink" || args[0] == "Drink")
			{
				player->Drink(args[1]);
			}
			else if (args[0] == "drop" || args[0] == "Drop")
			{
				player->Drop(args[1],false, true);
			}
			else if ((args[0] == "throw" || args[0] == "Throw") && args[1] != "up")
			{
				player->Throw(args[1], false);
			}
			else if (args[0] == "look" || args[0] == "Look")
			{
				player->Look(args[1]);
			}
			else if (args[0] == "press" || args[0] == "Press")
			{
				player->Press(args[1]);
			}
			else if (args[0] == "read" || args[0] == "Read")
			{
				player->Read(args[1]);
			}
			else if (args[0] == "move" || args[0] == "Move")
			{
				player->Move(args[1]);
			}
			else if ((args[0] == "throw" || args[0] == "Throw") && args[1] == "up")
			{
				player->Vomit();
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
			else if ((args[0] == "talk" || args[0] == "Talk") && args[1] == "to")
			{
				player->TalkTo(args[2]);
			}
			else if ((args[0] == "look" || args[0] == "Look") && args[1] == "at")
			{
				if (args[2] == "myself") 
				{
					player->Look();
				}
				else 
				{
					player->Look(args[2]);
				}
			}
			else
			{
				executed = false;
			}
			break;
		case 4:
			if ((args[0] == "buy" || args[0] == "Buy") && args[2] == "with")
			{
				player->BuyWith(args[1], args[3]);
			}
			else if ((args[0] == "open" || args[0] == "Open") && args[2] == "with")
			{
				player->OpenWith(args[1], args[3]);
			}
			else if ((args[0] == "put" || args[0] == "Put") && args[2] == "in") 
			{
				player->Put(args[1], args[3]);
			}
			else if ((args[0] == "throw" || args[0] == "Throw") && args[2] == "at")
			{
				player->ThrowAt(args[1], args[3]);
			}
			else
			{
				executed = false;
			}
			break;
		default:
			executed = false;
			break;
	}
	return executed;
}