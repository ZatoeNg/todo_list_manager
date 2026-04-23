//
// Created by 33722 on 2026/4/21.
//

#include "task.h"

std::string Task::toString() const {

    std::ostringstream oss;
    oss <<"ID: "<<id
    <<",描述: "<<description
    <<",优先级: "<<priority
    <<",截止日期: "<<due_date;

    return oss.str();
}
