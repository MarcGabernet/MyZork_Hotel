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

    cout << "Hotel!\n\n";

    world.player->location->Look();

    cout << "\n> ";

    while (true)
    {
        if (args.size() == 0)
            getline(cin, line);
        istringstream iss(line);

        cout << "\n";

        while (getline(iss, arg, ' '))
            args.push_back(arg);

        if (args.size() > 0 && (args[0] == "quit" || args[0] == "Quit" || args[0] == "q" || args[0] == "Q"))
            break;
        else if (world.ExecuteCommand(args) == false)
        {
            cout << "Sorry I don't understand this command\n";
        }

        if (args.size() > 0)
        {
            args.clear();
            cout << "\n> ";
        }
    }

    return 0;
}
