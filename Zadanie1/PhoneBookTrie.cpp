#pragma once

#include "TrieNode.h"
#include "PhoneBookTrie.h"
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

void PhoneBookTrie::insertNode(const string& lastName, const string& firstName, const string& phoneNumber)
{
	TrieNode* node = _root.get();
	for (char character : lastName) 
	{
		if (!node->children.count(character))
		{
			node->children[character] = make_unique<TrieNode>();
		}
		node = node->children[character].get();
	}

	node->isEnd = true;
	node->entries[firstName] = phoneNumber;
}

TrieNode* PhoneBookTrie::searchNode(const string& lastName) const
{
	TrieNode* node = _root.get();
	if (!node)
	{
		return nullptr;
	}

	for (char character : lastName)
	{
		if (!node->children.count(character))
		{
			return nullptr;
		}

		node = node->children.at(character).get();
		if (!node)
		{
			return nullptr;
		}
	}

	bool prunedNodeExists = !node->isEnd || node->entries.empty();
	if (prunedNodeExists)
	{
		return nullptr;
	}

	return node;
}

bool PhoneBookTrie::removeNode(const string& lastName, const string& firstName)
{
	/*TrieNode* node = searchNode(lastName);
	if (node && node->entries.count(firstName)) 
	{
		node->entries.erase(firstName);
		return true;
	}

	return false;*/

	return removeHelper(_root, lastName, firstName, 0);
}

// private 
bool PhoneBookTrie::removeHelper(unique_ptr<TrieNode>& node, const string& lastName, const string& firstName, size_t depth)
{
	if (!node)
	{
		return false;
	}

	bool isEndOfLastNamePath = depth == lastName.length();
	if (isEndOfLastNamePath)
	{
		if (!node->entries.count(firstName))
		{
			return false;
		}

		node->entries.erase(firstName); // remove firstname + phonenumber pair

		bool shouldPrune = node->entries.empty() && node->children.empty();
		if (shouldPrune) 
		{
			node.reset(); // delete object managed by smart pointer and set the pointer to nullptr
			return true;
		}

		node->isEnd = !node->entries.empty();  // update end flag
		return true;
	}

	char character = lastName[depth];
	auto& child = node->children[character];
	if (!child)
	{
		return false;
	}

	bool shouldDeleteChild = removeHelper(child, lastName, firstName, depth + 1);

	bool shouldPruneChild = shouldDeleteChild && child == nullptr;
	if (shouldPruneChild) 
	{
		node->children.erase(character);

		bool isNodeEmptyAndNotEnd = node->entries.empty() && node->children.empty() && !node->isEnd;
		if (isNodeEmptyAndNotEnd)
		{
			node.reset();
			return true;
		}
	}

	return false;
}