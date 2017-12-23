//
// Created by amit on 12/21/17.
//

#include <cstdlib>
#include <unistd.h>
#include "StartCommand.h"
#define MAX_MSG_LEN 300

StartCommand ::StartCommand(Server *server) : Command(server){}

void StartCommand :: execute(vector<string> args) {
    int clientSocket = atoi(args.front().c_str());
    string gameName = args.at(1);
    Game game = Game(gameName, clientSocket);
    this->server->addGame(game);

    char msg1 [MAX_MSG_LEN] = "Waiting for another player to connect...";

    int n = write(clientSocket, &msg1, sizeof(msg1));
    if (n == -1) {
        throw "Error in writing to socket";
    }
}