//
// Created by amit on 12/21/17.
//

#include "ListGamesCommand.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

ListGamesCommand ::ListGamesCommand(Server *server) : Command(server){}

void ListGamesCommand :: execute(vector<string> args) {
    list<string> namesList = list<string>();
    list<Game> *games = this->server->getGamesList();
    list<Game>::iterator it;
    for (it = games->begin(); it != games->end(); ++it) {
        namesList.push_back(it->getGameName());
    }
    int clientSocket = atoi(args.front().c_str());
    // send to client the games list
    int n = write(clientSocket, &namesList, sizeof(namesList));
    if (n == -1) {
        throw "Error writing to socket";
    }
}