//
// Created by noa on 23/12/17.
//

#ifndef EX4SERVER_JOINCOMMAND_H
#define EX4SERVER_JOINCOMMAND_H


#include <list>
#include "Command.h"
#include "Game.h"

#define MAX_CONNECTED_CLIENTS 2
#define MAX_MSG_LEN 300
#define END_SIZE 4
class JoinCommand;

struct DataStruct {
    JoinCommand *obj;
    int clientSocket1;
    int clientSocket2;
    string gameName;
    Game *currentGame;
};
class JoinCommand : public Command {
public:
    /**
     * Constructor
     * @param gamesList - the current list of games.
     */
    JoinCommand (list<Game> *gamesList);
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
    /**
     * The static function to execute the command.
     * @param obj - void*
     * @return - void*
     */
    static void * excecuteRoutine(void *obj);
    /**
     * Destructor.
     */
    ~JoinCommand() {};


private:
    list<Game> *gamesList;
};

#endif //EX4SERVER_JOINCOMMAND_H
