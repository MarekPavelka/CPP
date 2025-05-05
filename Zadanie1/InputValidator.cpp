#include "InputValidator.h"
#include <string>
#include <iostream>

using namespace std;

namespace InputValidator
{
	bool wasConfirmed(const string& prompt)
	{
		while (true)
		{
			string input = getValidInput(prompt);

			if (input == "Y" || input == "y")
			{
				return true;
			}
			if (input == "N" || input == "n")
			{
				return false;
			}

			cout << "Please enter Y or N." << endl;
		}
	}

	string getValidInput(const string& prompt)
	{
		string input;
		do
		{
			cout << prompt;
			getline(cin, input);
			input = trim(input);
		} while (input.empty());

		return input;
	}

	int getValidInput(const string& prompt, const int from, const int to)
	{
		string input;
		int parsedInput;

		while (true)
		{
			cout << prompt;
			getline(cin, input);
			input = trim(input);

			if (cin.eof())
			{
				cout << "Input closed. Exiting..." << endl;
				exit(EXIT_SUCCESS);
			}

			if (input.empty())
			{
				cout << "Please enter a number between " << from << " and " << to << endl;
				continue;
			}

			try
			{
				parsedInput = stoi(input);
				bool isChoiceValid = parsedInput >= from && parsedInput <= to;
				if (isChoiceValid)
				{
					return parsedInput;
				}

				cout << "Please enter a number between " << from << " and " << to << endl;
			}
			catch (const exception&)
			{
				cout << "Please enter a valid number." << endl;
			}
		}

		return parsedInput;
	}

	string trim(const string& input)
	{
		auto start = input.find_first_not_of(" \t\n\r");
		auto end = input.find_last_not_of(" \t\n\r");
		if (start == string::npos || end == string::npos)
		{
			return "";
		}

		return input.substr(start, end - start + 1);
	}
}