//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_STARTCOMMAND_H
#define EX4SERVER_STARTCOMMAND_H


#include "Command.h"

class StartCommand : public Command{
public:
    StartCommand (Server* server);
    virtual void execute(vector<string> args);
    ~StartCommand() {};

};


#endif //EX4SERVER_STARTCOMMAND_H
