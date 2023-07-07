#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
 * @class Task
 * @brief Classe que representa uma tarefa.
 */
class Task {
public:
    /**
     * @brief Construtor da classe Task.
     * @param name O nome da tarefa.
     * @param priority A prioridade da tarefa.
     * @param due_date A data de vencimento da tarefa.
     */
    Task(const std::string& name, int priority, const std::string& due_date)
        : name_(name), priority_(priority), due_date_(due_date) {}

    /**
     * @brief Obtém o nome da tarefa.
     * @return O nome da tarefa.
     */
    const std::string& GetName() const {
        return name_;
    }

    /**
     * @brief Obtém a prioridade da tarefa.
     * @return A prioridade da tarefa.
     */
    int GetPriority() const {
        return priority_;
    }

    /**
     * @brief Obtém a data de vencimento da tarefa.
     * @return A data de vencimento da tarefa.
     */
    const std::string& GetDueDate() const {
        return due_date_;
    }

    /**
     * @brief Obtém as notas da tarefa.
     * @return As notas da tarefa.
     */
    const std::string& GetNotes() const {
        return notes_;
    }

    /**
     * @brief Adiciona notas à tarefa.
     * @param notes As notas a serem adicionadas.
     */
    void AddNotes(const std::string& notes) {
        notes_ += notes;
    }

private:
    std::string name_;
    int priority_;
    std::string due_date_;
    std::string notes_;
};

/**
 * @class TaskManager
 * @brief Classe que gerencia as tarefas.
 */
class TaskManager {
public:
    /**
     * @brief Adiciona uma tarefa.
     * @param task A tarefa a ser adicionada.
     */
    void AddTask(const Task& task) {
        tasks_.push_back(task);
    }

    /**
     * @brief Adiciona notas a uma tarefa existente.
     * @param task_index O índice da tarefa na lista.
     * @param notes As notas a serem adicionadas.
     * @return true se as notas foram adicionadas com sucesso, false caso contrário.
     */
    bool AddNotes(int task_index, const std::string& notes) {
        if (task_index >= 0 && task_index < tasks_.size()) {
            tasks_[task_index].AddNotes(notes);
            return true;
        }
        return false;
    }

    /**
     * @brief Remove uma tarefa.
     * @param task_index O índice da tarefa na lista.
     * @return true se a tarefa foi removida com sucesso, false caso contrário.
     */
    bool RemoveTask(int task_index) {
        if (task_index >= 0 && task_index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + task_index);
            return true;
        }
        return false;
    }

    /**
     * @brief Lista todas as tarefas.
     */
    void ListTasks() const {
        for (size_t i = 0; i < tasks_.size(); ++i) {
            std::cout << "Task " << i + 1 << ": " << tasks_[i].GetName() << "\n";
            std::cout << "Priority: " << tasks_[i].GetPriority() << "\n";
            std::cout << "Due date: " << tasks_[i].GetDueDate() << "\n";
            std::cout << "Notes: " << tasks_[i].GetNotes() << "\n";
        }
    }

    /**
     * @brief Ordena as tarefas por prioridade.
     */
    void SortTasksByPriority() {
        std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
            return a.GetPriority() < b.GetPriority();
        });
    }

    /**
     * @brief Ordena as tarefas por data de vencimento.
     */
    void SortTasksByDueDate() {
        std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
            return a.GetDueDate() < b.GetDueDate();
        });
    }

    /**
     * @brief Função para uso do TaskManager.
     * @param task_manager O gerenciador de tarefas.
     */
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