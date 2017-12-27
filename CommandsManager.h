//
// Created by amit on 12/21/17.
//

#ifndef EX4SERVER_COMMANDSMANAGER_H
#define EX4SERVER_COMMANDSMANAGER_H

class Command;
class Server;
#include <map>
#include <list>
#include "Command.h"
#include "Game.h"


class CommandsManager {
public:
    /**
     * Constructor.
     * @param gamesList - the current list of games.
     */
    CommandsManager(list<Game> *gamesList);
    // the first arg is client socket
    /**
     * The function executes the command.
     * @param command - the string of the command.
     * @param args - vector of strings.
     */
    bool executeCommand(string command, vector<string> args);
    /**
     * Destructor.
     */
    ~CommandsManager();

private:
    map<string, Command *> commandsMap;
};


#endif //EX4SERVER_COMMANDSMANAGER_H
