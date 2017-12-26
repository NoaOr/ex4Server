//
// Created by amit on 12/21/17.
//

#include "Command.h"

Command::Command() {
    pthread_mutex_init(&mtx, NULL);
}
Command::~Command() {}