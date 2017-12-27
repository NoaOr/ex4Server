//
// Created by noa on 07/12/17.
//
#include<iostream>
using namespace std;
#ifndef EX4SERVER_FILEREADER_H
#define EX4SERVER_FILEREADER_H


class FileReader {
public:
    /**
     * Constructor
     * @param fileName
     */
    FileReader(char *fileName);
    /**
     *
     * @return the server IP
     */
    string getIP();
    /**
     *
     * @return the port.
     */
    int getPort();
private:
    string IP;
    int port;

};


#endif //EX4SERVER_FILEREADER_H
