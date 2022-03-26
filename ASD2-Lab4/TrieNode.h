#pragma once

#include <unordered_map>

struct TrieNode
{
	std::unordered_map<char, TrieNode*> children;
	bool isTerminal;

	TrieNode();
};