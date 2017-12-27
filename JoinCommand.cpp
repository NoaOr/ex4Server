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

void* JoinCommand::excecuteRoutine(void *arg) {
    DataStruct *data = (DataStruct*)arg;
    JoinCommand *ptr = data->obj;
    ptr->startRoutine(arg);
}

void* JoinCommand::startRoutine(void* args) {

    DataStruct *data = (DataStruct*)args;
    int clientSocket1 = data->clientSocket1;
    int clientSocket2 = data->clientSocket2;
    Game *game = data->currentGame;
    string gameName = data->gameName;
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
    handleExitStatus(data);
    n = write(clientSocket1, &value1, sizeof(value1));
    if (n == -1) {
        throw "Error writing to socket";
    }
    handleExitStatus(data);
    n = write(clientSocket2, &value2, sizeof(value2));
    if (n == -1) {
        throw "Error writing to socket";
    }
    while (true) {
        if (isFirstTurn) {
            handleExitStatus(data);
            n = write(clientSocket1, &firstMsg, sizeof(firstMsg));
            if (n == -1) {
                throw "Error writing to socket";
            }
            handleExitStatus(data);
            n = write(clientSocket1, &firstTurnBuff, sizeof(firstTurnBuff));
            if (n == -1) {
                throw "Error writing to socket";
            }
            isFirstTurn = false;
        } else {
            handleExitStatus(data);
            n = write(clientSocket1, &buffer, sizeof(buffer));
            if (n == -1) {
                throw "Error writing to socket";
            }
        }
        handleExitStatus(data);
        n = write(clientSocket2, &waitingMsg, sizeof(waitingMsg));
        if (n == -1) {
            throw "Error writing to socket";
        }
        handleExitStatus(data);
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
            close(clientSocket1);
            close(clientSocket2);
            return stopGame;
        }
        handleExitStatus(data);
        n = write(clientSocket2, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error writing to socket";
        }
        handleExitStatus(data);
        n = write(clientSocket1, &waitingMsg, sizeof(waitingMsg));
        if (n == -1) {
            throw "Error writing to socket";
        }
        handleExitStatus(data);
        // read the second client's choice
        n = read(clientSocket2, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error reading from socket";
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            close(clientSocket1);
            close(clientSocket2);
            return stopGame;
        }
        if (isEndMessage(buffer)) {
            break;
        }
        if (isNoMoveMessage(buffer) && !player1hasMove) {
            char endGame[END_SIZE] = "End";
            handleExitStatus(data);
            n = write(clientSocket1, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            handleExitStatus(data);
            n = write(clientSocket2, &endGame, sizeof(endGame));
            if (n == -1) {
                throw "Error writing to socket";
            }
            break;
        }
        if (n == 0) {
            close(clientSocket1);
            close(clientSocket2);
            return stopGame;
        }
        player1hasMove = true;
    }
    // delete the game from the list
    list<Game>::iterator it;
    pthread_mutex_lock(&mtx);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        if (it->getGameName() == gameName) {
            gamesList->erase(it);
            break;
        }
    }
    pthread_mutex_unlock(&mtx);
    close(clientSocket1);
    close(clientSocket2);
}

void JoinCommand::handleExitStatus(DataStruct *data) {
    Game *game = data->currentGame;
    int clientSocket1 = data->clientSocket1;
    int clientSocket2 = data->clientSocket2;
    if (game->getStatus() == Game::exit) {
        close(clientSocket1);
        close(clientSocket2);
        pthread_exit(NULL);
    }
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
    pthread_mutex_unlock(&mtx);
    if (!isGameFound) {
        // לבדוק מה קורה אם המשחק לא קיים
        return;
    }
    game = &(*it);
    game->setStatus(Game::run);
    DataStruct *data = new DataStruct();
    data->clientSocket1 = game->getClientSocket();
    data->clientSocket2 = atoi(args.at(0).c_str());
    data->gameName = game->getGameName();
    data->obj = this;
    data->currentGame = game;
    int rc = pthread_create(game->getPthreadAddress(), NULL, excecuteRoutine,(void*)data);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
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