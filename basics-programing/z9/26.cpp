#include <iostream>
using namespace std;

void sort(int arr[], int len, bool even_greater)
{
    int tmp;

    for (int i = 0; i < len; i++)
    {
        cout << "Enter " << i+1 << " element array: ";
        cin >> arr[i];
    }


    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if ( ((arr[i]%2)==1) && ((arr[j]%2)==1) && (arr[i] > arr[j]) ||
                 ((arr[i]%2)==0) && ((arr[j]%2)==0) && (arr[i] > arr[j]) ||
                 ((arr[i]%2)==1) && ((arr[j]%2)==0) && (even_greater == true) || 
                 ((arr[i]%2)==0) && ((arr[j]%2)==1) && (even_greater == false))
                swap (arr[i], arr[j]);
        }
    }


    for (int i = 0; i < len; i++)
        cout << '\n' << arr[i];
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len;
    bool even_greater;

    cout << "Enter length of array: ";
    cin >> len;
    cout << "Multiples two or 1? 1/0: ";
    cin >> even_greater;

    if (len > 0)
    {
        int *arr = new int [len];
        sort(arr, len, even_greater);
        delete [] arr;
    }
    else
        cout << "Lenght cant be zero or negative";

    return 0;
}
