//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMAND_H
#define EX4SERVER_COMMAND_H

class Server;
#include <vector>
#include <string>
#include "Server.h"


using namespace std;
class Command {
public:
    Command(Server *server);
    virtual void execute(vector<string> args) = 0;
    ~Command();

protected:
    Server *server;
};

#endif //EX4SERVER_COMMAND_H
