//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_STARTCOMMAND_H
#define EX4SERVER_STARTCOMMAND_H


#include "Command.h"
#include "Game.h"

class StartCommand : public Command {
public:
    StartCommand (list<Game> *gamesList);
    virtual void execute(vector<string> args);
    ~StartCommand();
private:
    list<Game> *gamesList;

};


#endif //EX4SERVER_STARTCOMMAND_H
