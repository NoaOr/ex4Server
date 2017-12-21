//
// Created by amit on 12/21/17.
//

#include "ListGamesCommand.h"

ListGamesCommand ::ListGamesCommand(Server *server) : Command(server){}

virtual void ListGamesCommand :: execute(vector<string> args) {
    list<string> namesList = list<string>();
    map<string,pthread_t> pthreadMap = this->server->getPthreadMap();
    map<string, pthread_t>::iterator it;
    for (it = pthreadMap.begin(); it != pthreadMap.end(); it++) {
        namesList.push_back(it->first);
    }
 //send to client names list
}