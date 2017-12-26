//
// Created by noa on 26/12/17.
//

#ifndef EX4SERVER_CLIENTHANDLER_H
#define EX4SERVER_CLIENTHANDLER_H


#include <list>
#include "Game.h"
#include "CommandsManager.h"
class CommandManager;

class ClientHandler {
public:
    ClientHandler();
    void run(int clientSocket);
    static void * routine(void *arg);
    void startRoutine (int clientSocket);
    void closeAllThreads();
    ~ClientHandler();
private:
    list<Game> *gamesList;
    CommandsManager *commandsManager;

};

struct Data{
    ClientHandler *clientHandler;
    int clientSocket;
};


#endif //EX4SERVER_CLIENTHANDLER_H
