#include "PhoneBookService.h"
#include <iostream>

using namespace std;

int getValidInput(const string& prompt);
string trim(const string& input);

int main()
{
	try
	{
		PhoneBookService phoneBookService;

		cout << "========== MENU ==========" << endl;
		cout << "1. Add contact" << endl;
		cout << "2. Find contact" << endl;
		cout << "3. Delete contact" << endl;
		cout << "4. Add to call queue" << endl;
		cout << "5. Start call queue" << endl;
		cout << "6. Exit" << endl;
		cout << "==========================" << endl;

		int input = getValidInput("Choose an option (1-6): ");

		switch (input)
		{
		case 1:
			phoneBookService.addContact();
			break;
		case 2:
			phoneBookService.findContact();
			break;
		case 3:
			phoneBookService.deleteContact();
			break;
		case 4:
			phoneBookService.addToCallQueue();
			break;
		case 5:
			phoneBookService.processCallQueue();
			break;
		case 6:
			return EXIT_SUCCESS;
		default:
			cout << "Invalid option." << endl;
		}

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
		return EXIT_FAILURE;
	}
}

int getValidInput(const string& prompt)
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
			cout << "Please select the option..." << endl;
			continue;
		}

		try
		{
			parsedInput = stoi(input);
			bool isChoiceValid = parsedInput >= 1 && parsedInput <= 6;
			if (isChoiceValid)
			{
				return parsedInput;
			}

			cout << "Please enter a number between 1 and 6." << endl;
		}
		catch (const std::exception&)
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