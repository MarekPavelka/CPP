#pragma once

#include "Contact.h"
#include <string>
#include <optional>
#include <queue>

class PhoneBookService
{
	public:
		std::optional<Contact> findContact(const std::string& lastName) const;
		void addContact();
		void deleteContact(const std::string& lastName);
		void addToCallQueue(const std::string& lastName);
		void processCallQueue();

	private:
		std::queue<Contact> _callQueue;		
};