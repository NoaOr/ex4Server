//
// Created by amit on 1/14/18.
//

#include "Task.h"
 Task::~Task() {
     delete(this->arg);
 }