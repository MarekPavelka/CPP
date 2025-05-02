#pragma once

#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class AvlNode 
{
    public:
        AvlNode(const string& deadline);
        ~AvlNode();

        // get set
        const vector<Task*>& getTasks() const;
		void setTasks(const vector<Task*>& tasks);

		const string& getDeadline() const;
		void setDeadline(const string& deadline);

        AvlNode* getLeftNode() const;
        void setLeftNode(AvlNode* left);

        AvlNode* getRightNode() const;
        void setRightNode(AvlNode* right);

        int getHeight() const;
        void setHeight(int height);

        // other
        void addTask(Task* task);
        void removeTask(Task* task);

    private:
        string _deadline;
        AvlNode* _left;
        AvlNode* _right;
        int _height;
        vector<Task*> _tasks;
};
