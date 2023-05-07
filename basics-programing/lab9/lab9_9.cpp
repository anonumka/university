//Вариант 9, задание на 100%
#include <iostream>

using namespace std;

void print_array(int *arr, int len)
{
    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
        cout << i+1 << " element array equal " << *arr++ << endl;
}

int search_first_negative_element(int arr[], int len)
{
    int negative_number_index = -1;

    int *arr_temp = arr;

    for (int i = 0; i < len; i++)
    {
        if (*arr_temp++ < 0)
            return i;
    }
    return negative_number_index;
}

int my_task(int *A, int lenA, int *B, int lenB)
{
    int negative_number_index = search_first_negative_element(A, lenA);
    if (negative_number_index == -1)
        return *A;
    
    int *A_temp = A;
    int *B_temp = B;

    // for (int i = 0; i < lenA; i++)
    // {
    //     if (*A_temp != min_number)
    //     {
    //         *B_temp = *A_temp;
    //         B_temp++;
    //     }
    //     A_temp++;
    // }

    for (int i = 0; i < lenA; i++)
    {
        if ( *A_temp == 0 && i < negative_number_index )
            *B_temp = 1;
        else
            *B_temp = *A_temp;
        A_temp++;
        B_temp++;
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
    int len = 0;

    cout << "Enter N: ";
    cin >> len;

    if (len <= 0)
        return 0;
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
