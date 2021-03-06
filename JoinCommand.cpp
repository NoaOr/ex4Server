//
// Created by noa on 23/12/17.
//

#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "JoinCommand.h"

JoinCommand ::JoinCommand(list<Game> *gamesList){
    this->gamesList = gamesList;
}

void JoinCommand::execute(vector<string> args) {
    bool isGameFound = false;
    Game *game;
    string gameName = args.at(1);
    list<Game>::iterator it;
    pthread_mutex_lock(&mtx);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        if (it->getGameName() == gameName) {
            isGameFound = true;
            break;
        }
    }
    game = &(*it);
    int clientSocket1 = game->getClientSocket1();
    int clientSocket2 = atoi(args.at(0).c_str());
    game->setClientSocket2(clientSocket2);
    game->setStatus(Game::run);
    pthread_mutex_unlock(&mtx);
    if (!isGameFound) {
        char error[MAX_MSG_LEN] = "Invalid name! There is no game with this name.";
        int n = write(clientSocket2, &error, sizeof(error));
        if (n == -1) {
            throw "Error in writing to socket";
        }
        close(clientSocket2);
        return;
    }
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
            char endGame[END_SIZE] = "End";
            n = write(clientSocket2, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            break;
        }
        if (isNoMoveMessage(buffer)) {
            player1hasMove = false;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            close(clientSocket1);
            close(clientSocket2);
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
        if (isEndMessage(buffer)) {
            char endGame[END_SIZE] = "End";
            n = write(clientSocket2, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            break;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            close(clientSocket1);
            close(clientSocket2);
            return;
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
            close(clientSocket1);
            close(clientSocket2);
            return;
        }
        player1hasMove = true;
    }
    // delete the game from the list
    list<Game>::iterator iterator1;
    pthread_mutex_lock(&mtx);
    for (iterator1 = gamesList->begin(); iterator1 != gamesList->end(); ++iterator1) {
        if (iterator1->getGameName() == gameName) {
            gamesList->erase(iterator1);
            break;
        }
    }
    pthread_mutex_unlock(&mtx);
    close(clientSocket1);
    close(clientSocket2);
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