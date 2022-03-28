#include "Helpers.h"

long long generateRandLong()
{
	long long num = 0;
	do
	{
		num = rand() % 10;
	} while (num == 0);
	for (int i = 1; i < 10; i++)
	{
		num = num * 10 + rand() % 10;
	}
	return num;
}

std::string generateNick()
{
	std::string nick = "";
	for (int i = 0; i < 6; i++)
	{
		nick += rand() % 26 + 'A';
	}
	for (int i = 0; i < 4; i++)
	{
		nick += rand() % 10 + '0';
	}
	return nick;
}