#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Entity.h"
#include "World.h"

using namespace std;

int main()
{
    string line;
    vector<string> args;
    string arg;

    World world;

    cout << "Hotel!\n\n> ";

    //Entity* dude = new Entity("Pep", "Weird looking fella", NULL);

    while (true)
    {
        if (args.size() == 0)
            getline(cin, line);
        istringstream iss(line);

        while (getline(iss, arg, ' '))
            args.push_back(arg);

        if (args.size() > 0 && (args[0] == "quit" || args[0] == "Quit" || args[0] == "q" || args[0] == "Q"))
            break;
        else if (args[0] == "look") 
        {
            for (vector<Entity*>::const_iterator it = world.things.begin(); it != world.things.cend(); ++it)
            {
                (*it)->Look();
            }
        }

        for (const string& a : args)
            cout << a << endl;

        if (args.size() > 0)
        {
            args.clear();
            cout << "\n> ";
        }
    }

    return 0;
}
