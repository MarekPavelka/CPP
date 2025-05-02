#include "TaskService.h"
#include "DateHelper.h"
#include "cxxopts.hpp"
#include <iostream>

using namespace std;
using namespace cxxopts;

const string DEFAULT_FILE_NAME = "tasks.db.txt";
const string DEFAULT_TASK_PRIO = "5";
const string OPTION_ADD = "add";
const string OPTION_REMOVE = "remove";
const string OPTION_LIST = "list";
const string OPTION_DONE = "done";
const string OPTION_TITLE = "title";
const string OPTION_DESC = "desc";
const string OPTION_PRIO = "priority";
const string OPTION_DEADLINE = "deadline";
const string OPTION_TODAY = "today";
const string OPTION_TOMORROW = "tomorrow";

bool wasOptionProvided(ParseResult& optionsResult, string optionName);

int main(int argc, char* argv[])
{
	auto taskService = TaskService(DEFAULT_FILE_NAME);
	taskService.loadTasks();

	try
	{
		Options options("Zadanie2", "Tasks manager");

		options.add_options()
			(OPTION_ADD, "Add new task")
			("t,title", "Task title", value<string>())
			(OPTION_DESC, "Task description", value<string>()->default_value(""))
			("p,priority", "Task priority", value<int>()->default_value(DEFAULT_TASK_PRIO))
			("d,deadline", "Task deadline (yyyy-mm-dd)", value<string>()->default_value(""))
			(OPTION_REMOVE, "Remove task")
			(OPTION_DONE, "Mark task as done")
			(OPTION_LIST, "Print tasks")
			(OPTION_TODAY, "Use today")
			(OPTION_TOMORROW, "Use tomorrow date")
			("h,help", "Print help");

		auto parsedOptions = options.parse(argc, argv);

		if (parsedOptions.count(OPTION_ADD))
		{
			if (!wasOptionProvided(parsedOptions, OPTION_TITLE))
			{
				return EXIT_FAILURE;
			}

			string title = parsedOptions[OPTION_TITLE].as<string>();
			string desc = parsedOptions[OPTION_DESC].as<string>();
			int priority = parsedOptions[OPTION_PRIO].as<int>();
			string deadline = parsedOptions[OPTION_DEADLINE].as<string>();

			if (!deadline.empty())
			{
				bool isDeadlineInIsoFormat = deadline.length() == 10;
				if (!isDeadlineInIsoFormat)
				{
					throw invalid_argument("Invalid date format. Expected yyyy-mm-dd.");
				}
			}

			if (deadline.empty())
			{
				deadline = getTodayDate();
			}

			auto newTask = Task(title, desc, priority, deadline, false);
			taskService.addTask(newTask);
		}
		else if (parsedOptions.count(OPTION_REMOVE))
		{
			if (!wasOptionProvided(parsedOptions, OPTION_TITLE))
			{
				return EXIT_FAILURE;
			}

			taskService.removeTask(parsedOptions[OPTION_TITLE].as<string>());
		}
		else if (parsedOptions.count(OPTION_DONE) && !parsedOptions.count(OPTION_LIST))
		{
			if (!wasOptionProvided(parsedOptions, OPTION_TITLE))
			{
				return EXIT_FAILURE;
			}

			taskService.finishTask(parsedOptions[OPTION_TITLE].as<string>());
		}
		else if (parsedOptions.count(OPTION_LIST))
		{
			string deadline;
			string day;

			if (parsedOptions.count(OPTION_DEADLINE))
			{
				deadline = parsedOptions[OPTION_DEADLINE].as<string>();
			}
			else
			{
				if (parsedOptions.count(OPTION_TODAY))
				{
					day = getTodayDate();
				}

				if (parsedOptions.count(OPTION_TOMORROW))
				{
					day = getTomorrowDate();
				}
			}

			bool printDoneTasks = parsedOptions.count(OPTION_DONE);
			taskService.printTasks(day, deadline, printDoneTasks);
		}
		if (parsedOptions.count("help"))
		{
			cout << options.help() << endl;
			return EXIT_SUCCESS;
		}
	}
	catch (const exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
		return EXIT_FAILURE;
	}

	EXIT_SUCCESS;
}

bool wasOptionProvided(ParseResult& optionsResult, string optionName)
{
	if (!optionsResult.count(optionName))
	{
		cout << optionName << " is required." << endl;
		return false;
	}

	return true;
}