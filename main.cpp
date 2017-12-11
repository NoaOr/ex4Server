#include <iostream>
#include "Server.h"
#include "FileReader.h"
#define MAX_MSG_LEN 300

using namespace std;

int main() {
    char fileName[MAX_MSG_LEN] = "definitions.txt";
    FileReader fileReader (fileName);
    int port = fileReader.getPort();
    Server server(port);
    try {
        server.start();
    } catch (char *msg) {
        cout << "by";
    }
}