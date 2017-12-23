//
// Created by noa on 23/12/17.
//

#include "Game.h"

Game::Game(string gameName, int clientSocket1) {
    this->gameName = gameName;
    this->clientSocket1 = clientSocket1;
    this->pthread = 0;
}

string Game::getGameName() const {
    return gameName;
}

pthread_t* Game::getPthreadAddress() {
    return &(this->pthread);
}

int Game::getClientSocket() const {
    return this->clientSocket1;
}