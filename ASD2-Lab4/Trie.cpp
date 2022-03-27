#include "Trie.h"

vector_string Trie::getAllWords(TrieNode* root, std::string word)
{
	vector_string res;
	if (root->isTerminal)
	{
		res.push_back(word);
	}
	for (auto pair : root->children)
	{
		vector_string childWords = getAllWords(pair.second, word + pair.first);
		res.insert(res.end(), childWords.begin(), childWords.end());
	}
	return res;
}

void Trie::clear(TrieNode* root)
{
	for (auto pair : root->children)
	{
		clear(pair.second);
	}
	delete root;
}

Trie::Trie()
{
	m_root = new TrieNode();
}

Trie::~Trie()
{
	if (m_root)
	{
		clear(m_root);
	}
}

void Trie::insert(std::string word)
{
	TrieNode* current = m_root;
	for (char c : word)
	{
		if (!current->children[c])
		{
			current->children[c] = new TrieNode();
		}
		current = current->children[c];
	}
	current->isTerminal = true;
}

vector_string Trie::findByPrefix(std::string word)
{
	TrieNode* current = m_root;
	for (char c : word)
	{
		if (!current->children[c])
		{
			return {};
		}
		current = current->children[c];
	}
	return getAllWords(current, word);
}