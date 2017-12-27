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
    /**
     * Constructor.
     * @param gamesList - the current list of the game.
     */
    ListGamesCommand (list<Game> *gamesList);
    /**
     * The function executes the command.
     * @param args - vector of strings.
     */
    virtual void execute(vector<string> args);
    /**
     * Destructor.
     */
    ~ListGamesCommand() {};

private:
    list<Game> *gamesList;
};


#endif //EX4SERVER_LISTGAMESCOMMAND_H
