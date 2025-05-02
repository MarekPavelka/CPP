#include "AvlNode.h"
#include "Task.h"

AvlNode::AvlNode(const string& deadline)
{
    _deadline = deadline;
    _left = nullptr;
    _right = nullptr;
    _height = 1;
}

AvlNode::~AvlNode() 
{
}

// get set
const vector<Task*>& AvlNode::getTasks() const { return _tasks; }
void AvlNode::setTasks(const vector<Task*>& tasks) { _tasks = tasks; }

const string& AvlNode::getDeadline() const { return _deadline; }
void AvlNode::setDeadline(const string& deadline) { _deadline = deadline; }

AvlNode* AvlNode::getLeftNode() const { return _left; }
void AvlNode::setLeftNode(AvlNode* left) { _left = left; }

AvlNode* AvlNode::getRightNode() const { return _right; }
void AvlNode::setRightNode(AvlNode* right) { _right = right; }

int AvlNode::getHeight() const { return _height; }
void AvlNode::setHeight(int height) { _height = height; }

// other
void AvlNode::addTask(Task* task)
{
    _tasks.push_back(task); 
}

void AvlNode::removeTask(Task* task)
{
    auto iterator = find(_tasks.begin(), _tasks.end(), task);
    bool wasTaskFound = iterator != _tasks.end();
    if (wasTaskFound)
    {
        _tasks.erase(iterator); 
    }
}
