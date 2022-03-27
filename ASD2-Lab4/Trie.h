#pragma once

#include "TrieNode.h"

typedef std::vector<std::string> vector_string;

class Trie
{
private:
	TrieNode* m_root;
	vector_string getAllWords(TrieNode* root, std::string word);
	void clear(TrieNode* root);

public:
	Trie();
	~Trie();
	void insert(std::string word);
	vector_string findByPrefix(std::string word);
};