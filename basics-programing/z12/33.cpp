#include <iostream>
#include <fstream>

using namespace std;

void transpose(int **arr, size_t size)
{
    int c = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < (size/2); j++)
        {
            c = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = c;
        }
    }
}

void print_transposed(const int * const *arr, size_t size, std::ostream &ost)
{
    ost << "Changed array: \n";
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            ost << arr[i][j] << ' ';
        }
        ost << '\n';
    }
}

int main ()
{
    ofstream ost("out3.txt", ios::out); 
    size_t size;
    cout << "Enter number size: ";
    cin >> size;
    if (size <= 0)
    {
        ost << "\nNegative value.";
        return 0;
    }

    int **arr = new int* [size];
    for (size_t i = 0; i < size; i++)
        arr[i] = new int [size];

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            cout << "Enter element of array " << i+1 << " row " << j+1 << " collumn: ";
            cin >> arr[i][j];
        }
    }

    transpose(arr, size);
    print_transposed(arr, size, ost);
    ost.close();
    
    for (size_t i = 0; i < size; i++)
        delete [] arr[i];
    delete [] arr;
    return 0;
}
