//
// Created by 33722 on 2026/4/21.
//

#include "logger.h"

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    _log_file.open("log.txt", std::ios::app);
    if (!_log_file.is_open()) throw std::runtime_error("Failed to open log file");

}


Logger::~Logger() {
    if (_log_file.is_open())_log_file.close();
}

void Logger::log(const std::string &msg) {
    std::lock_guard<std::mutex> lock(_log_mutex);
    if (_log_file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));

        _log_file << std::string(buffer) <<": "<<msg << std::endl;
    }
}

