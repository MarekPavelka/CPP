#pragma once

#include "TrieNode.h"
#include "PhoneBookTrie.h"
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

void PhoneBookTrie::insert(const string& lastName, const string& firstName, const string& phoneNumber)
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
	for (char character : lastName)
	{
		if (!node->children.count(character))
		{
			return nullptr;
		}

		node = node->children[character].get();
	}

	return node->isEnd ? node : nullptr;
}

bool PhoneBookTrie::remove(const string& lastName, const string& firstName)
{
	TrieNode* node = searchNode(lastName);
	if (node && node->entries.count(firstName)) 
	{
		node->entries.erase(firstName);
		return true;
	}

	return false;
}