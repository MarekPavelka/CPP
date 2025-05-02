#pragma once

#include "AvlNode.h"
#include <string>

class AvlTree 
{
    public:
        AvlTree();  
        ~AvlTree();  

        void insert(Task* task);
        void remove(const string& deadline, Task* task);
        vector<Task*> findTasksByDeadline(const string& deadline) const;
        void printTree() const;

    private:
        AvlNode* _root;

        AvlNode* insertNode(AvlNode* node, Task* task);
        AvlNode* removeNode(AvlNode* node, const string& deadline, Task* task);
        AvlNode* rotateLeft(AvlNode* node);
        AvlNode* rotateRight(AvlNode* node);
        void printTreeHelper(AvlNode* node, int depth, int& nodeCount, const string& direction) const;
        int getHeight(AvlNode* node);
        int getBalanceFactor(AvlNode* node);
        int deadlineCompare(Task* task, AvlNode* node);
        int deadlineCompare(const string& first, const string& second) const;
        void deleteSubtree(AvlNode* node);
};