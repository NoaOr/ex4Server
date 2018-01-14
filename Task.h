//
// Created by amit on 1/14/18.
//

#ifndef EX4SERVER_TASK_H
#define EX4SERVER_TASK_H


class Task {
public:
    Task(void * (*func)(void *arg), void* arg) :
            func(func), arg(arg) {}
    void execute() {
        func(arg);
    }
    virtual ~Task() {}
private:
    void * (*func)(void *arg);
    void *arg;
};


#endif //EX4SERVER_TASK_H
