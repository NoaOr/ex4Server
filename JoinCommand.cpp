//
// Created by noa on 23/12/17.
//

#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "JoinCommand.h"

JoinCommand ::JoinCommand(Server *server) : Command(server){}


void* JoinCommand::executeRoutine(void *obj) {
    JoinCommand *ptr = (JoinCommand*)obj;
    ptr->startRoutine((void*)&ptr->sockets);
}
void* JoinCommand::startRoutine(void* args) {
    vector<int>* sockets = (vector<int>*) args;
    int clientSocket1 = (*sockets).at(0);
    int clientSocket2 = (*sockets).at(1);
    void * stopGame;
    int value1 = 1, value2= 2;
    bool isFirstTurn = true;
    bool player1hasMove = true;
    int buffer[2];
    char waitingMsg[MAX_MSG_LEN] = "Waiting for the other player to respond";
    char firstMsg[MAX_MSG_LEN] = "First turn";
    int firstTurnBuff[2];
    firstTurnBuff[0] = -1;
    firstTurnBuff[1] = -1;
    char msg2 [MAX_MSG_LEN] = "Connected successfully";

       ssize_t n = write(clientSocket2, &msg2, sizeof(msg2));
        cout << "Client connected" << endl;
        if (clientSocket2 == -1) {
            throw "Error on accept";
        }
    // writing the value to each player

    n = write(clientSocket1, &value1, sizeof(value1));
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
            return stopGame;
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
            return stopGame;
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
            return stopGame;
        }
        player1hasMove = true;
    }

}


void JoinCommand::execute(vector<string> args) {
    //args = clientSocket2, name
    int n;
    bool isGameFound = false;
    Game *game;
    list<Game> *games = this->server->getGamesList();
    string gameName = args.at(1);
    list<Game>::iterator it;
    for (it = games->begin(); it != games->end(); ++it) {
//        if (strcmp(it->getGameName(), gameName) == 0) {
        if (it->getGameName() == gameName) {
            isGameFound = true;
            //game = &(*it);
            break;
        }
    }
    if (!isGameFound) {
        // לבדוק מה קורה אם המשחק לא קיים
        return;
    }
    game = &(*it);
    vector<int> sockets = vector<int>();
    int clientSocket2 = atoi(args.at(0).c_str());
    int clientSocket1 = game->getClientSocket();
    sockets.push_back(clientSocket1);
    sockets.push_back(clientSocket2);
    this->sockets = sockets;

    pthread_create(game->getPthreadAddress(), NULL, excecuteRoutine,(void*)this);
}

bool JoinCommand::isEndMessage(int *buffer) {
    char *str = (char*) buffer;
    if (strcmp(str, "End") == 0) {
        return true;
    }
    return false;

}

bool JoinCommand::isNoMoveMessage(int *buffer) {
    char *str = (char*) buffer;
    if (strcmp(str, "NoMove") == 0) {
        return true;
    }
    return false;
}