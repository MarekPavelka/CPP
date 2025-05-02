#pragma once

#include "Task.h"
#include "AvlTree.h"
#include <vector>
#include <string>
using namespace std;

class TaskService
{
    public:
        TaskService(const string& fileName);

        void loadTasks();
        void saveTasks() const;
        bool addTask(Task& task);
        bool removeTask(const string& name);
        bool finishTask(const string& name);
        void printTasks(const string& day = "", const string & deadlineFilter = "", bool listFinished = false) const;
        void printHelp() const;

    private:
        vector<Task> _tasks;
        string _fileName;
        AvlTree _deadlineTree;

        Task* findTask(const string& name);
        void printTaskInfo(const Task& task) const;
};
