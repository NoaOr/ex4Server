//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_STARTCOMMAND_H
#define EX4SERVER_STARTCOMMAND_H


#include "Command.h"
#include "Game.h"

class StartCommand : public Command {
public:
    /**
     * Constructor
     * @param gamesList - the current list of games.
     */
    StartCommand (list<Game> *gamesList);
    /**
     * The function executes the command.
     * @param args - vector of strings.
     */
    virtual void execute(vector<string> args);
    /**
     * Destructor.
     */
    ~StartCommand();
private:
    list<Game> *gamesList;

};


#endif //EX4SERVER_STARTCOMMAND_H
