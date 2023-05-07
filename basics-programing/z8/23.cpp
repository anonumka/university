#include <iostream>

using namespace std;

int count_equal(int *arr, int len, int x)
{
    int c = 0;

    for (int i = 0; i < len; i++, arr++)
    {
        cout << "Enter number " << i+1 << " array: \n";
        cin >> *arr;
        if (*arr == x)
            c++;

    }

    return c;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len, x = 0;

    cout << "Enter length of array: ";
    cin >> len;

    cout << "Number which compare : ";
    cin >> x;

    if (len > 0)
    {
        int *arr = new int [len];

        cout << "Number of coincidences: " << count_equal(arr, len, x);

        delete arr;
    }

    else
        cout << "Lenght can't be negative or zero";

    return 0;
}
