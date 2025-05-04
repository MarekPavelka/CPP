#pragma once

#include <string>

namespace InputValidator
{
	std::string getValidInput(const std::string& prompt);
	std::string trim(const std::string& input);
	int getValidInput(const std::string& prompt, const int from, const int to);
}