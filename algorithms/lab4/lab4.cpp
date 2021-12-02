#include <iostream>
#include <fstream>
#include <vector>
#include "chainhash.hpp"
#include "hash.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    ifstream ist("C:\\Users\\1\\source\\repos\\lab4\\lab4\\in.txt");
    
    size_t n;
    ist >> n;

    ChainHash hashTable(n);
    for (size_t i = 0; i < n; i++)
    {
        string input;
        ist >> input;
        Hash newHash;
        newHash.insert(input);
        newHash.print();
        hashTable.add(input, newHash.getHash(n));
    }

    cout << "Hash-таблица: \n";
    hashTable.print();

    string search;
    cout << "\nВведите строку для поиска: ";
    cin >> search;
    Hash searchHash;
    searchHash.insert(search);
    hashTable.search(search, searchHash.getHash(n));

    cout << "\nВведите строку, которую удалить: ";
    cin >> search;
    Hash deleteHash;
    deleteHash.insert(search);
    hashTable.del(search, deleteHash.getHash(n));

    cout << "\nHash-таблица после удаления " << search << ": \n";
    hashTable.print();
}