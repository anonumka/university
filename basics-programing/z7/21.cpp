#include <iostream>

using namespace std;

int splice_array(int arr1[], int arr2[], int len, int arr_out[])
{

    for (int i = 0; i < len; i++)
    {
        cout << "Enter number " << i+1 << " first array: \n";
        cin >> arr1[i];
    }

    cout << endl;

    for (int i = 0; i < len; i++)
    {
        cout << "Enter number " << i+1 << " second array: \n";
        cin >> arr2[i];
    }

    for (int i = 0; i < len*2; i+=2)
    {
        arr_out[i] = arr1[i/2];
        arr_out[i+1] = arr2[i/2];
    }

        return *arr_out;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len, f = 0;

    cout << "Enter length of array: ";
    cin >> len;

    if (len > 0)
    {
        int *arr1 = new int [len];
        int *arr2 = new int [len];
        int *arr_out = new int [len*2];

        *arr_out = splice_array(arr1, arr2, len, arr_out);

        for (int i = 0; i < len*2; i++)
            cout << arr_out[i] << ' ';

        delete [] arr1;
        delete [] arr2;
        delete [] arr_out;
    }

    else
        cout << "Lenght can't be negative or zero";

    return 0;
}
