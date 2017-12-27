//
// Created by amit on 12/21/17.
//
//
#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "ListGamesCommand.h"
#include <typeinfo>

CommandsManager::CommandsManager(list<Game> *gamesList) {
    commandsMap["start"]  = new StartCommand(gamesList);
    commandsMap["join"] = new JoinCommand(gamesList);
    commandsMap["list_games"] = new ListGamesCommand(gamesList);
}
bool CommandsManager::executeCommand(string command, vector<string> args) {
    if(commandsMap.find(command) == commandsMap.end()) {
        //the command not found
        return false;
    }
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
    return true;
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}