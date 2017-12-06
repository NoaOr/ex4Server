//
// Created by noa on 04/12/17.
//

#ifndef EX4SERVER_SERVER_H
#define EX4SERVER_SERVER_H


class Server {
public:
    Server(int port);
    void start();
    void stop();
    bool isEndMessage(int *buffer);
    bool isNoMoveMessage(int *buffer);
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClients(int clientSocket1, int clientSocket2);


};


#endif //EX4SERVER_SERVER_H
