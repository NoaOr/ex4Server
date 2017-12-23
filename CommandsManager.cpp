//
// Created by amit on 12/21/17.
//
//
#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "ListGamesCommand.h"

CommandsManager::CommandsManager(Server *server) {
    commandsMap["start"]  = new StartCommand(server);
    commandsMap["join"] = new JoinCommand(server);
    commandsMap["list_games"] = new ListGamesCommand(server);
}
void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}