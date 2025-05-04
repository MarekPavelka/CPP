#include "PhoneBookService.h"
#include "InputValidator.h"
#include "Contact.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <queue>

using namespace std;
using namespace InputValidator;

optional<Contact> PhoneBookService::findContact(const string& lastName) const
{
	return Contact();
}

void PhoneBookService::addContact()
{
	string firstName = getValidInput("Enter first name: ");
	string lastName = getValidInput("Enter surname: ");
	string phoneNumber = getValidInput("Enter phone number: ");
	// trie.insert()
	cout << "Contact " << firstName << " " << lastName << " saved successfully." << endl;
}

void PhoneBookService::deleteContact(const string& lastName)
{
	Contact contact;
	auto contactResult = findContact(lastName);
	if (contactResult.has_value())
	{
		contact = contactResult.value();
	}
	else
	{
		cout << "Contact with last name " << lastName << "not found" << endl;
	}

	string confirm = getValidInput("Confirm delete (Y/N): ");
	if (confirm == "Y")
	{
		bool wasDeleted = false; // trie.remove()
		if (wasDeleted)
		{
			cout << "Successfully deleted contact " << contact.firstName << " " << contact.lastName << "." << endl;
		}
		else
		{
			cout << "Delete failed for contact " << contact.firstName << " " << contact.lastName << "." << endl;
		}
	}
}

void PhoneBookService::addToCallQueue(const string& lastName)
{
	Contact contact;
	auto contactResult = findContact(lastName);
	if (contactResult.has_value())
	{
		contact = contactResult.value();
	}
	else
	{
		cout << "Contact with last name " << lastName << "not found" << endl;
	}

	string confirm = getValidInput("Add to call queue (Y/N): ");
	if (confirm == "Y")
	{
		_callQueue.push(contact);
		cout << "Contact " << contact.firstName << " " << contact.lastName << "was added to the call queue." << endl;
	}
}

void PhoneBookService::processCallQueue()
{
	while (!_callQueue.empty())
	{
		Contact contact = _callQueue.front();
		cout << "Call: " << contact.firstName << " " << contact.lastName << " - " << contact.phoneNumber << endl;

		string confirm = getValidInput("Call completed? (Y/N): ");
		if (confirm == "Y")
		{
			_callQueue.pop();
		}
		else
		{
			break;
		}
	}

	if (_callQueue.empty())
	{
		cout << "Call queue is empty." << endl;
	}
}