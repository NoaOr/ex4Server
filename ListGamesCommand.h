//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_LISTGAMESCOMMAND_H
#define EX4SERVER_LISTGAMESCOMMAND_H


#include "Command.h"
#include "iostream"
using namespace;

class ListGamesCommand : public Command {
public:
    ListGamesCommand (Server* server);
    virtual void execute(vector<string> args);
    ~ListGamesCommand() {};
};


#endif //EX4SERVER_LISTGAMESCOMMAND_H
