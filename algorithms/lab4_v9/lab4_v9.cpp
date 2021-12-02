#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int toHash(int num)
{
    int res = 0;
    while (num != 0)
    {
        res += num % 10;
        num /= 10;
    }
    return res % 256;
}

void printHashTable(vector<int>** HashTable, int len)
{
    cout << "Hash-таблица: \n";
    for (size_t i = 0; i < 256; i++)
    {
        cout << "[" << i << "] ";
        for (size_t j = 0; j < HashTable[i]->size(); j++)
        {
            cout << HashTable[i]->at(j) << " ";
        }
        cout << '\n';
    }
}

void addNum(vector<int>** HashTable, int add_num)
{
    int key = toHash(add_num);
    HashTable[key]->push_back(add_num);
}

void searchNum(vector<int>** HashTable, int search)
{
    int key = toHash(search);
    for (size_t i = 0; i < HashTable[key]->size(); i++)
    {
        if (HashTable[key]->at(i) == search)
        {
            cout << "Строка " << search << " найдена.\n"
                << "[" << key << "]" << "[" << i << "] " << search;
            return;
        }
    }
    cout << "Число " << search << " не найдено.";
}

void deleteNum(vector<int>** HashTable, int del_num)
{
    int key = toHash(del_num);
    for (size_t i = 0; i < HashTable[key]->size(); i++)
    {
        if (HashTable[key]->at(i) == del_num)
        {
            HashTable[key]->erase(HashTable[key]->begin() + i);
            return;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");
    ifstream ist("in.txt");
    vector<int> InputNum;
    vector<int>** ChainHash = new vector<int>*[256];
    for (size_t i = 0; i < 256; i++)
        ChainHash[i] = new vector<int>;
    int n = 0;
    ist >> n;
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        ist >> tmp;
        InputNum.push_back(tmp);
    }
    sort(InputNum.begin(), InputNum.begin());
    for (size_t i = 0; i < n; i++)
        addNum(ChainHash, InputNum[i]);

    printHashTable(ChainHash, n);

    int search;
    cout << "\nВведите число для поиска: ";
    cin >> search;
    searchNum(ChainHash, search);

    int del_num;
    cout << "\nВведите число для удаления: ";
    cin >> del_num;
    deleteNum(ChainHash, del_num);
    printHashTable(ChainHash, n);
}