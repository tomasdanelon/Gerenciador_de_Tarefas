#include <iostream>
#include <vector>
#include <string>

class Task {
public:
    Task(const std::string& name) : name_(name) {}

    const std::string& GetName() const {
        return name_;
    }

private:
    std::string name_;
};

class TaskManager {
public:
    void AddTask(const std::string& task_name) {
        tasks_.emplace_back(task_name);
    }

    void RemoveTask(int index) {
        if (index >= 0 && index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + index);
        }
    }

    void ListTasks() const {
        for (size_t i = 0; i < tasks_.size(); ++i) {
            std::cout << i + 1 << ". " << tasks_[i].GetName() << std::endl;
        }
    }

private:
    std::vector<Task> tasks_;
};

int main() {
    TaskManager task_manager;
    std::string command;

    while (true) {
        std::cout << "Insira o comando (add, list, remove, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string task_name;
            std::cout << "Insira o nome da tarefa: ";
            std::cin.ignore();
            std::getline(std::cin, task_name);
            task_manager.AddTask(task_name);
        } else if (command == "list") {
            task_manager.ListTasks();
        } else if (command == "remove") {
            int index;
            std::cout << "Insira o numero da tarefa: ";
            std::cin >> index;
            task_manager.RemoveTask(index - 1);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Comando inválido, tente novamente." << std::endl;
        }
    }

    return 0;
}
