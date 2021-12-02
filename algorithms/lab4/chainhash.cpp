#include "chainhash.hpp"

ChainHash::ChainHash(size_t n) : size(n)
{
	HashTable = new vector<string>*[n];

	for (size_t i = 0; i < n; i++)
	{
		HashTable[i] = new vector<string>;
	}
}

ChainHash::~ChainHash()
{
	delete[] HashTable;
}

void ChainHash::add(const string& word,const size_t key)
{
	HashTable[key]->push_back(word);
}

void ChainHash::print()
{
	for (size_t i = 0; i < size; i++)
	{
		cout << "[" << i << "] ";
		for (size_t j = 0; j < (*HashTable[i]).size(); j++)
		{
			cout << (*HashTable[i])[j] << " ";
		}
		cout << '\n';
	}
}

void ChainHash::search(const string& word, const size_t key)
{
	for (size_t i = 0; i < HashTable[key]->size(); i++)
	{
		if (HashTable[key]->at(i) == word)
		{
			cout << "Строка " << word << " найдена.\n"
				<< "[" << key << "]" << "[" << i << "] " << word;
			return;
		}
	}

	cout << "Строка " << word << " не найдена.";
}

void ChainHash::del(const string& word, const size_t key)
{
	for (size_t i = 0; i < HashTable[key]->size(); i++)
	{
		if (HashTable[key]->at(i) == word)
		{
			HashTable[key]->erase(HashTable[key]->begin() + i);
		}
	}
}