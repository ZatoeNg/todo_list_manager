//
// Created by 33722 on 2026/4/21.
//

#ifndef YODO_LIST_MANAGER_LOGGER_H
#define YODO_LIST_MANAGER_LOGGER_H
#include "pch.h"

class Logger {
public:
    // 获取单例
    static Logger& get_instance();

    // 禁止拷贝和赋值
    Logger(const Logger &) = delete;

    Logger &operator=(Logger const &) = delete;

    // 记录日志
    void log(const std::string &msg);

    ~Logger();

private:
    Logger();

private:
    std::ofstream _log_file;
    std::mutex _log_mutex;
};


#endif //YODO_LIST_MANAGER_LOGGER_H
