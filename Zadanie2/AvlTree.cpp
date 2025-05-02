#include "AvlTree.h"
#include "Task.h"
#include <iostream>

AvlTree::AvlTree()
{
	_root = nullptr;
}

AvlTree::~AvlTree()
{
	deleteSubtree(_root);
	_root = nullptr;
}

// public 
void AvlTree::insert(Task* task)
{
	_root = insertNode(_root, task);
}

void AvlTree::remove(const string& deadline, Task* task)
{
	_root = removeNode(_root, deadline, task);
}


vector<Task*> AvlTree::findTasksByDeadline(const string& deadline) const
{
	AvlNode* node = _root;

	while (node)
	{
		if (deadlineCompare(deadline, node->getDeadline()) < 0)
		{
			node = node->getLeftNode();
		}
		else if (deadlineCompare(deadline, node->getDeadline()) > 0)
		{
			node = node->getRightNode();
		}
		else
		{
			return node->getTasks();
		}
	}

	return {};
}

void AvlTree::printTree() const // utility for printing the tree to check the structure
{
	int nodeCount = 0;
	printTreeHelper(_root, 0, nodeCount, "root");
	cout << "Number of nodes in the tree: " << nodeCount << endl;
	cout << "===============================" << endl;
}

// private
AvlNode* AvlTree::insertNode(AvlNode* node, Task* task)
{
	if (!node)
	{
		auto root = new AvlNode(task->getDeadline());
		root->addTask(task);
		return root;
	}

	auto compareResult = deadlineCompare(task, node);
	if (compareResult < 0)
	{
		node->setLeftNode(insertNode(node->getLeftNode(), task));  // insert into the left subtree
	}
	else if (compareResult > 0)
	{
		node->setRightNode(insertNode(node->getRightNode(), task));  // insert into the right subtree
	}
	else
	{
		node->addTask(task);  // add task to the node if deadlines are the same
		return node;
	}

	auto newHeight = 1 + max(getHeight(node->getLeftNode()), getHeight(node->getRightNode()));
	node->setHeight(newHeight);

	int balance = getBalanceFactor(node);
	bool isLeftHeavy = balance > 1 && deadlineCompare(task, node->getLeftNode()) < 0;
	if (isLeftHeavy)
	{
		return rotateRight(node);
	}

	bool isRightHeavy = balance < -1 && deadlineCompare(task, node->getRightNode()) > 0;
	if (isRightHeavy)
	{
		return rotateLeft(node);
	}

	bool isLeftRightCase = balance > 1 && deadlineCompare(task, node->getLeftNode()) > 0;
	if (isLeftRightCase)
	{
		node->setLeftNode(rotateLeft(node->getLeftNode()));
		return rotateRight(node);
	}

	bool isRightLeftCase = balance < -1 && deadlineCompare(task, node->getRightNode()) < 0;
	if (isRightLeftCase)
	{
		node->setRightNode(rotateRight(node->getRightNode()));
		return rotateLeft(node);
	}

	return node;
}

AvlNode* AvlTree::removeNode(AvlNode* node, const string& deadline, Task* task)
{
	if (!node)
	{
		return node;
	}

	// traverse the tree to find the node to remove
	int compareResult = deadlineCompare(deadline, node->getDeadline());
	if (compareResult < 0)
	{
		node->setLeftNode(removeNode(node->getLeftNode(), deadline, task));
	}
	else if (compareResult > 0)
	{
		node->setRightNode(removeNode(node->getRightNode(), deadline, task));
	}
	else
	{
		node->removeTask(task);
		if (node->getTasks().empty()) // if no tasks are left, remove the node
		{
			if (!node->getLeftNode())
			{
				AvlNode* temp = node->getRightNode();
				delete node;
				return temp;
			}
			else if (!node->getRightNode())
			{
				AvlNode* temp = node->getLeftNode();
				delete node;
				return temp;
			}

			// node with two children
			AvlNode* temp = node->getRightNode();
			while (temp && temp->getLeftNode())
			{
				temp = temp->getLeftNode();
			}

			if (temp)
			{
				node->setDeadline(temp->getDeadline());
				node->setTasks(temp->getTasks());
				node->setRightNode(removeNode(node->getRightNode(), temp->getDeadline(), task));
			}
		}
	}

	// balance the tree after removal
	auto newHeight = 1 + max(getHeight(node->getLeftNode()), getHeight(node->getRightNode()));
	node->setHeight(newHeight);

	int balance = getBalanceFactor(node);

	if (balance > 1 && getBalanceFactor(node->getLeftNode()) >= 0)
	{
		return rotateRight(node);
	}

	if (balance > 1 && getBalanceFactor(node->getLeftNode()) < 0)
	{
		node->setLeftNode(rotateLeft(node->getLeftNode()));
		return rotateRight(node);
	}

	if (balance < -1 && getBalanceFactor(node->getRightNode()) <= 0)
	{
		return rotateLeft(node);
	}

	if (balance < -1 && getBalanceFactor(node->getRightNode()) > 0)
	{
		node->setRightNode(rotateRight(node->getRightNode()));
		return rotateLeft(node);
	}

	return node;
}

AvlNode* AvlTree::rotateLeft(AvlNode* node)
{
	AvlNode* rightChildNode = node->getRightNode();
	node->setRightNode(rightChildNode->getLeftNode());
	rightChildNode->setLeftNode(node);
	int newNodeHeight = max(getHeight(node->getLeftNode()), getHeight(node->getRightNode())) + 1;
	node->setHeight(newNodeHeight);
	int newRightChildHeight = max(getHeight(rightChildNode->getLeftNode()), getHeight(rightChildNode->getRightNode())) + 1;
	rightChildNode->setHeight(newRightChildHeight);

	return rightChildNode;
}

AvlNode* AvlTree::rotateRight(AvlNode* node)
{
	AvlNode* leftChild = node->getLeftNode();
	node->setLeftNode(leftChild->getRightNode());
	leftChild->setRightNode(node);
	int newNodeHeight = max(getHeight(node->getLeftNode()), getHeight(node->getRightNode())) + 1;
	node->setHeight(newNodeHeight);
	int newLeftChildHeight = max(getHeight(leftChild->getLeftNode()), getHeight(leftChild->getRightNode())) + 1;
	leftChild->setHeight(newLeftChildHeight);

	return leftChild;
}

void AvlTree::printTreeHelper(AvlNode* node, int depth, int& nodeCount, const string& direction) const
{
	if (!node)
	{
		return;
	}

	if (depth == 0)
	{
		cout << "======= Tree structure ========" << endl;
	}

	nodeCount++;

	cout << node->getDeadline()
		<< " (" << direction << " " + to_string(depth) << ")"
		<< " | Tasks: " << node->getTasks().size()
		<< endl;

	printTreeHelper(node->getLeftNode(), depth + 1, nodeCount, "left");
	printTreeHelper(node->getRightNode(), depth + 1, nodeCount, "right");
}

int AvlTree::getHeight(AvlNode* node)
{
	return node ? node->getHeight() : 0;
}

int AvlTree::getBalanceFactor(AvlNode* node)
{
	auto balance = getHeight(node->getLeftNode()) - getHeight(node->getRightNode());
	return node ? balance : 0;
}

int AvlTree::deadlineCompare(Task* task, AvlNode* node)
{
	return deadlineCompare(task->getDeadline(), node->getDeadline());
}

int AvlTree::deadlineCompare(const string& first, const string& second) const
{
	auto foo1 = first > second;
	return strcmp(first.c_str(), second.c_str());
}

void AvlTree::deleteSubtree(AvlNode* node)
{
	if (!node)
	{
		return;
	}

	deleteSubtree(node->getLeftNode());
	deleteSubtree(node->getRightNode());
	delete node;
}
