#include <iostream>

#include "Data.h"
#include "Helpers.h"

Data::Data()
{
	nick = generateNick();
	rank = rand() % 100 + 1;
	experience = rand() % 15 + 1;
	donate = rand() % 100000 + 1;
}

void Data::print()
{
	std::cout << "{ " 
		<< nick << ", " 
		<< rank << ", " 
		<< experience << ", " 
		<< donate << " }";
}