//
// Created by noa on 04/12/17.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 2
#define MAX_MSG_LEN 300
#define END_SIZE 4

Server::Server(int port): port(port), serverSocket(0) {
    this->pthreadList = list <pthread_t>();
    this->pthreadMap = map <string, pthread_t>();
}
void Server::start() {
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

        char msg1 [MAX_MSG_LEN] = "Waiting for another player to connect...";

        int n = write(clientSocket1, &msg1, sizeof(msg1));
        if (n == -1) {
            throw "Error in writing to socket";
        }
        int clientSocket2 = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);


        char msg2 [MAX_MSG_LEN] = "Connected successfully";

        n = write(clientSocket2, &msg2, sizeof(msg2));
        cout << "Client connected" << endl;
        if (clientSocket2 == -1) {
            throw "Error on accept";
        }

        handleClients(clientSocket1, clientSocket2);
        // Close communication with the client
        close(clientSocket1);
        close(clientSocket2);
    }
}


void Server ::handleClients(int clientSocket1, int clientSocket2) {
    int value1 = 1, value2= 2;
    bool isFirstTurn = true;
    bool player1hasMove = true;
    int buffer[2];
    char waitingMsg[MAX_MSG_LEN] = "Waiting for the other player to respond";
    char firstMsg[MAX_MSG_LEN] = "First turn";
    int firstTurnBuff[2];
    firstTurnBuff[0] = -1;
    firstTurnBuff[1] = -1;
    // writing the value to each player
    ssize_t n = write(clientSocket1, &value1, sizeof(value1));
    if (n == -1) {
        throw "Error writing to socket";
    }
    n = write(clientSocket2, &value2, sizeof(value2));
    if (n == -1) {
        throw "Error writing to socket";
    }
    while (true) {
        if (isFirstTurn) {
            n = write(clientSocket1, &firstMsg, sizeof(firstMsg));
            if (n == -1) {
                throw "Error writing to socket";
            }
            n = write(clientSocket1, &firstTurnBuff, sizeof(firstTurnBuff));
            if (n == -1) {
                throw "Error writing to socket";
            }
            isFirstTurn = false;
        } else {
            n = write(clientSocket1, &buffer, sizeof(buffer));
            if (n == -1) {
                throw "Error writing to socket";
            }
        }
        n = write(clientSocket2, &waitingMsg, sizeof(waitingMsg));
        if (n == -1) {
            throw "Error writing to socket";
        }
        // read the first client's choice
        n = read(clientSocket1, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error reading from socket";
        }
        if (isEndMessage(buffer)) {
            break;
        }
        if (isNoMoveMessage(buffer)) {
            player1hasMove = false;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            return;
        }

        n = write(clientSocket2, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error writing to socket";
        }
        n = write(clientSocket1, &waitingMsg, sizeof(waitingMsg));
        if (n == -1) {
            throw "Error writing to socket";
        }
        // read the second client's choice
        n = read(clientSocket2, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error reading from socket";
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            return;
        }
        if (isEndMessage(buffer)) {
            break;
        }
        if (isNoMoveMessage(buffer) && !player1hasMove) {
            char endGame[END_SIZE] = "End";
            n = write(clientSocket1, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            n = write(clientSocket2, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            break;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            return;
        }
        player1hasMove = true;
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

map <string, pthread_t> Server::getPthreadMap() {
   return this->pthreadMap;
}