//
// Created by noa on 04/12/17.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iterator>
#include <sstream>
#include "Server.h"
using namespace std;

#define MAX_CONNECTED_CLIENTS 2
#define MAX_MSG_LEN 300
#define END_SIZE 4


Server::Server(int port): port(port), serverSocket(0), clientHandler() {}

void Server::start() {

    pthread_t closeThread;
    pthread_create(&closeThread, NULL, startClosing, (void*)this);

    char buffer[MAX_MSG_LEN];
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    //socklen_t clientAddressLen = sizeof((struct sockaddr*) &clientAddress);
    socklen_t clientAddressLen = sizeof(struct sockaddr);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket1 = accept(serverSocket, (struct sockaddr*)
                &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket1 == -1) {
            throw "Error on accept";
        }
        this->clientHandler.run(clientSocket1);
    }
}


bool Server::isEndMessage(int *buffer) {
    char *str = (char*) buffer;
    if (strcmp(str, "End") == 0) {
        return true;
    }
    return false;

}

bool Server::isNoMoveMessage(int *buffer) {
    char *str = (char*) buffer;
    if (strcmp(str, "NoMove") == 0) {
        return true;
    }
    return false;
}

Server::~Server() {
//    delete(this->commandsManager);
}

void* Server::startClosing(void *obj) {
    Server *ptr = (Server*)obj;
    ptr->closing();
}

void Server::closing() {
    string str;
    cin >> str;
    if (str == "exit") {
        this->clientHandler.closeAllThreads();
    }
    exit(EXIT_SUCCESS);

}
