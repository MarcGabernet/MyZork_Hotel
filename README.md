# MyZork_Hotel

HOTEL:
--------

This game was developed as an entry test into the "Advanced programming for AAA video games" UPC's Master's degree.

This is a Zork-like game. The objective of the game is to reach the elevator of the hotel and go to your "resting place".
The game follows a main character that doesn't know who he is and has to find out in what kind of hotel it is.

You control the player using commands. The commands are:

-Buy _____

-Buy _____ with _____

-Close _____

-Drink _____

-Drop _____

-Inventory

-Kick _____

-Look

-Look _____

-Look at _____

-Move _____

-Open _____

-Open _____ with _____

-Pick up _____

-Press _____

-Put _____ in _____

-Read _____

-Talk to _____

-Throw _____

-Throw _____ at _____

-Throw up

-Vomit

-Travel (north/west/east/south or n/w/e/s)

The _____ in the commands are places where to write the name of the entities that are object of the action performed.

The first letter of the first world can be written in capital letters, the other have to be in lowercase.

Looking around the room you're in (Look) can tell you the name of the entities that are in there and give you information about the rooms next to it.

Some objects can be picked up, some can be moved, some can be put inside others.

Some exits can be opened withou keys, some are locked but don't have a key assigned to the (maybe brute force will help) and some need a key to be opened.

Items can be dropped by dropping them or throwing them.
Throwing can also be targeted, sometimes things happen when you throw an object at another.

There is a readable sign in the initial room that gives a hint about the game's objective and ending.

NPC will give you hints about the mechanics of the game of you talk to them.
They have four dialog options, some try talking to them until they saig everything they can say.

You can become drunk, but there are also way of becoming sober.

Moving objects can reveal others the were in or on them.

Try reading item, some have information in them.
Also look at items, it will give you a description of them.

You can also interact with yourself: look at yourself and putting thins in you. The name you can use to reference yourself is "me", "myself" and "player".

There is more than one ending, depending on the characteristics of the player when finsihing the game.

This game was fully programmed by me: Marc Gabernet Rodríguez. The original idea of the setting and design was developed by me and the artist @enuji_robotto (Instagram) and is intened to be developed into a videogame in the future.

There are pictures attached to the gitHub repository that show a layout of the hotel and the outside of the hotel. In the layout there are also shown the objects in their respective rooms (spoilers).

The link to the gitHub repository:
https://github.com/MarcGabernet/MyZork_Hotel

PERSONAL NOTES:
--------
Being the first time I programmed in C++ it took me a little while to get used to, but afted getting the hang of it I started enjoying the process very much! I feel like this is only the beggining and I am eager to learn more and make more complex programs, I feel like the possiblities are limitless.

I'm very happy on how the game turned out, it takes into account many variations of the use of the commands depening on the targets in a very clever way in my opinion.

The game is vague as in what is going on and the actual nature of the Hotel on purpose, so I hope you try to play without looking at the spoilers first!

For more clarifications and a guide on how to finish the game: SPOLIERS
--------
-The game has two endings depening on if the player has put a heart in himself.

-To find the heart move the container located at the west of the hotel

-The game ends when you press the button loacted in the elevator.

-To find the key that opens the gate of the elevator, throw an object at the chandelier, it will fall from there.

-Other features are getting drunk: to do that buy a drink from the barman. To buy the drink use the card (credit card) found under the table in the dining hall (move the table)

-If you drink the drink you will become a 10% more drunk and have a 10% more chance of not executing the next command because of your intoxication.

-To become sober again you can drink the coffee found at the kitchen or throw up/vomit in the bathroom (10% more sober every time).

-Closed exits can be opened with open _____ / kick _____ / open _____ with foot if a key is not needed (with locked door and no key needed only kicking the exit is succesful)
