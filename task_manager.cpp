//
// Created by 33722 on 2026/4/21.
//

#include "pch.h"
#include "task_manager.h"
#include "logger.h"

TaskManager::TaskManager() : next_task_id(1) {
    load_tasks();
}

void TaskManager::add_task(const std::string &description, int priority, const std::string &due_date) {
    Task task;
    task.id = next_task_id++;
    task.description = description;
    task.priority = priority;
    task.due_date = due_date;
    tasks.push_back(task);
    Logger::get_instance().log("Task added:" + task.toString());
    save_tasks();
}

void TaskManager::remove_task(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task &task) {
        return task.id == id;
    });

    if (it != tasks.end()) {
        tasks.erase(it);
        Logger::get_instance().log("Task removed:" + it->toString());
        save_tasks();
    } else {
        std::cout << "Task not found" << std::endl;
    }
}

void TaskManager::update_task(int id, const std::string &description, int priority, const std::string &due_date) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task &task) {
        return task.id == id;
    });

    if (it != tasks.end()) {
        it->description = description;
        it->priority = priority;
        it->due_date = due_date;
        Logger::get_instance().log("Task updated:" + it->toString());
        save_tasks();
    } else {
        std::cout << "Task not found" << std::endl;
    }
}

void TaskManager::list_tasks(int option) const {
    std::vector<Task> list = tasks;
    switch (option) {
        case 1:
            std::sort(list.begin(), list.end(), compare_by_priority);
            break;
        case 2:
            std::sort(list.begin(), list.end(), compare_by_due_date);
            break;
        default:
            break;
    }

    for (const auto &task: list) {
        std::cout << task.toString() << std::endl;
    }
}

void TaskManager::load_tasks() {
    std::ifstream in_file("tasks.txt");
    if (!in_file.is_open()) {
        Logger::get_instance().log("Failed Loading tasks.txt");
        return;
    }

    std::string line;
    while (std::getline(in_file, line)) {
        std::istringstream iss(line);
        Task task;
        char delimiter;

        iss >> task.id >> delimiter;
        std::getline(iss, task.description, ',');
        iss >> task.priority >> delimiter;
        iss >> task.due_date;
        tasks.push_back(task);

        if (task.id >= next_task_id)next_task_id = task.id + 1;
    }

    in_file.close();
    Logger::get_instance().log("Tasks loaded successfully.");
}

void TaskManager::save_tasks() const {
    std::ofstream out_file("tasks.txt");
    if (!out_file.is_open()) {
        Logger::get_instance().log("Failed Saving tasks.txt");
        return;
    }

    for (const auto &task: tasks) {
        out_file << task.id << "," << task.description << "," << task.priority << "," << task.due_date << std::endl;
        Logger::get_instance().log("Task saved successfully.");
    }

    out_file.close();
}

bool TaskManager::compare_by_priority(const Task &a, const Task &b) {
    return a.priority < b.priority;
}

bool TaskManager::compare_by_due_date(const Task &a, const Task &b) {
    return a.due_date < b.due_date;
}
