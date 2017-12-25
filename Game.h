//
// Created by noa on 23/12/17.
//

#ifndef EX4SERVER_GAME_H
#define EX4SERVER_GAME_H
#include <iostream>
using namespace std;

class Game {
public:
    enum Status {waiting, run, exit};
    Game(string gameName, int clientSocket1);
    string getGameName() const;
    int getClientSocket() const;
    pthread_t* getPthreadAddress();
    void setStatus(Game::Status newStatus);
    Game::Status getStatus();

private:
    string gameName;
    int clientSocket1;
    pthread_t pthread;
    Game::Status status;
};


#endif //EX4SERVER_GAME_H
