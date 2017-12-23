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
//    map <string, pthread_t> getPthreadMap();

    list<Game>* getGamesList();

    void addGame(Game game);
    ~Server();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClients(int clientSocket1, int clientSocket2);
    list<Game> gamesList;
//    CommandsManager* commandsManager;
//    list <pthread_t> pthreadList;
//    map <string, pthread_t> pthreadMap;

};


#endif //EX4SERVER_SERVER_H
