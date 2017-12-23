//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMANDSMANAGER_H
#define EX4SERVER_COMMANDSMANAGER_H

class Command;
class Server;
#include <map>
#include "Command.h"
#include "Server.h"
//#include "StartCommand.h"
//#include "JoinCommand.h"
//#include "ListGamesCommand.h"


class CommandsManager {
public:
    CommandsManager(Server *server);
    ~CommandsManager();
    // the first arg is client socket
    void executeCommand(string command, vector<string> args);
private:
    map<string, Command *> commandsMap;
};


#endif //EX4SERVER_COMMANDSMANAGER_H
