#include <iostream>
#include <fstream>

using namespace std;

void fliplr(int **arr, size_t nrows, size_t ncols)
{
    int c = 0;
    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < (ncols/2); j++)
        {
            c = arr[i][j];
            arr[i][j] = arr[i][ncols-1-j];
            arr[i][ncols-1-j] = c;
        }
    }
}

void print_fliplr(const int * const *arr, size_t nrows, size_t ncols, std::ostream &ost)
{
    ost << "Changed array: \n";
    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
        {
            ost << arr[i][j] << ' ';
        }
        ost << '\n';
    }
}

int main ()
{
    ofstream ost("out2.txt", ios::out); 
    size_t nrows;
    cout << "Enter number rows: ";
    cin >> nrows;
    if (nrows <= 0)
    {
        ost << "\nNegative value.";
        return 0;
    }

    size_t ncols;
    cout << "Enter number cols: ";
    cin >> ncols;
    if (ncols <= 0)
    {
        ost << "\nNegative value.";
        return 0;
    }

    int **arr = new int* [nrows];
    for (size_t i = 0; i < nrows; i++)
        arr[i] = new int [ncols];

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
        {
            cout << "Enter element of array " << i+1 << " row " << j+1 << " collumn: ";
            cin >> arr[i][j];
        }
    }

    fliplr(arr, nrows, ncols);
    print_fliplr(arr, nrows, ncols, ost);
    ost.close();

    for (size_t i = 0; i < nrows; i++)
        delete [] arr[i];
    delete [] arr;
    return 0;
}
