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

	BinarySearchTree(NodeType root)
	{
		m_root = balance(root);
		m_size = size(root);
	}

	size_t getHeight(NodeType root)
	{
		return root ? root->height : 0;
	}

	void correctHeight(NodeType root)
	{
		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
	}

	int getBalanceFactor(NodeType root)
	{
		return getHeight(root->right) - getHeight(root->left);
	}

	NodeType rotateLeft(NodeType root)
	{
		NodeType right = root->right;
		root->right = right->left;
		right->left = root;
		correctHeight(root);
		correctHeight(right);
		return right;
	}

	NodeType rotateRight(NodeType root)
	{
		NodeType left = root->left;
		root->left = left->right;
		left->right = root;
		correctHeight(root);
		correctHeight(left);
		return left;
	}

	NodeType balance(NodeType root)
	{
		correctHeight(root);
		if (getBalanceFactor(root) == 2)
		{
			if (getBalanceFactor(root->right) < 0)
			{
				root->right = rotateRight(root->right);
			}
			return rotateLeft(root);
		}
		if (getBalanceFactor(root) == -2)
		{
			if (getBalanceFactor(root->left) > 0)
			{
				root->left = rotateLeft(root->left);
			}
			return rotateRight(root);
		}
		return root;
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
		return balance(root);
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

	NodeType getMin(NodeType root)
	{
		return root->left ? getMin(root->left) : root;
	}

	NodeType eraseMin(NodeType root)
	{
		if (!root->left)
		{
			return root->right;
		}
		root->left = eraseMin(root->left);
		return balance(root);
	}

	NodeType erase(NodeType root, T object)
	{
		if (!root)
		{
			return nullptr;
		}
		if (object < root->value)
		{
			root->left = erase(root->left, object);
		}
		else if (object > root->value)
		{
			root->right = erase(root->right, object);
		}
		else
		{
			--m_size;
			NodeType left = root->left;
			NodeType right = root->right;
			delete root;
			if (!right)
			{
				return left;
			}
			NodeType min = getMin(right);
			min->right = eraseMin(right);
			min->left = left;
			return balance(min);
		}
		return balance(root);
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
		m_root = erase(m_root, object);
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
		return getHeight(m_root);
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