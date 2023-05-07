#include <iostream>

using namespace std;

int main ()
{
    setlocale (LC_ALL, ".1251");

    float n;
    unsigned long int s = 0;
    cout << "¬ведите натуральное число: ";
    cin >> n;

    if ( ( n > 0 ) && ( n == int(n) ))
    {
        for (int i = 1; i <= n; i++)
        {
            s+=i;
        }

        cout << s << " ";

        s = ((2 + n - 1) / 2) * n;
        cout << s << " ";

        s = 1;

        for (int i = 1; i <= n; i++)
        {
            s *= i;
        }

        cout << s << " ";
    }

    else
    {
        cout << "¬веденное число не €вл€етс€ натуральным";
    }

    return 0;
}
