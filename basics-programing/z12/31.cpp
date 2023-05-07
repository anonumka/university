#include <iostream>
#include <fstream>

using namespace std;

void print2d(const int * const *arr, size_t nrows, size_t ncols, std::ostream &ost)
{
    ost << "Matrix equal: \n";
    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
        {
            ost << arr[i][j] << ' ';
        }
        ost << '\n';
    }
}

int **make2d(size_t nrows, size_t ncols, int val)
{
    int **arr = new int* [nrows];
    for (size_t i = 0; i < nrows; i++)
        arr[i] = new int [ncols];
    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
        {
            arr[i][j] = val;
        }
    }
    return arr;
}

int main ()
{
    ofstream ost("out1.txt", ios::out);
    size_t nrows;
    cout << "Enter number rows: ";
    cin >> nrows;
    if (nrows <= 0)
    {
        cout << "\nNegative value.";
        return 0;
    }
    size_t ncols;
    cout << "Enter number cols: ";
    cin >> ncols;
    if (ncols <= 0)
    {
        cout << "\nNegative value.";
        return 0;
    }
    int val;
    cout << "Enter value elements: ";
    cin >> val;
    int **arr = make2d(nrows, ncols, val);

    print2d(arr, nrows, ncols, ost);
    ost.close();

    for (size_t i = 0; i < nrows; i++)
        delete [] arr[i];
    delete [] arr;
    return 0;
}
