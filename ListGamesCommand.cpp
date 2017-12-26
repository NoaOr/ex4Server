//
// Created by amit on 12/21/17.
//

#include "ListGamesCommand.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cstring>

#define MAX_SIZE 300
using namespace std;

ListGamesCommand ::ListGamesCommand(list<Game> *gamesList){
    this->gamesList = gamesList;

}

void ListGamesCommand :: execute(vector<string> args) {
    string names;
    list<Game>::iterator it;
    pthread_mutex_lock(&mtx);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        if (it->getStatus() == Game::waiting) {
            names.append(it->getGameName());
        }
        names.append("\n");
    }
    pthread_mutex_unlock(&mtx);
    names = names.substr(0, names.size()-1);
    const char* namesArr = names.c_str();
    int clientSocket = atoi(args.front().c_str());
    // send to client the games list
    int n = write(clientSocket, namesArr, MAX_SIZE);
    if (n == -1) {
        throw "Error writing to socket";
    }
    close(clientSocket);
}