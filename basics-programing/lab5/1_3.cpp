#include<iostream>

using namespace std;

string check_num(int n)
{
    unsigned long s = 0, tmp_n = 0, tmp = 0;

    tmp_n = n;
    while ( tmp_n > 0 )
    {
        tmp_n /= 10;
        s++;
    }

    tmp = n*n;
    tmp_n = 1;

    for (int i = 0; i < s; i++)
    {
        tmp_n*=10;
    }

    if ((tmp %= tmp_n) == n)
        return "Да";
    else
        return "Нет";
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int64_t n = 0;

    cout << "Введите число: ";
    cin >> n;

    if (n > 0)
        cout << "Автоморфно число? " << check_num(n) << "\n";
    else
        cout << "Введенное число меньше или равен нулю\n";

    return 0;
}
