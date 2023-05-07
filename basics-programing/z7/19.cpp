 #include <iostream>

using namespace std;

void print_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "Enter number " << i+1 << " array: \n";
        cin >> arr[i];
    }

    for (int i = 0; i < len; i++)
        cout << '\n' << arr[i];
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

        delete [] arr;
    }

    else
        cout << "Lenght can't be negative or zero";

    return 0;
}
