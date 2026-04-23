//
// Created by 33722 on 2026/4/21.
//

#ifndef TODO_LIST_MANAGER_TASK_MANAGER_H
#define TODO_LIST_MANAGER_TASK_MANAGER_H
#include "task.h"


class TaskManager {
public:
    TaskManager();

    ~TaskManager() = default;

public:
    void add_task(const std::string& description, int priority, const std::string &due_date);

    void remove_task(int id);

    void update_task(int id, const std::string& description, int priority, const std::string &due_date);

    void list_tasks(int option) const; //0:按id,1:按优先级,2:按日期
    void load_tasks();

    void save_tasks() const;

private:
    static bool compare_by_priority(const Task &a, const Task &b);

    static bool compare_by_due_date(const Task &a, const Task &b);

private:
    std::vector<Task> tasks;
    int next_task_id;
};


#endif //TODO_LIST_MANAGER_TASK_MANAGER_H
