//
// Created by amit on 1/14/18.
//

#ifndef EX4SERVER_TREADPOOL_H
#define EX4SERVER_TREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;
class ThreadPool {
public:
    ThreadPool(int threadsNum);
    void addTask(Task *task);
    void terminate();
    virtual ~ThreadPool();
private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    static void *execute(void *arg);
};


#endif //EX4SERVER_TREADPOOL_H
