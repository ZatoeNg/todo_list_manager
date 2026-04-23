//
// Created by 33722 on 2026/4/21.
//

#ifndef TODO_LIST_MANAGER_COMMAND_H
#define TODO_LIST_MANAGER_COMMAND_H
#include <string>

// class CommandBase {
// public:
//     virtual void execute(const std::string &args) = 0;
// };

template<typename Derived>
class Command{
public:
    void execute(const std::string &args) {
        (static_cast<Derived *>(this))->executeImpl(args);
    }
};

#include "task_manager.h"
#include "logger.h"

class AddCommand : public Command<AddCommand> {
public:
    AddCommand(TaskManager &manager) : _task_manager(manager) {
    }

    void executeImpl(const std::string &args) {
        size_t pos_1 = args.find(',');
        size_t pos_2 = args.find(',', pos_1 + 1);
        if (pos_1 == std::string::npos || pos_2 == std::string::npos) {
            Logger::get_instance().log("参数格式错误,请使用:add <描述>,<优先级>,<截止日期>");
            std::cout<<"参数格式错误,请使用:add <描述>,<优先级>,<截止日期>"<<std::endl;
            return;
        }

        std::string description = args.substr(0, pos_1);
        int priority = std::stoi(args.substr(pos_1 + 1, pos_2 - pos_1 - 1));
        std::string due_date = args.substr(pos_2 + 1);

        _task_manager.add_task(description, priority, due_date);
        std::cout << "任务添加成功." << std::endl;
    }

private:
    TaskManager &_task_manager;
};

class RemoveCommand : public Command<RemoveCommand> {
public:
    RemoveCommand(TaskManager &manager) : _task_manager(manager) {
    }

    void executeImpl(const std::string &args) {
        try {
            size_t pos;
            int id = std::stoi(args, &pos);
            if (pos != args.length()) {
                Logger::get_instance().log("参数格式错误,请使用:add <描述>,<优先级>,<截止日期>");
                std::cout<<"参数格式错误,请使用:remove <ID>"<<std::endl;
                return;
            }

            _task_manager.remove_task(id);
            std::cout << "任务删除成功." << std::endl;
        } catch (const std::invalid_argument &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        } catch (const std::out_of_range &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        }
    }

private:
    TaskManager &_task_manager;
};

class ListCommand : public Command<ListCommand> {
public:
    ListCommand(TaskManager &manager) : _task_manager(manager) {
    }

    void executeImpl(const std::string &args) {
        try {
            int sort_type = 0;
            if (!args.empty()) {
                sort_type = std::stoi(args);
            }
            std::cout << "当前任务列表:" << std::endl;
            _task_manager.list_tasks(sort_type);
        } catch (const std::invalid_argument &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        } catch (const std::out_of_range &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        }
    }

private:
    TaskManager &_task_manager;
};

class UpdateCommand : public Command<UpdateCommand> {
public:
    UpdateCommand(TaskManager &manager) : _task_manager(manager) {
    }

    void executeImpl(const std::string &args) {
        try {
            size_t pos_1 = args.find(',');
            size_t pos_2 = args.find(',', pos_1 + 1);
            size_t pos_3 = args.find(',', pos_2 + 1);
            if (pos_1 == std::string::npos || pos_2 == std::string::npos || pos_3 == std::string::npos) {
                Logger::get_instance().log("参数格式错误,请使用:add <描述>,<优先级>,<截止日期>");
                std::cout<<"参数格式错误,请使用:update <ID>,<描述>,<优先级>,<截止日期>"<<std::endl;
                return;
            }

            int id = std::stoi(args.substr(0, pos_1));
            std::string description = args.substr(pos_1 + 1, pos_2 - pos_1 - 1);
            int priority = std::stoi(args.substr(pos_2 + 1, pos_3 - pos_2 - 1));
            std::string due_date = args.substr(pos_3 + 1);
            _task_manager.update_task(id, description, priority, due_date);
            std::cout << "任务更新成功." << std::endl;
        } catch (const std::invalid_argument &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        } catch (const std::out_of_range &e) {
            Logger::get_instance().log("参数格式错误.");
            return;
        }
    }

private:
    TaskManager &_task_manager;
};

class CommandWrapper {

    struct Concept {
        virtual void execute(const std::string &args) =0;
    };

    template<typename T>
    struct Model : public Concept {
        T command;
        Model(T cmd):command(std::move(cmd)) {}
        void execute(const std::string &args) {
            command.execute(args);
        }
    };

public:
    template <typename T>
    CommandWrapper(T cmd):impl(std::make_unique<Model<T>>(std::move(cmd))) {}
    void execute(const std::string &args) {
        impl->execute(args);
    }
private:
    std::unique_ptr<Concept> impl;
};

#endif //TODO_LIST_MANAGER_COMMAND_H
