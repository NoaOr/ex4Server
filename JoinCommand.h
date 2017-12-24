//
// Created by noa on 23/12/17.
//

#ifndef EX4SERVER_JOINCOMMAND_H
#define EX4SERVER_JOINCOMMAND_H


#include "Command.h"
#define MAX_CONNECTED_CLIENTS 2
#define MAX_MSG_LEN 300
#define END_SIZE 4


class JoinCommand : public Command {
public:
    JoinCommand (Server *server);
    void execute(vector<string> args);
    void* startRoutine(void* sockets);
    /**
     * This function checks if the received message is an end message
     * @param buffer - the buffer
     * @return - boolean
     */
    bool isEndMessage(int *buffer);
    /**
     * This function checks if the received message is a no move message
     * @param buffer - the buffer
     * @return - boolean
     */
    bool isNoMoveMessage(int *buffer);
    ~JoinCommand() {};
    static void * executeRoutine(void *obj);

private:
    vector<int>sockets;
};


#endif //EX4SERVER_JOINCOMMAND_H
