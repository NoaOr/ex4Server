#include <iostream>
#include "Server.h"
using namespace std;

int main() {
    Server server(8000);
    try {
        server.start();
    } catch (char *msg) {
        cout << "by";
    }
}