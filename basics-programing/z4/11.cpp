#include <iostream>

using namespace std;

void print_diag(int s)
{
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << "*\n";
    }
}

int main ()
{
    setlocale(LC_ALL, ".1251");

    int64_t s = 0;
    cout << "¬ведите количество звездочек: ";
    cin >> s;

    if (s > 0)
        print_diag(s);
    else
        cout << "¬веденное число меньше или равно нулю.";

    return 0;
}
