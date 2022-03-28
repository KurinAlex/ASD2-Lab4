#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#include "BinarySearchTree.h"
#include "Data.h"
#include "Helpers.h"
#include "Trie.h"

using namespace std;

const string fileName = "words.txt";

bool testBinarySearchTree()
{
	srand(time(NULL));
	const int iters = 80000;
	const int keysAmount = iters * 2;
	const int itersToRangeQueries = 1000;
	vector<Data> data(keysAmount);
	vector<Data> dataToInsert(iters);
	vector<Data> dataToErase(iters);
	vector<Data> dataToFind(iters);
	vector<pair<Data, Data>> dataToRangeQueries;
	for (int i = 0; i < iters; i++)
	{
		dataToInsert[i] = data[generateRandLong() % keysAmount];
		dataToErase[i] = data[generateRandLong() % keysAmount];
		dataToFind[i] = data[generateRandLong() % keysAmount];
	}
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		Data minData = Data();
		Data maxData = Data();
		if (maxData < minData)
		{
			swap(minData, maxData);
		}
		dataToRangeQueries.push_back({ minData, maxData });
	}
	BinarySearchTree<Data> myTree;
	clock_t myStart = clock();
	for (int i = 0; i < iters; i++)
	{
		myTree.insert(dataToInsert[i]);
	}
	int myInsertSize = myTree.size();
	int myTreeHeight = myTree.height();
	int optimalTreeHeight = log2(myInsertSize) + 1;
	for (int i = 0; i < iters; i++)
	{
		myTree.erase(dataToErase[i]);
	}
	int myEraseSize = myInsertSize - myTree.size();
	int myFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (myTree.find(dataToFind[i]))
		{
			myFoundAmount++;
		}
	}
	clock_t myEnd = clock();
	float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
	set<Data> stlTree;
	clock_t stlStart = clock();
	for (int i = 0; i < iters; i++)
	{
		stlTree.insert(dataToInsert[i]);
	}
	int stlInsertSize = stlTree.size();
	for (int i = 0; i < iters; i++)
	{
		stlTree.erase(dataToErase[i]);
	}
	int stlEraseSize = stlInsertSize - stlTree.size();
	int stlFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (stlTree.find(dataToFind[i]) != stlTree.end())
		{
			stlFoundAmount++;
		}
	}
	clock_t stlEnd = clock();
	float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
	clock_t myRangeStart = clock();
	int myRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first,
			dataToRangeQueries[i].second);
	}
	clock_t myRangeEnd = clock();
	float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
	clock_t stlRangeStart = clock();
	int stlRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
		const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
		stlRangeFoundAmount += distance(low, up);
	}
	clock_t stlRangeEnd = clock();
	float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
	cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<
		optimalTreeHeight << endl;
	cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
		", found amount : " << myFoundAmount << endl;
	cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount
		<< endl << endl;
	cout << "STL Tree:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize <<
		", found amount: " << stlFoundAmount << endl;
	cout << "Range time: " << stlRangeTime << ", range found amount: " <<
		stlRangeFoundAmount << endl << endl;
	if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
		myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
	{
		cout << "BinarySearchTree test passed" << endl << endl;
		return true;
	}
	cerr << "BinarySearchTree test not passed" << endl << endl;
	return false;
}

bool testEraseRange()
{
	srand(time(NULL));
	BinarySearchTree<Data> bst;
	for (int i = 0; i < 10000; i++)
	{
		bst.insert(Data());
	}
	Data minObject = Data();
	Data maxObject = Data();
	if (maxObject < minObject)
	{
		swap(minObject, maxObject);
	}
	size_t foundBefore = bst.findInRange(minObject, maxObject);
	bst.eraseRange(minObject, maxObject);
	size_t foundAfter = bst.findInRange(minObject, maxObject);
	cout << "Range before erase: " << foundBefore << endl;
	cout << "Range after erase: " << foundAfter << endl;
	if (foundAfter == 0)
	{
		cout << "eraseRange test passed" << endl << endl;
		return true;
	}
	cout << "eraseRange test not passed" << endl << endl;
	return false;
}

void testTrie()
{
	Trie trie;
	string word;
	ifstream file;

	file.open(fileName);
	cout << "Building a trie..." << endl;
	clock_t start = clock();
	while (getline(file, word))
	{
		trie.insert(word);
	}
	clock_t end = clock();
	cout << "Trie built in " << (float(end - start)) / CLOCKS_PER_SEC << endl;
	file.close();

	char answer;
	do
	{
		cout << endl << "Enter prefix to test: ";
		cin >> word;

		vector<string> words = trie.findByPrefix(word);
		if (words.empty())
		{
			cout << "No words found";
		}
		else
		{
			cout << "Output: ";
			auto it = words.begin();
			cout << *(it++);
			for (; it != words.end(); ++it)
			{
				cout << ", " << *it;
			}
		}
		cout << endl;

		do
		{
			cout << "Enter y/n if you'd like to continue/stop testing: ";
			cin >> answer;
			answer = tolower(answer);
		} while (answer != 'y' && answer != 'n');
	} while (answer == 'y');
}

int main()
{
	cout << "BinarySearchTree test: " << endl << endl;
	testBinarySearchTree();
	cout << endl;

	cout << "eraseRange test:" << endl << endl;
	testEraseRange();
	cout << endl;

	cout << "Trie test:" << endl << endl;
	testTrie();
	cin.get();
}