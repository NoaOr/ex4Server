//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMAND_H
#define EX4SERVER_COMMAND_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Command {
public:
    /**
     * Constructor.
     */
    Command();
    /**
     * The function executes the command.
     * @param args
     */
    virtual void execute(vector<string> args) = 0;
    /**
     * Destructor.
     */
    ~Command();

protected:
    pthread_mutex_t mtx;
};

#endif //EX4SERVER_COMMAND_H
