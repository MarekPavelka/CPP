#include "PhoneBookService.h"
#include "InputValidator.h"
#include <iostream>

using namespace std;
using namespace InputValidator;

const int FIRST_OPTION = 1;
const int LAST_OPTION = 6;

string createOptionsPrompt(const int from, const int to);

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

		string prompt = createOptionsPrompt(FIRST_OPTION, LAST_OPTION);
		int input = getValidInput(prompt, FIRST_OPTION, LAST_OPTION);

		switch (input)
		{
			case 1:
			{
				phoneBookService.addContact();
				break;
			}
			case 2:
			{
				string lastName = getValidInput("Enter last name: ");
				phoneBookService.findContact(lastName);
				break;
			}
			case 3:
			{
				string lastName = getValidInput("Enter last name: ");
				phoneBookService.deleteContact(lastName);
				break;
			}
			case 4:
			{
				string lastName = getValidInput("Enter last name: ");
				phoneBookService.addToCallQueue(lastName);
				break;
			}
			case 5:
			{
				phoneBookService.processCallQueue();
				break;
			}
			case 6:
			{
				return EXIT_SUCCESS;
			}
			default:
			{
				cout << "Invalid option." << endl;
			}
		}

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
		return EXIT_FAILURE;
	}
}

string createOptionsPrompt(const int from, const int to)
{
	return string("Choose an option (") +
		to_string(from) + "-" +
		to_string(to) + "): ";
}