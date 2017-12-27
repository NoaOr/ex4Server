//
// Created by noa on 23/12/17.
//

#include "Game.h"

Game::Game(string gameName, int clientSocket1) {
    this->gameName = gameName;
    this->clientSocket1 = clientSocket1;
    this->clientSocket2 = 0;
    this->pthread = 0;
    this->status = Game::waiting;
}

string Game::getGameName() const {
    return gameName;
}

pthread_t* Game::getPthreadAddress() {
    return &(this->pthread);
}

int Game::getClientSocket1() const {
    return this->clientSocket1;
}
int Game::getClientSocket2() const {
    return this->clientSocket2;
}
Game::Status Game::getStatus() {
    return this->status;
}
void Game::setStatus(Status newStatus) {
    this->status = newStatus;
}
pthread_t Game::getPthread() {
    return this->pthread;
}
void Game::setClientSocket2(int clientSocket2) {
    this->clientSocket2 = clientSocket2;
}