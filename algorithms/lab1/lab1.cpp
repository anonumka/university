#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

float time_checker(bool(*func)(string a, string b), string a, string b)
{
    auto t1 = high_resolution_clock::now();

    bool res = func(a, b);

    auto t2 = high_resolution_clock::now();

    cout << std::boolalpha << res << " ";

    return duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
}

bool is_subseq1(string a, string b)
{
    int max = a.length(), min = b.length(), j = 0;

    for (int i = 0; i < max; i++)
    {
        if (a[i] == b[j])
        {
            j++;
            if (j == min) return true;
        }
    }
    return false;
}

bool is_subseq2(string a, string b)
{
    int a_len = a.length(), b_len = b.length(), count = 0;

    for (int i = 0; i < b_len; i++)
    {
        for (int j = 0; j < a.length(); j++)
        {
            if (a[j] == b[i])
            {
                count++; string c;
                for (int k = 0; k < a_len; k++)
                {
                    if (k != j) c.push_back(a[k]);
                }
                a = c;
                break;
            }
        }
    }

    return count == b_len;
}

int main()
{
    setlocale(LC_ALL, "");
    string a, b;
    ifstream ist("in.txt");

    for (size_t i = 1; i <= 11; i++)
    {
        ist >> a; ist >> b;
        if (a.length() < b.length()) swap(a, b);
        cout << "----------------";
        cout << "Итерация: " << i << endl;
        cout << "Первая строка: "; cout << a << endl;
        cout << "Вторая строка: "; cout << b << endl;
        cout << "Входит ли одна в другую в качестве подпоследовательности? " << endl;
        cout << "выдала первая функция, а время " << time_checker(is_subseq1, a, b) << " мс" << endl;
        cout << "выдала вторая функция, а время " << time_checker(is_subseq2, a, b) << " мс" << endl;
    }

    return 0;
}