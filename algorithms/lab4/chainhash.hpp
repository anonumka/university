#include "hash.hpp"
#pragma once
class ChainHash
{
public:
	ChainHash(size_t n);
	~ChainHash();
	void add(const string& word, const size_t key);
	void print();
	void search(const string& word, const size_t key);
	void del (const string& word, const size_t key);
private:
	vector<string>** HashTable;
	size_t size;
};

