#include<iostream>
#include<clocale>
using namespace std;

int zeros(int A)
{
    int sum_of_zeros = 0;
    while (A > 0)
    {
        if (A % 10 == 0)
        {
            sum_of_zeros++;
        }
        A /= 10;
    }
    return sum_of_zeros;
}

void search_for_zeros(int A[], int B[], int lenA, int lenB)
{
    for (int i = 0; i < lenA; i++)
    {
        B[i] = zeros(A[i]);
    }
}

int* read_array(int len)
{
    int* A = new int[len];
    int* arr = A;
    for (int i = 0; i < len; i++)
    {
        cout << "Введите " << i + 1 << " элемент массива: ";
        cin >> *arr;
        arr++;
    }
    return A;

}

void print_array(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}

void sort(int* arr, int len, bool asc)
{
    int temp;
    for (int i = 1, k; i < len; ++i)
    {
        temp = arr[i];
        for (k = i - 1; k >= 0 && ((arr[k] > temp && asc) || (arr[k] < temp && !asc)); --k)
        {
            arr[k + 1] = arr[k];
        }
        arr[k + 1] = temp;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int  lenA, lenB, len, N;
    bool asc;
    cout << "Введите длину массивa: ";
    cin >> len;
    lenB = len;
    lenA = len;
    int* A = read_array(len);
    int* B = new int[lenB];
    cout << "\nМассив B: ";
    search_for_zeros(A, B, lenA, lenB);
    print_array(B, lenB);
    cout << "\n1=true, 0=false." << endl << " Сортировка массива B длины lenB по возрастанию, если asc = true, и по убыванию, если asc = false "
        <<"Введите asc: ";
    cin >> asc;
    sort(B, lenB, asc);
    cout << "Массив B: ";
    print_array(B, lenB);
    delete[] A;
    delete[] B;
    return 0;
}