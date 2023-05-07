#include <iostream>
using namespace std;

void sort(float arr[], int len, bool asc)
{
    float tmp;

    for (int i = 0; i < len; i++)
    {
        cout << "Enter " << i+1 << " element array:: ";
        cin >> arr[i];
    }

    for (int i = 0; i < len-1; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    if (asc == true)
        for (int i = 0; i < len; i++)
            cout << '\n' << arr[i];
    else
        for (int i = len-1; i >= 0; i--)
            cout << '\n' << arr[i];

}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len;
    bool asc;

    cout << "Enter length of array: ";
    cin >> len;
    cout << "Don't reverse array? 1 if yes/0 if nope: ";
    cin >> asc;

    if (len > 0)
    {
        float *arr = new float [len];
        sort(arr, len, asc);
        delete [] arr;
    }
    else
        cout << "Length cant be zero or negative";

    return 0;
}
