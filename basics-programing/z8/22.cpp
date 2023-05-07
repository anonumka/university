 #include <iostream>

using namespace std;

void print_array(int *arr, int len)
{
    int *arr_temp = arr;

    for (int i = 0; i < len; i++, arr_temp++)
    {
        cout << "Enter number " << i+1 << " array: ";
        cin >> *arr_temp;
    }

    for (int i = 0; i < len; i++)
        cout << '\n' << *arr++;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len;

    cout << "Enter length of array: ";
    cin >> len;

    if (len > 0)
    {
        int *arr = new int [len];

        print_array(arr, len);

        delete arr;
    }

    else
        cout << "Lenght can't be negative or zero";

    return 0;
}
