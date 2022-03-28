#pragma once

#include <string>

struct Data
{
	std::string nick;
	int rank;
	int experience;
	int donate;

	Data();

	void print();

	friend bool operator < (Data left, Data right)
	{
		return left.nick < right.nick;
	}

	friend bool operator > (Data left, Data right)
	{
		return left.nick > right.nick;
	}

	friend bool operator == (Data left, Data right)
	{
		return left.nick == right.nick;
	}
};