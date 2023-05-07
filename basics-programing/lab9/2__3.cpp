#include <iostream>

using namespace std;

void print_array(int *arr, int len)
{
    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
        cout << i+1 << " element array equal " << *arr++ << endl;
}

int search_min_element(int *arr, int len)
{
    int min_number = arr[0];

    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
    {
        if (*arr_temp++ < min_number)
            min_number = *arr_temp;
    }

    return min_number;
}

int my_task(int *A, int lenA, int *B, int lenB)
{
    int min_number = search_min_element(A, lenA);

    int *A_temp = A;
    int *B_temp = B;

    for (int i = 0; i < lenA; i++)
    {
        if (*A_temp != min_number)
        {
            *B_temp = *A_temp;
            B_temp++;
        }
        A_temp++;
    }

    return *B;
}

int *read_array(int len)
{
    int *arr = new int [len];

    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
    {
        cout << "Enter number " << i+1 << " array: ";
        cin >> *arr_temp++;
    }

    return arr;
}

int main()
{
    int len = 0, *arr = 0, min_number = 0;

    cout << "Enter N: ";
    cin >> len;

    if (len <= 0)
        return 0;

    arr = read_array(len);

    print_array(arr, len);

    min_number = search_min_element(arr, len);

    int lenA = len;
    int lenB = len;

    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
    {
        if (*arr_temp++ == min_number)
            lenB--;
    }

    int *A = new int [lenA];
    int *B = new int [lenB];

    A = arr;

    *B = my_task(A, lenA, B, lenB);

    print_array(B, lenB);

    delete [] A;
    delete [] B;
    delete [] arr;

    return 0;
}
