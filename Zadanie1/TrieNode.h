#pragma once

#include <unordered_map>
#include <memory>
#include <string>

class TrieNode
{
    public:
        bool isEnd = false;

        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        std::unordered_map<std::string, std::string> entries;
};
