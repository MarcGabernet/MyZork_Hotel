#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Entity.h"
#include "World.h"
#include "Player.h"

using namespace std;

int main()
{
    string line;
    vector<string> args;
    string arg;

    World world;

    cout << RED_TEXT;
    cout << "My Zork: Hotel\n\n";

    cout << YELLOW_TEXT;
    cout << "You find yourself in a floating island. In this island there is only one building, a Hotel.\n";
    cout << "You don't seem to be on Earth, but you're not in space either since you're still breathing.\n";
    cout << "All that surrounds you is an unnatural void. You wouldn't want to get lost in it.\n\n\n";

    cout << DEFAULT_COLOR;
    world.player->location->Look();

    cout << YELLOW_TEXT;
    cout << "\n> ";

    while (true)
    {
        if (args.size() == 0)
            getline(cin, line);
        istringstream iss(line);

        cout << "\n";

        while (getline(iss, arg, ' '))
        {
            args.push_back(arg);
        }
        cout << DEFAULT_COLOR;

        if (args.size() > 0 && (args[0] == "quit" || args[0] == "Quit" || args[0] == "q" || args[0] == "Q")) 
        {
            break;
        }
        else if (world.ExecuteCommand(args) == false)
        {
            cout << "Sorry I don't understand this command\n";
        }
        cout << YELLOW_TEXT;

        if (args.size() > 0)
        {
            args.clear();
            cout << "\n> ";
        }
    }

    return 0;
}
