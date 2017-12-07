#include <iostream>
#include "Server.h"
#include "FileReader.h"

using namespace std;

int main() {
    FileReader fileReader ("info.txt");
    int port = fileReader.getPort();
    Server server(port);
    try {
        server.start();
    } catch (char *msg) {
        cout << "by";
    }
}