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
	TrieNode* node = _trie.searchNode(lastName);
	if (!node) 
	{
		cout << "Contact with last name " << lastName << "not found" << endl << endl;
		return nullopt;
	}

	if (node->entries.empty())
	{
		cout << "No first names found for last name " << lastName << endl << endl;
		return nullopt;
	}

	cout << "Found entries:" << endl;
	
	int i = 1;
	vector<string> firstNames;

	for (const auto& entry : node->entries) 
	{
		cout << i++ << ". " << entry.first << endl;
		firstNames.push_back(entry.first);
	}

	cout << endl;
	int userInput = getValidInput("Select a first name by number (1-" + to_string(firstNames.size()) + "): ", 1, firstNames.size());
	string chosenFirstName = firstNames[userInput - 1];

	Contact contact{ chosenFirstName, lastName, node->entries[chosenFirstName] };
	cout << contact.firstName << " " << contact.lastName << " - " << contact.phoneNumber << endl << endl;

	return contact;
}

void PhoneBookService::addContact()
{
	string firstName = getValidInput("Enter first name: ");
	string lastName = getValidInput("Enter last name: ");
	string phoneNumber = getValidInput("Enter phone number: ");

	_trie.insertNode(lastName, firstName, phoneNumber);

	cout << "Contact " << firstName << " " << lastName << " saved successfully." << endl << endl;
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
		cout << "Contact with last name " << lastName << "not found" << endl << endl;
	}

	string confirm = getValidInput("Confirm delete (Y/N): ");
	if (confirm == "Y")
	{
		bool wasDeleted = _trie.removeNode(contact.lastName, contact.firstName);
		if (wasDeleted)
		{
			cout << "Successfully deleted contact " << contact.firstName << " " << contact.lastName << "." << endl << endl;
		}
		else
		{
			cout << "Delete failed for contact " << contact.firstName << " " << contact.lastName << "." << endl << endl;
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
		cout << "Contact with last name " << lastName << "not found" << endl << endl;
	}

	string confirm = getValidInput("Add to call queue (Y/N): ");
	if (confirm == "Y")
	{
		_callQueue.push(contact);
		cout << "Contact " << contact.firstName << " " << contact.lastName << "was added to the call queue." << endl << endl;
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
		cout << "Call queue is empty." << endl << endl;
	}
}