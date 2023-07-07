#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Task {
public:
    Task(const std::string& name, int priority, const std::string& due_date)
        : name_(name), priority_(priority), due_date_(due_date) {}

    const std::string& GetName() const {
        return name_;
    }

    int GetPriority() const {
        return priority_;
    }

    const std::string& GetDueDate() const {
        return due_date_;
    }

    const std::string& GetNotes() const {
        return notes_;
    }

    void AddNotes(const std::string& notes) {
        notes_ += notes;
    }

private:
    std::string name_;
    int priority_;
    std::string due_date_;
    std::string notes_;
};

class TaskManager {
public:
    void AddTask(const Task& task) {
        tasks_.push_back(task);
    }

    bool AddNotes(int task_index, const std::string& notes) {
        if (task_index >= 0 && task_index < tasks_.size()) {
            tasks_[task_index].AddNotes(notes);
            return true;
        }
        return false;
    }

    bool RemoveTask(int task_index) {
        if (task_index >= 0 && task_index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + task_index);
            return true;
        }
        return false;
    }

    void ListTasks() const {
        for (size_t i = 0; i < tasks_.size(); ++i) {
            std::cout << "Task " << i + 1 << ": " << tasks_[i].GetName() << "\n";
            std::cout << "Priority: " << tasks_[i].GetPriority() << "\n";
            std::cout << "Due date: " << tasks_[i].GetDueDate() << "\n";
            std::cout << "Notes: " << tasks_[i].GetNotes() << "\n";
        }
    }

    void SortTasksByPriority() {
        std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
            return a.GetPriority() < b.GetPriority();
        });
    }

    void SortTasksByDueDate() {
        std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
            return a.GetDueDate() < b.GetDueDate();
        });
    }

    void use(TaskManager& task_manager) {
    std::string command;

    while (true) {
        std::cout << "Insira um comando (add, list, remove, notes, sort_priority, sort_due_date, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string task_name, due_date;
            int priority;
            std::cout << "Insira o nome da tarefa: ";
            std::cin.ignore();
            std::getline(std::cin, task_name);
            std::cout << "Insira a prioridade: ";
            std::cin >> priority;
            std::cout << "Insira a data: ";
            std::cin >> due_date;
            task_manager.AddTask(Task(task_name, priority, due_date));
        } else if (command == "list") {
            task_manager.ListTasks();
        } else if (command == "remove") {
            int index;
            std::cout << "Insira o numero da tarefa a remover: ";
            std::cin >> index;
            if (!task_manager.RemoveTask(index - 1)) {
                std::cout << "Falha ao remover tarefa.\n";
            }
        } else if (command == "notes") {
            int index;
            std::string notes;
            std::cout << "Insira o numero da tarefa a adicionar notas: ";
            std::cin >> index;
            std::cin.ignore();
            std::cout << "Insira a nota: ";
            std::getline(std::cin, notes);
            if (!task_manager.AddNotes(index - 1, notes)) {
                std::cout << "Falha a inserir uma nota.\n"; } 
        } else if (command == "sort_priority") {
            task_manager.SortTasksByPriority();
        }else if (command == "sort_due_date") {
            task_manager.SortTasksByDueDate();
        }else if (command == "exit") {
            break;
        }
    } 
    }

private:
    std::vector<Task> tasks_;
};

/*int main() {
    TaskManager task_manager;
    std::string command;

    while (true) {
        std::cout << "Insira um comando (add, list, remove, notes, sort_priority, sort_due_date, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string task_name, due_date;
            int priority;
            std::cout << "Insira o nome da tarefa: ";
            std::cin.ignore();
            std::getline(std::cin, task_name);
            std::cout << "Insira a prioridade: ";
            std::cin >> priority;
            std::cout << "Insira a data: ";
            std::cin >> due_date;
            task_manager.AddTask(Task(task_name, priority, due_date));
        } else if (command == "list") {
            task_manager.ListTasks();
        } else if (command == "remove") {
            int index;
            std::cout << "Insira o numero da tarefa a remover: ";
            std::cin >> index;
            if (!task_manager.RemoveTask(index - 1)) {
                std::cout << "Falha ao remover tarefa.\n";
            }
        } else if (command == "notes") {
            int index;
            std::string notes;
            std::cout << "Insira o numero da tarefa a adicionar notas: ";
            std::cin >> index;
            std::cin.ignore();
            std::cout << "Insira a nota: ";
            std::getline(std::cin, notes);
            if (!task_manager.AddNotes(index - 1, notes)) {
                std::cout << "Falha a inserir uma nota.\n"; } 
        } else if (command == "sort_priority") {
            task_manager.SortTasksByPriority();
        }
         else if (command == "sort_due_date") {
            task_manager.SortTasksByDueDate();
        }
             } }*/