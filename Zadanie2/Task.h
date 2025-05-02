#pragma once

#include <string>
using namespace std;

class Task
{
	public:
		Task(const string& name, const string& description, int priority, const string& deadline, bool getFinished);

		// get set
		const string& getName() const;
		void setName(const string& name);

		const string& getDescription() const;
		void setDescription(const string& description);

		int getPriority() const;
		void setPriority(int priority);

		const string& getDeadline() const;
		void setDeadline(const string& deadline);
		
		const bool getFinished() const;
		void setFinished(bool finished);

	private:
		string _name;
		string _description;
		int _priority;
		string _deadline;
		bool _isFinished;
};
