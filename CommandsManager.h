//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMANDSMANAGER_H
#define EX4SERVER_COMMANDSMANAGER_H


#include <map>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command,
                        vector<string> args);
private:
    map<string, Command *> commandsMap;
};


#endif //EX4SERVER_COMMANDSMANAGER_H
