//
// Created by noa on 23/12/17.
//

#ifndef EX4SERVER_GAME_H
#define EX4SERVER_GAME_H
#include <iostream>
using namespace std;

class Game {
public:
    /**
     * enum to the status of the game.
     */
    enum Status {waiting, run, exit};
    /**
     * Constructor
     * @param gameName- the game name.
     * @param clientSocket1 - socket of the first client.
     */
    Game(string gameName, int clientSocket1);
    /**
     *
     * @return the game name.
     */
    string getGameName() const;
    /**
     *
     * @return the client socket.
     */
    int getClientSocket() const;
    /**
     *
     * @return the pthread.
     */
    pthread_t* getPthreadAddress();
    /**
     * The function changes the status of the game.
     * @param newStatus - the new status.
     */
    void setStatus(Game::Status newStatus);
    /**
     *
     * @return the current status.
     */
    Game::Status getStatus();
    /**
     *
     * @return the pthread id.
     */
    int getPthread();

private:
    string gameName;
    int clientSocket1;
    pthread_t pthread;
    Game::Status status;
};


#endif //EX4SERVER_GAME_H
