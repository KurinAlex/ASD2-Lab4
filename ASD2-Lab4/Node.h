#pragma once

template<class T>
struct Node
{
	T value;
	Node<T>* left;
	Node<T>* right;
	size_t height;

	Node(T value)
	{
		this->value = value;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
};