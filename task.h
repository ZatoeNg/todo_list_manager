//
// Created by 33722 on 2026/4/21.
//

#ifndef TODO_LIST_MANAGER_TASK_H
#define TODO_LIST_MANAGER_TASK_H
#include "pch.h"


class Task {

public:
    std::string toString()const;

public:
    int id;
    std::string description;
    int priority;
    std::string due_date;
};



#endif //TODO_LIST_MANAGER_TASK_H
