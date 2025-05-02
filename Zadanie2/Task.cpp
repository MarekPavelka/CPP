#include "Task.h"


Task::Task(const string& name, const string& description, int priority, const string& deadline, bool getFinished)
{
	_name = name;
	_description = description;
	_priority = priority;
	_deadline = deadline;
	_isFinished = getFinished;
}

// get set
const string& Task::getName() const { return _name; }
void Task::setName(const string& name) { _name = name; }

const string& Task::getDescription() const { return _description; }
void Task::setDescription(const string& description) { _description = description; }

int Task::getPriority() const { return _priority; }
void Task::setPriority(int priority) { _priority = priority; }

const string& Task::getDeadline() const { return _deadline; }
void Task::setDeadline(const string& deadline) { _deadline = deadline; }

const bool Task::getFinished() const { return _isFinished; }
void Task::setFinished(bool finished) { _isFinished = finished; }