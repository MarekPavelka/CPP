#pragma once

#include "Contact.h"
#include <string>

class PhoneBookService
{
	public:
		Contact findContact();
		void addContact();
		void deleteContact();
		void addToCallQueue();
		void processCallQueue();

	private:
};