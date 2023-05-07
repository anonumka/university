#include <iostream>

using namespace std;

int splice_array(int *arr1, int *arr2, int len, int *arr_out)
{

    int *arr1_temp = arr1;
    int *arr2_temp = arr2;

    for (int i = 0; i < len; i++, arr1_temp++)
    {
        cout << "Enter number " << i+1 << " first array: \n";
        cin >> *arr1_temp;
    }

    cout << endl;

    for (int i = 0; i < len; i++, arr2_temp++)
    {
        cout << "Enter number " << i+1 << " second array: \n";
        cin >> *arr2_temp;
    }

    for (int i = 0; i < len*2; i+=2, arr1++, arr2++)
    {
        *arr_out = *arr1;
        arr_out++;
        *arr_out = *arr2;
        arr_out++;
    }

    return len*2;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len, f = 0, len2;

    cout << "Enter length of array: ";
    cin >> len;

    if (len > 0)
    {
        int *arr1 = new int [len];
        int *arr2 = new int [len];
        int *arr_out = new int [len*2];

         len2 = splice_array(arr1, arr2, len, arr_out);

        for (int i = 0; i < len2; i++, arr_out++)
            cout << *arr_out << ' ';

        delete arr1;
        delete arr2;
        delete arr_out;
    }

    else
        cout << "Lenght can't be negative or zero";

    return 0;
}
