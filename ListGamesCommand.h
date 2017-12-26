//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_LISTGAMESCOMMAND_H
#define EX4SERVER_LISTGAMESCOMMAND_H


#include "Command.h"
#include "Game.h"
#include <iostream>
#include <list>

using namespace std;
class Command;

class ListGamesCommand : public Command {
public:
    ListGamesCommand (list<Game> *gamesList);
    virtual void execute(vector<string> args);
    ~ListGamesCommand() {};

private:
    list<Game> *gamesList;
};


#endif //EX4SERVER_LISTGAMESCOMMAND_H
