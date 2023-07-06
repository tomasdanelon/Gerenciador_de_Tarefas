#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <iomanip>
#include <sstream>

class Task {
public:
    Task(const std::string& name, int priority, const std::tm& due_date)
        : name_(name), priority_(priority), due_date_(due_date), completed_(false) {}

    const std::string& GetName() const {
        return name_;
    }

    int GetPriority() const {
        return priority_;
    }

    const std::tm& GetDueDate() const {
        return due_date_;
    }

    bool IsCompleted() const {
        return completed_;
    }

    void SetCompleted(bool completed) {
        completed_ = completed;
    }

    const std::string& GetNotes() const {
        return notes_;
    }

    void SetNotes(const std::string& notes) {
        notes_ += notes;
    }

    bool operator<(const Task& other) const {
        if (priority_ != other.priority_) {
            return priority_ < other.priority_;
        }
        return mktime(const_cast<std::tm*>(&due_date_)) > mktime(const_cast<std::tm*>(&other.due_date_));
    }

private:
    std::string name_;
    int priority_;
    std::tm due_date_;
    bool completed_;
    std::string notes_;
};

class TaskManager {
public:
    void AddTask(const Task& task) {
        tasks_.push(task);
    }

    void RemoveTask() {
        if (!tasks_.empty()) {
            tasks_.pop();
        }
    }

    void ListTasks() const {
        std::priority_queue<Task> temp_tasks = tasks_;
        int index = 1;
        while (!temp_tasks.empty()) {
            const Task& task = temp_tasks.top();
            std::cout << index++ << ". " << task.GetName() << " (Prioridade: " << task.GetPriority() << ", Data: ";
            std::cout << std::put_time(&task.GetDueDate(), "%d-%m-%Y") << ", Completa: " << (task.IsCompleted() ? "Sim" : "Nao") << ")" << std::endl;
            if (!task.GetNotes().empty()) {
                std::cout << "    Notes: " << task.GetNotes() << std::endl;
            }
            temp_tasks.pop();
        }
    }

private:
    std::priority_queue<Task> tasks_;
};

std::tm ParseDate(const std::string& date_str) {
    std::tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%d-%m-%Y");
    return tm;
}

int main() {
    TaskManager task_manager;
    std::string command;

    while (true) {
        std::cout << "Enter command (add, list, remove, complete, notes, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string task_name, due_date;
            int priority;
            std::cout << "Insira o nome da tarefa:";
            std::cin.ignore();
            std::getline(std::cin, task_name);
            std::cout << "Insira a prioridade da tarefa(1-5) ";
            std::cin >> priority;
            std::cout << "Insira a data de entrega da tarefa (DD-MM-AAAA): ";
            std::cin >> due_date;
            task_manager.AddTask(Task(task_name, priority, ParseDate(due_date)));
        } else if (command == "list") {
            task_manager.ListTasks();
        } else if (command == "remove") {
            task_manager.RemoveTask();
        } else if (command == "complete") {
            // Mark a task as completed
        } else if (command == "notes") {
            // Add notes to a task
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Comando invalido, tente novamente." << std::endl;
        }
    }

    return 0;
}
