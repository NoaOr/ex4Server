//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMANDSMANAGER_H
#define EX4SERVER_COMMANDSMANAGER_H

class Command;
class Server;
#include <map>
#include <list>
#include "Command.h"
#include "Game.h"


class CommandsManager {
public:
    CommandsManager(list<Game> *gamesList);
    ~CommandsManager();
    // the first arg is client socket
    void executeCommand(string command, vector<string> args);

private:
    map<string, Command *> commandsMap;
};


#endif //EX4SERVER_COMMANDSMANAGER_H
