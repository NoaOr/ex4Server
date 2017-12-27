//
// Created by noa on 04/12/17.
//

#ifndef EX4SERVER_SERVER_H
#define EX4SERVER_SERVER_H
#include <string>
#include <map>
#include <list>
#include "Game.h"
#include "CommandsManager.h"
#include "ClientHandler.h"

class CommandsManager;
using namespace std;

class Server {
public:
    /**
     * Constructor
     * @param port - the port
     */
    Server(int port);
    /**
     * start function
     */
    void start();
    /**
     * stop function
     */
    void stop();
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
    /**
     * The static function for starting the pthread of closing.
     * @param obj - void *
     * @return void*
     */
    static void * startClosing(void *obj);
    /**
     * The function closes the threads and ends the game.
     */
    void closing();
    /**
     * Destructor.
     */
    ~Server();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    ClientHandler clientHandler;
    void handleClients(int clientSocket1, int clientSocket2);

};


#endif //EX4SERVER_SERVER_H
