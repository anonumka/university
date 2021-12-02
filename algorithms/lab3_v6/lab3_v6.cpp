#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

void SearchCloseElement(int* arr, int len, int search_num)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == search_num)
        {
            cout << "Searching element: " << arr[i] << endl;
            return;
        }
    }
    cout << "Search element not finded." << endl;
}

void Search_Binary(int* arr, int len, int search_num)
{
    int midd = 0;
    int left = 0;
    int right = len - 1;
    if (len == 1 && search_num == arr[0])
    {
        cout << "Only one element in array and searching element is that element";
        return;
    }
    while (left <= right)
    {
        midd = (left + right) / 2;

        if (search_num < arr[midd])
            right = midd - 1;
        else if (search_num > arr[midd])
            left = midd + 1;
        else
        {
            cout << "Searching element: " << arr[midd] << endl;
            return;
        }
    }
    cout << "Search element not finded." << endl;
}

void interpolSearch(int* arr, int len, int search_num)
{
    int midd = 0;
    int left = 0;
    int temp;
    int right = len - 1;
    int lefttemp = 0, righttemp = 0;
    if (len == 1 && search_num == arr[0])
    {
        cout << "Only one element in array and searching element is that element";
        return;
    }
    while (left <= right)
    {
        midd = left + (search_num - arr[left]) * ((right - left) / (arr[right] - arr[left]));

        if (search_num < arr[midd])
            right = midd - 1;
        else if (search_num > arr[midd])
            left = midd + 1;
        else
        {
            cout << "Searching element: " << arr[midd] << endl;
            return;
        }
    }
    cout << "Search element not finded.";
}

int cmpfunc(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    int length, search_num;
    ifstream ist("in.txt");

    //cout << "Enter the length of the array: ";
    ist >> length;

    while (length <= 0)
    {
        cout << "length of the array can not be less than zero!\nEnter the length of the array: ";
        ist >> length;
    }

    int* array = new int[length];

    for (int i = 0; i < length; i++) { ist >> array[i]; }

    cout << "Enter the number you want to search for: ";
    cin >> search_num;

    qsort(array, length, sizeof(int), cmpfunc);
    Search_Binary(array, length, search_num);
    SearchCloseElement(array, length, search_num);
    interpolSearch(array, length, search_num);
}