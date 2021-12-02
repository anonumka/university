#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

size_t toHash(string num)
{
    size_t res = 0, pow = 1;
    for (size_t i = 0; i < num.size(); i++)
    {
        res += (num[i] - 96) * pow;
        pow *= 26;
    }
    int denominator = 1;
    res *= res;
    size_t res_tmp = res;
    while (res_tmp >= 10)
    {
        res_tmp /= 10;
        denominator *= 10;
    }
    res %= denominator;
    return res % 256;
}

void printHashTable(vector<string>** HashTable, int len)
{
    cout << "Hash-таблица: \n";
    for (size_t i = 0; i < 256; i++)
    {
        if (HashTable[i]->size() != 0)
        {
            cout << "[" << i << "] ";
            for (size_t j = 0; j < HashTable[i]->size(); j++)
            {
                cout << HashTable[i]->at(j) << " ";
            }
            cout << '\n';
        }
    }
}

void addString(vector<string>** HashTable, string add_string)
{
    int key = toHash(add_string);
    HashTable[key]->push_back(add_string);
}

void searchString(vector<string>** HashTable, string search)
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
    cout << "Строка " << search << " не найдена.";
}

void deleteString(vector<string>** HashTable, string del_string)
{
    int key = toHash(del_string);
    for (size_t i = 0; i < HashTable[key]->size(); i++)
    {
        if (HashTable[key]->at(i) == del_string)
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
    vector<string> InputString;
    vector<string>** ChainHash = new vector<string>*[256];;
    for (size_t i = 0; i < 256; i++)
        ChainHash[i] = new vector<string>;
    cout << "Программа готова к выполнению.\n";
    int n = 0;
    ist >> n;
    for (size_t i = 0; i < n; i++)
    {
        string tmp;
        ist >> tmp;
        InputString.push_back(tmp);
    }

    for (size_t i = 0; i < n; i++)
    {
        addString(ChainHash, InputString[i]);
    }
        

    printHashTable(ChainHash, n);

    string search;
    cout << "\nВведите число для поиска: ";
    cin >> search;
    searchString(ChainHash, search);

    string del_num;
    cout << "\nВведите число для удаления: ";
    cin >> del_num;
    deleteString(ChainHash, del_num);
    printHashTable(ChainHash, n);
}