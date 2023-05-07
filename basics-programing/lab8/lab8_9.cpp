//Вариант 9, задание на 100%
#include <iostream>

using namespace std;

void print_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        cout << i+1 << " element array equal " << arr[i] << endl;
}

int search_first_negative_element(int arr[], int len)
{
    int negative_number_index = -1;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0)
            return i;
    }
    return negative_number_index;
}

int my_task(int A[], int lenA, int B[], int lenB)
{
    int negative_number_index = search_first_negative_element(A, lenA);
    if (negative_number_index == -1)
        return *A;
    for (int i = 0; i < lenA; i++)
    {
        if ( A[i] == 0 && i < negative_number_index )
            B[i] = 1;
        else
            B[i] = A[i];
    }
    return *B;
}

int *read_array(int len)
{
    int *arr = new int [len];

    for (int i = 0; i < len; i++)
    {
        cout << "Enter number " << i+1 << " array: ";
        cin >> arr[i];
    }

    return arr;
}

int main()
{
    int len = 0, min_number = 0;

    cout << "Enter N: ";
    cin >> len;

    if (len <= 0)
    {
        cout << "\nLen should be '>' 0.";
        return 0;
    }

    int *A = new int [len];
    A = read_array(len);
    print_array(A, len);

    int *B = new int [len];
    *B = my_task(A, len, B, len);
    print_array(B, len);

    delete [] A;
    delete [] B;

    return 0;
}
