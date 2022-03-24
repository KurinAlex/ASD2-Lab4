#pragma once

#include <iostream>
#include <algorithm>

#include "Node.h"

template<class T>
class BinarySearchTree
{
	typedef Node<T>*                      NodeType;
	typedef std::pair<NodeType, NodeType> NodePair;
	typedef BinarySearchTree<T>           BST;
	typedef std::pair<BST, BST>           BSTPair;

private:
	NodeType m_root;
	size_t m_size;

	T minimum(NodeType root)
	{
		return root->left ? minimum(root->left) : root->value;
	}

	NodeType insert(NodeType root, T object)
	{
		if (!root)
		{
			++m_size;
			return new Node<T>(object);
		}
		else if (object < root->value)
		{
			root->left = insert(root->left, object);
		}
		else if (object > root->value)
		{
			root->right = insert(root->right, object);
		}
		return root;
	}

	NodeType find(NodeType root, T object)
	{
		if (!root || root->value == object)
		{
			return root;
		}
		if (object < root->value)
		{
			return find(root->left, object);
		}
		return find(root->right, object);
	}

	NodeType erase(NodeType root, T object, bool changeSize)
	{
		if (!root)
		{
			return root;
		}
		if (object < root->value)
		{
			root->left = erase(root->left, object, changeSize);
		}
		else if (object > root->value)
		{
			root->right = erase(root->right, object, changeSize);
		}
		else
		{
			if (changeSize)
			{
				--m_size;
			}
			if (root->left && root->right)
			{
				root->value = minimum(root->right);
				root->right = erase(root->right, root->value, false);
			}
			else
			{
				if (root->left)
				{
					root = root->left;
				}
				else if (root->right)
				{
					root = root->right;
				}
				else
				{
					root = nullptr;
				}
			}
		}
		return root;
	}

	size_t size(NodeType root)
	{
		return root ? size(root->left) + size(root->right) + 1 : 0;
	}

	void print(NodeType root)
	{
		if (root)
		{
			print(root->left);
			root->value.print();
			std::cout << std::endl;
			print(root->right);
		}
	}

	size_t height(NodeType root)
	{
		return root ? std::max(height(root->left), height(root->right)) + 1 : 0;
	}

	size_t findInRange(NodeType root, T minObject, T maxObject)
	{
		if (!root)
		{
			return 0;
		}
		if (root->value < minObject)
		{
			return findInRange(root->right, minObject, maxObject);
		}
		if (root->value > maxObject)
		{
			return findInRange(root->left, minObject, maxObject);
		}
		return findInRange(root->left, minObject, maxObject) + findInRange(root->right, minObject, maxObject) + 1;
	}

	static NodeType merge(NodeType root1, NodeType root2)
	{
		if (!root2)
		{
			return root1;
		}
		if (!root1)
		{
			return root2;
		}
		if (root1->value > root2->value)
		{
			root1->right = merge(root1->right, root2);
			return root1;
		}
		root2->left = merge(root1, root2->left);
		return root2;
	}

	static NodePair split(NodeType root, T object)
	{
		if (!root)
		{
			return { nullptr, nullptr };
		}
		if (root->value < object)
		{
			NodePair nodePair = split(root->right, object);
			root->right = nodePair.first;
			return { root, nodePair.second };
		}
		NodePair nodePair = split(root->left, object);
		root->left = nodePair.second;
		return { nodePair.first, root };
	}

	void clear(NodeType root)
	{
		if (root->left)
		{
			clear(root->left);
		}
		if (root->right)
		{
			clear(root->right);
		}
		delete root;
	}

public:
	BinarySearchTree()
	{
		m_root = nullptr;
		m_size = 0;
	}

	BinarySearchTree(NodeType root)
	{
		m_root = root;
		m_size = size(root);
	}

	~BinarySearchTree()
	{
		if (m_root)
		{
			clear(m_root);
		}
	}

	void insert(T object)
	{
		m_root = insert(m_root, object);
	}

	bool find(T object)
	{
		return find(m_root, object) != nullptr;
	}

	void erase(T object)
	{
		m_root = erase(m_root, object, true);
	}

	size_t size()
	{
		return m_size;
	}

	void print()
	{
		print(m_root);
	}

	int height()
	{
		return height(m_root);
	}

	size_t findInRange(T minObject, T maxObject)
	{
		return findInRange(m_root, minObject, maxObject);
	}

	static BST merge(BST tree1, BST tree2)
	{
		return BST(merge(tree1.m_root, tree2.m_root));
	}

	static BSTPair split(BST tree, T object)
	{
		NodePair nodePair = split(tree.m_root, object);
		return { BST(nodePair.first), BST(nodePair.second) };
	}

	void eraseRange(T minObject, T maxObject)
	{
		NodePair nodePair = split(m_root, minObject);
		m_root = merge(nodePair.first, split(nodePair.second, maxObject).second);
	}
};