//
// Created by amit on 12/21/17.
//

#include <cstdlib>
#include <unistd.h>
#include <list>
#include "StartCommand.h"
#include "Game.h"

#define MAX_MSG_LEN 300

StartCommand ::StartCommand(list<Game> *gamesList) : Command() {
    this->gamesList = gamesList;
}

void StartCommand :: execute(vector<string> args) {
    int clientSocket = atoi(args.front().c_str());
    string gameName = args.at(1);
    bool isGameFound = false;
    list<Game>::iterator it;
    pthread_mutex_lock(&mtx);
    for (it = this->gamesList->begin(); it != gamesList->end(); ++it) {
        if (it->getGameName() == gameName) {
            isGameFound = true;
            break;
        }
    }
    pthread_mutex_unlock(&mtx);
    if (isGameFound) {
        /// do something
        char error[MAX_MSG_LEN] = "Invalid name! There is another game with this name.";
        int n = write(clientSocket, &error, sizeof(error));
        if (n == -1) {
            throw "Error in writing to socket";
        }
        close(clientSocket);
        return;
    }

    Game game = Game(gameName, clientSocket);
    pthread_mutex_lock(&mtx);
    this->gamesList->push_back(game);
    pthread_mutex_unlock(&mtx);
    char msg1 [MAX_MSG_LEN] = "Waiting for another player to connect...";

    int n = write(clientSocket, &msg1, sizeof(msg1));
    if (n == -1) {
        throw "Error in writing to socket";
    }
}