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

    cout << "Hotel!\n";

    world.things[0]->Look();

    cout << "> ";

    while (true)
    {
        if (args.size() == 0)
            getline(cin, line);
        istringstream iss(line);

        while (getline(iss, arg, ' '))
            args.push_back(arg);

        if (args.size() > 0 && (args[0] == "quit" || args[0] == "Quit" || args[0] == "q" || args[0] == "Q"))
            break;
        else if (world.ReadCommand(args) == false)
        {
            cout << "\nSorry I don't understand this command\n";
        }

        if (args.size() > 0)
        {
            args.clear();
            cout << "\n> ";
        }
    }

    return 0;
}
