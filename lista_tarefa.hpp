#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>

class Task{
public:
    Task(const std::string& description, bool completed = false)
        : description(description), completed(completed) {}

    std::string getDescription() const {
        return description;
    }

    bool isCompleted() const {
        return completed;
    }

    void setCompleted(bool completed) {
        this->completed = completed;
    }

private:
    std::string description;
    bool completed;
};

class TaskManager{
public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].setCompleted(true);
        }
    }

    void printTasks() const {
        for (int i = 0; i < tasks.size(); ++i) {
            const Task& task = tasks[i];
            std::cout << "[" << (i + 1) << "] " << (task.isCompleted() ? "[X] " : "[ ] ")
                      << task.getDescription() << std::endl;
        }
    }

private:
    std::vector<Task> tasks;
};

#endif
