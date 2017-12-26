//
// Created by noa on 26/12/17.
//

#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <iterator>
#include "ClientHandler.h"
#define MAX_MSG_LEN 300
ClientHandler::ClientHandler() {
    this->gamesList = new list<Game>();
    this->commandsManager = new CommandsManager(this->gamesList);
}


void ClientHandler::run(int clientSocket) {
    pthread_t pthread;
    Data *data = new Data();
    data->clientHandler = this;
    data->clientSocket = clientSocket;
    int rc = pthread_create(&pthread, NULL, routine, (void*)data);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
   // pthread_exit(NULL);
}

void* ClientHandler::routine(void *arg) {
    Data *data = (Data*)arg;
    ClientHandler *ptr = data->clientHandler;
    ptr->startRoutine(data->clientSocket);
}

void ClientHandler::startRoutine(int clientSocket) {
    char buffer[MAX_MSG_LEN];
    int n = read(clientSocket, &buffer, sizeof(buffer));
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
    this->commandsManager->executeCommand(command, tokens);
}
void ClientHandler::closeAllThreads() {
    void * state;
    list<Game> ::iterator it;
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        it->setStatus(Game::exit);
        pthread_join(it->getPthread(), &state);
    }
}
ClientHandler::~ClientHandler() {
  //  delete(commandsManager);
//    list<Game> ::const_iterator it;
//    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
//        delete it;
//    }
    //delete(gamesList);
}