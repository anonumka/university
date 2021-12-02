#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

float time_checker(void(*func)(vector<string>& arr_string, string& check), vector<string>& arr_string, string& check)
{
    auto t1 = high_resolution_clock::now();

    func(arr_string, check);

    auto t2 = high_resolution_clock::now();

    return duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
}

int string_system(string check_size)
{
    int sum = 0, size = check_size.size(), min_elem = 96, pow = 1;
    for (int i = size - 1; i >= 0; i--)
    {
        sum += (check_size[i] - min_elem) * pow;
        pow *= 26;
    }
    return sum;
}

bool wayToSort(string i, string j)
{
    return string_system(i) < string_system(j);
}

void linear_search(vector<string> &arr_string, string &check)
{
    int min = -1;
    int check_num = string_system(check);

    for (size_t i = 0; i < arr_string.size(); i++)
    {
        int string_num = string_system(arr_string[i]);
        if (string_num > check_num)
        {
            min = i;
            break;
        }
    }

    if (min != -1)
    {
        int min_num = string_system(arr_string[min]);
        for (size_t i = 0; i < arr_string.size(); i++)
        {
            int string_num = string_system(arr_string[i]);
            if (string_num > check_num)
                if (string_num < min_num)
                {
                    min = i;
                    min_num = string_num;
                }
                    
        }
        //cout << "\nПоследовательный поиск: " << arr_string[min];
    }
    //else { cout << "\nПоследовательный поиск ничего не нашел."; }
}

void binary_search(vector<string>& arr_string, string& check)
{

    int start = 0,
        finish = arr_string.size() - 1,
        start_num = string_system(arr_string[start]),
        finish_num = string_system(arr_string[finish]),
        check_num = string_system(check);

    if ((check_num > finish_num) || (check_num < start_num))
    {
        cout << "\nБинарный поиск ничего не нашел.";
        return;
    }

    while (start < finish)
    {
        int i = start + ((finish - start) / 2);

        int string_num = string_system(arr_string[i]);
        if (string_num == check_num) 
        { 
            start = i;
            break; 
        }

        if (string_num > check_num)
        {
            finish = i - 1;
            finish_num = string_system(arr_string[finish]);
        }
        else
        {
            start = i + 1;
            start_num = string_system(arr_string[start]);
        }
    }

    if (arr_string[start] > check)
        cout << "\nБинарный поиск: " << arr_string[start];
    else
        cout << "\nБинарный поиск: " << arr_string[start + 1];
}

void interpolating_search(vector<string>& arr_string, string& check)
{

    int start = 0,
        finish = arr_string.size() - 1,
        start_num = string_system(arr_string[start]),
        finish_num = string_system(arr_string[finish]),
        check_num = string_system(check);

    if ( (check_num > finish_num) || (check_num < start_num) )
    {
        cout << "\nИнтерполирующий поиск ничего не нашел.";
        return;
    }

    while ( (start_num <= check_num) && (check_num <= finish_num ) )
    {
        int i = start + (check_num - start_num) * ((finish - start) / (finish_num - start_num));

        int string_num = string_system(arr_string[i]);
        if (string_num == check_num) { break; }

        if (string_num > check_num)
        {
            finish = i - 1;
            finish_num = string_system(arr_string[finish]);
        }
        else
        {
            start = i + 1;
            start_num = string_system(arr_string[start]);
        }
    }

    //if ( arr_string[start] == check )
        //cout << "\nИнтерполирующий поиск: " << arr_string[start + 1];
    //else
        //cout << "\nИнтерполирующий поиск: " << arr_string[start];
}

int main()
{
    setlocale(LC_ALL, "");
    ifstream ist("scbb2.txt");
    if (!ist.is_open()) return 0;

    string check; vector<string> arr_string;
    size_t n = 0;
    ist >> n;
    for (size_t i = 0; i < n; i++)
    {
        ist >> check;
        arr_string.push_back(check);
    }

    cout << "Введите элемент поиска: ";
    cin >> check;

    cout << "Сортировка...";
    sort(arr_string.begin(), arr_string.end(), wayToSort);
    cout << "\nСортировка закончена.";

    //linear_search(arr_string, check);
    
    cout << time_checker(linear_search, arr_string, check) << " мс";
    //binary_search(arr_string, check);
    cout << time_checker(interpolating_search, arr_string, check) << " мс";
    //interpolating_search(arr_string, check);

    return 0;
}