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
    /**
     * Constructor.
     */
    ClientHandler();
    /**
     * The function opens a thread and runs it.
     * @param clientSocket
     */
//    void run(int clientSocket);
    /**
     * The static function to create the thread.
     * @param arg - void*
     * @return - void*
     */
    static void* routine(void *arg);
    /**
     * The function starts the routine and handles the client.
     * @param clientSocket - the socket.
     */
    void run(int clientSocket);
    /**
     * The function closes all threads.
     */
    void closeAllThreads();
    /**
     * destructor.
     */
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
