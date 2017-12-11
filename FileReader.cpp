//
// Created by noa on 07/12/17.
//

#include <fstream>
#include <cstring>
#include "FileReader.h"
#define MAX_MSG_LEN 300


FileReader::FileReader(char *fileName) {
    char temp[MAX_MSG_LEN];

    fstream file;
    file.open(fileName);
    file >> temp;
    if (strcmp(temp, "serverIP") == 0) {
        file >> this->IP;
        file >> temp;
    }
    if (strcmp (temp, "port") == 0) {
        file >> this->port;
    }
    file.close();
}

int FileReader::getPort() {
    return this->port;
}

string FileReader::getIP() {
    return this->IP;
}