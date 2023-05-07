// Вариант 3, на 100%
#include <iostream>

using namespace std;

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

void print_array(int *arr, int len)
{
    int *arr_temp = arr;
    for (int i = 0; i < len; i++)
        cout << '\n' << i+1 << " element array equal " << *arr++;
}

bool check_num(int *arr, int x, int len)
{
    int c = 0;
    for (int i = 0; i < len; i++)
        if (arr[i] == x)
            c++;
    if (c == 0)
        return true;
    else
        return false;
}

 void sort(int *arr, int len, bool asc)
 {
    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if ((arr[i] > arr[j]) && (asc == true))
                swap(arr[i], arr[j]);
            else if ((arr[i] < arr[j]) && (asc == false))
                swap(arr[i], arr[j]);
        }
    }
 }

int main()
{
    int len = 0;
    int *arr = 0;
    bool asc;
    int lenC = 0;

    cout << "Enter lenght: ";
    cin >> len;

    if (len <= 0)
        return 0;
    else
    {
        cout << "Type of order array.\nEnter 1 if direct/0 if reverse: ";
        cin >> asc;

        int *A = new int [len];
        int *B = new int [len];

        A = read_array(len);
        B = read_array(len);

        for (int i = 0; i < len; i++)
        {
            if (check_num(A, B[i], len))
            {
                int c = 0;
                for (int j = 0; j < i; j++)
                    if(B[j]==B[i])
                        c++;
                if (c == 0)
                    lenC++;
            }
        }
        int *C = new int [lenC];
        int k = 0;
        for (int i = 0; i < len; i++)
        {
            if (check_num(A, B[i], len))
            {
                int c = 0;
                for (int j = 0; j < i; j++)
                    if (B[i] == B[j])
                        c++;
                if (c == 0)
                {
                    C[k] = B[i];
                    k++;
                }
            }
        }

        cout << "\nInitial array";
        print_array(C, lenC);
        sort (C, lenC, asc);
        cout << "\nSorted array";
        print_array(C, lenC);

        delete [] A;
        delete [] B;
        delete [] C;
        delete [] arr;
    }

    return 0;
}
