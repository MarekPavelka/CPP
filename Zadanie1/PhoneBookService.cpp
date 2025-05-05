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
		cout << "Contact with last name " << lastName << " not found." << endl << endl;
		return nullopt;
	}

	cout << "Contacts with last name " << lastName << ":" << endl;

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
	if (!contactResult.has_value())
	{
		return;
	}

	if (!wasConfirmed("Confirm delete (Y/N): "))
	{
		return;
	}

	contact = contactResult.value();
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

void PhoneBookService::addToCallQueue(const string& lastName)
{
	Contact contact;
	auto contactResult = findContact(lastName);
	if (!contactResult.has_value())
	{
		return;
	}

	if (!wasConfirmed("Add to call queue (Y/N): "))
	{
		return;
	}
	
	contact = contactResult.value();
	if (isInCallQueue(contact))
	{
		cout << "Contact " << contact.firstName << " " << contact.lastName << " is already in the call queue." << endl << endl;
		return;
	}

	_callQueue.push(contact);
	cout << "Contact " << contact.firstName << " " << contact.lastName << " was added to the call queue." << endl << endl;
}

void PhoneBookService::processCallQueue()
{
	while (!_callQueue.empty())
	{
		Contact contact = _callQueue.front();
		cout << "Call: " << contact.firstName << " " << contact.lastName << " - " << contact.phoneNumber << endl;

		if (!wasConfirmed("Call completed? (Y/N): "))
		{
			break;
		}

		_callQueue.pop();
	}

	if (_callQueue.empty())
	{
		cout << "Call queue is empty." << endl << endl;
	}
}

// private
bool PhoneBookService::isInCallQueue(const Contact& contact) const
{
	queue<Contact> tempQueue = _callQueue;

	while (!tempQueue.empty())
	{
		const Contact& queuedContact = tempQueue.front();
		bool wasFound = queuedContact.firstName == contact.firstName
			&& queuedContact.lastName == contact.lastName
			&& queuedContact.phoneNumber == contact.phoneNumber;

		if (wasFound)
		{
			return true;
		}

		tempQueue.pop();
	}

	return false;
}