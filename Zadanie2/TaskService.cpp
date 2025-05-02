#include "TaskService.h"
#include "AvlTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <ios>

TaskService::TaskService(const string& fileName)
{
	_fileName = fileName;
}

void TaskService::loadTasks()
{
	_tasks.clear();
	ifstream file(_fileName);
	if (!file.is_open())
	{
		ofstream createFile(_fileName);
		if (!createFile.is_open())
		{
			throw runtime_error("Failed to create file " + _fileName);
		}

		return;
	}

	string line;
	while (getline(file, line))
	{
		stringstream stream(line);
		string name;
		string description;
		string deadline;
		int priority;
		bool finished;

		getline(stream, name, '|');
		getline(stream, description, '|');
		stream >> priority;
		stream.ignore(1);
		getline(stream, deadline, '|');
		stream >> finished;

		if (name.empty())
		{
			cout << "Skipping malformed task line: " << line << endl;
			continue;
		}

		auto task = new Task(name, description, priority, deadline, finished);
		_tasks.push_back(*task);
		_deadlineTree.insert(task); // create tree
	}
}

void TaskService::saveTasks() const
{
	ofstream file(_fileName, ios::trunc);

	for (const auto& task : _tasks)
	{
		file << task.getName() << '|'
			<< task.getDescription() << '|'
			<< task.getPriority() << '|'
			<< task.getDeadline() << '|'
			<< task.getFinished() << '\n';
	}
}

bool TaskService::addTask(Task& task)
{
	auto taskName = task.getName();
	if (findTask(taskName))
	{
		cout << "Task with name " << taskName << " already exists." << endl;
		return false;
	}

	_tasks.push_back(task);
	_deadlineTree.insert(&task);

	saveTasks();
	cout << "Task with name " << taskName << " added successfully." << endl;

	return true;
}

bool TaskService::removeTask(const string& taskName)
{
	for (auto taskIterator = _tasks.begin(); taskIterator != _tasks.end(); taskIterator++)
	{
		auto name = taskIterator->getName();
		if (name == taskName)
		{
			_deadlineTree.remove(taskIterator->getDeadline(), &(*taskIterator));
			_tasks.erase(taskIterator);
			saveTasks();
			cout << "Task with name " << name << " removed successfully." << endl;

			return true;
		}
	}

	cout << "Task with name " << taskName << " was not found." << endl;
	return false;
}

bool TaskService::finishTask(const string& taskName)
{
	Task* task = findTask(taskName);
	if (!task)
	{
		cout << "Task with name " << taskName << " was not found." << endl;
		return false;
	}

	task->setFinished(true);
	saveTasks();

	cout << "Task with name " << taskName << " marked as finished." << endl;
	return true;
}

void TaskService::printTasks(const string& day, const string& deadlineDay, bool printFinishedTasks) const
{
	if (!deadlineDay.empty())
	{
		auto tasks = _deadlineTree.findTasksByDeadline(deadlineDay);
		for (auto task : tasks)
		{
			if (task->getFinished() != printFinishedTasks)
			{
				continue;
			}

			printTaskInfo(*task);
		}
	}
	else if (!day.empty())
	{
		auto tasks = _deadlineTree.findTasksByDeadline(day);
		for (auto task : tasks)
		{
			if (task->getFinished() != printFinishedTasks)
			{
				continue;
			}

			printTaskInfo(*task);
		}
	}
	else
	{
		for (const auto& task : _tasks)
		{
			if (printFinishedTasks)
			{
				if (task.getFinished() != printFinishedTasks)
				{
					continue;
				}

				printTaskInfo(task);
			}
			else
			{
				printTaskInfo(task);
			}
		}
	}
}

// private
Task* TaskService::findTask(const string& name)
{
	for (auto& task : _tasks)
	{
		if (task.getName() == name)
		{
			return &task;
		}
	}

	return nullptr;
}

void TaskService::printTaskInfo(const Task& task) const
{
	cout << "Title: " << task.getName() << endl;
	cout << "Description: " << task.getDescription() << endl;
	cout << "Priority: " << task.getPriority() << endl;
	cout << "Deadline: " << task.getDeadline() << endl;
	cout << "Status: " << (task.getFinished() ? "Finished" : "Not finished") << endl;
	cout << "--------------------------" << endl;
}