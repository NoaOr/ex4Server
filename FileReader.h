//
// Created by noa on 07/12/17.
//
#include<iostream>
using namespace std;
#ifndef EX4SERVER_FILEREADER_H
#define EX4SERVER_FILEREADER_H


class FileReader {
public:
    FileReader(char *fileName);
    string getIP();
    int getPort();
private:
    string IP;
    int port;

};


#endif //EX4SERVER_FILEREADER_H
