#include "logger.h"
#include "task_manager.h"
#include "command.h"
#include <unordered_map>
#include <functional>
#include <variant>

int main() {
    system("chcp 65001 > nul");
    TaskManager task_manager;

    //方式1:虚基类
    // std::unordered_map<std::string, std::unique_ptr<CommandBase> > commands;
    // commands["add"] = std::make_unique<AddCommand>(task_manager);
    // commands["remove"] = std::make_unique<RemoveCommand>(task_manager);
    // commands["list"] = std::make_unique<ListCommand>(task_manager);
    // commands["update"] = std::make_unique<UpdateCommand>(task_manager);

    // 方式2:类型擦除
    // std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
    // auto add_command = std::make_shared<AddCommand>(task_manager);
    // auto remove_command = std::make_shared<RemoveCommand>(task_manager);
    // auto list_command = std::make_shared<ListCommand>(task_manager);
    // auto update_command = std::make_shared<UpdateCommand>(task_manager);
    //
    // commands["add"] =[add_command](const std::string& args) {
    //     add_command->execute(args);
    // };
    // commands["remove"]=[remove_command](const std::string& args) {
    //     remove_command->execute(args);
    // };
    // commands["list"] =[list_command](const std::string& args) {
    //     list_command->execute(args);
    // };
    // commands["update"]=[update_command](const std::string& args) {
    //     update_command->execute(args);
    // };

    //方式3
    // using command_variant = std::variant<
    //     std::unique_ptr<AddCommand>,
    //     std::unique_ptr<RemoveCommand>,
    //     std::unique_ptr<ListCommand>,
    //     std::unique_ptr<UpdateCommand>
    // >;
    //
    // std::unordered_map<std::string, command_variant> commands;
    // commands["add"] = std::make_unique<AddCommand>(task_manager);
    // commands["remove"] = std::make_unique<RemoveCommand>(task_manager);
    // commands["list"] = std::make_unique<ListCommand>(task_manager);
    // commands["update"] = std::make_unique<UpdateCommand>(task_manager);

    //方法4
    std::unordered_map<std::string, CommandWrapper> commands;
    commands.emplace("add",AddCommand(task_manager));
    commands.emplace("remove",AddCommand(task_manager));
    commands.emplace("list",ListCommand(task_manager));
    commands.emplace("update",UpdateCommand(task_manager));

    std::cout << "欢迎来到任务管理系统." << std::endl;
    std::cout << "可以命令:add,delete,list,update,exit" << std::endl;
    std::string input;
    while (true) {
        std::cout << "\n>";
        std::getline(std::cin, input);
        if (input.empty()) {
            continue;
        }

        size_t space_pos = input.find(' ');
        std::string command = input.substr(0, space_pos);
        std::string args;
        if (space_pos != std::string::npos) {
            args = input.substr(space_pos + 1);
        }

        if (command == "exit") {
            std::cout << "退出程序." << std::endl;
            break;
        }

        auto it = commands.find(command);
        if (it != commands.end()) {
            // std::visit([&args](auto&& cmd_ptr) {
            //     cmd_ptr->execute(args);
            // },it->second);

            it->second.execute(args);
        } else {
            std::cout << "未知命令." << std::endl;
        }
    }

    return 0;
}
