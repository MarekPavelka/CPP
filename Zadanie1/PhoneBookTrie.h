#pragma once

#include "TrieNode.h"
#include <memory>
#include <string>

class PhoneBookTrie 
{
    public:
        void insertNode(const std::string& lastName, const std::string& firstName, const std::string& phoneNumber);
        TrieNode* searchNode(const std::string& lastName) const;
        bool removeNode(const std::string& lastName, const std::string& firstName);

    private:
        std::unique_ptr<TrieNode> _root = std::make_unique<TrieNode>();
};

