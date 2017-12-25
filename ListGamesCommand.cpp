//
// Created by amit on 12/21/17.
//

#include "ListGamesCommand.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cstring>

#define MAX_SIZE 300
using namespace std;

ListGamesCommand ::ListGamesCommand(Server *server) : Command(server){}

void ListGamesCommand :: execute(vector<string> args) {
   // list<string> namesList = list<string>();
    string names;
    list<Game> *games = this->server->getGamesList();
    list<Game>::iterator it;
    for (it = games->begin(); it != games->end(); ++it) {
        if (it->getStatus() == Game::waiting) {
            names.append(it->getGameName());
        }
        names.append("\n");
    }
    names = names.substr(0, names.size()-1);
    const char* namesArr = names.c_str();
    int clientSocket = atoi(args.front().c_str());
    // send to client the games list
    int n = write(clientSocket, namesArr, MAX_SIZE);
    if (n == -1) {
        throw "Error writing to socket";
    }

    //read another command
    char buffer [MAX_SIZE];
    n = read(clientSocket, &buffer, sizeof(buffer));
    if (n == -1) {
        throw "Error reading from socket";
    }
    string strBuff(buffer);
    istringstream buf(strBuff);
    istream_iterator<std::string> beg(buf), end;
    std::vector<string> tokens(beg, end);
    string command = tokens.at(0);
    tokens.erase(tokens.begin());
    ostringstream oss;
    oss << clientSocket;
    string str = oss.str();
    tokens.insert(tokens.begin(), str);
    CommandsManager commandsManager(this->server);
    commandsManager.executeCommand(command, tokens);
}