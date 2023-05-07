#include <iostream>
#include <iomanip> 
#include <fstream>
#include <vector>
#include "omp.h"

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::setw;

void print_array(int** arr, int n, int k)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            cout << setw(5) << arr[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

void print_array_txt(ofstream& ost, int** arr, int n, int k)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            ost << setw(5) << arr[i][j];
        }
        ost << '\n';
    }
    ost << '\n';
}

int** fill_array(std::ifstream& file, int n, int k, int step)
{
    int** arr = new int* [n];
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = new int[k];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if ((i == 0) || (i == n - step) || (j == 0) || (j == k - step))
            {
                arr[i][j] = 0;
            }
            else
                file >> arr[i][j];
        }
    }

    return arr;
}

int** fill_cores(std::ifstream& file, int n)
{
    int** core = new int* [n];
    for (size_t i = 0; i < n; i++)
    {
        core[i] = new int[n];
        for (size_t j = 0; j < n; j++)
        {
            file >> core[i][j];
        }
    }
    return core;
}

void fill_maps_zeros(vector<int**>& maps, int count_maps, int n, int k, int mode)
{
    if (!mode)
    {
        for (size_t i = 0; i < count_maps; i++)
        {
            int** arr = new int* [n];
            for (size_t j = 0; j < n; j++)
            {
                arr[j] = new int[k];
                for (size_t l = 0; l < k; l++)
                {
                    arr[j][l] = 0;
                }
            }
            maps.push_back(arr);
        }
    }
    else
    {
        for (size_t i = 0; i < count_maps; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                for (size_t l = 0; l < k; l++)
                {
                    maps.at(i)[j][l] = 0;
                }
            }
        }
    }

}

void release_array(int** arr, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

void bundle_array(int** arr, int** arr_, int** core, int n, int k, int size_core)
{
    int tmp_sum = 0;
    for (size_t i = 0; i < size_core; i++)
    {
        for (size_t j = 0; j < size_core; j++)
        {
            tmp_sum += arr[i + n][j + k] * core[i][j];
        }
    }
    arr_[n][k] = tmp_sum;

}

int main() {
    int n, k;

    ifstream file_array("input_array4.txt");
    file_array >> n;
    file_array >> k;

    ifstream file_cores("input_cores.txt");
    int count_core, size_core;
    file_cores >> count_core;
    file_cores >> size_core;

    int step = (size_core - 1) / 2;
    n = n + step * 2;
    k = k + step * 2;

    int** arr = fill_array(file_array, n, k, step);
    cout << "Finish! Array was writed\n";
    file_array.close();

    vector <int**> cores;
    for (size_t i = 0; i < count_core; i++)
    {
        int** core = fill_cores(file_cores, count_core);
        cores.push_back(core);
    }
    file_cores.close();
    cout << "Finish! Cores was writed\n";

    vector <int**> maps;
    fill_maps_zeros(maps, count_core + 1, n, k, 0);

    cout << "Program ready to work\n";

    int flag;
    cout << "\nOutput res (0 - no, 1 - yes)? ";
    cin >> flag;

    int threads;
    cout << "\nEnter count of threads (enter -1 to exit from program): ";
    cin >> threads;

    double start, stop, duration;

    while (threads > 0)
    {
        if (threads == 1)
        {
            start = omp_get_wtime();

            for (int i = 0 + step; i < n - step; i++)
            {
                for (int j = 0 + step; j < k - step; j++)
                {
                    for (int l = 0; l < count_core; l++)
                    {
                        bundle_array(arr, maps.at(l), cores.at(l), i - step, j - step, size_core);
                    }
                }
            }
            for (size_t i = 0; i < n; i++)
            {
                for (size_t j = 0; j < k; j++)
                {
                    for (int l = 0; l < count_core; l++)
                    {
                        maps.back()[i][j] += maps.at(l)[i][j];
                    }
                }
            }
        }
        else
        {
            int chunk = n / threads;
            omp_set_num_threads(threads);
            start = omp_get_wtime();
#pragma omp parallel
            {
#pragma omp for
                for (int i = 0 + step; i < n - step; i++)
                {
                    for (int j = 0 + step; j < k - step; j++)
                    {
                        for (int l = 0; l < count_core; l++)
                        {
                            bundle_array(arr, maps[l], cores[l], i - step, j - step, size_core);
                        }
                    }
                }
#pragma omp for
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < k; j++)
                    {
                        for (int l = 0; l < count_core; l++)
                        {
                            maps.back()[i][j] += maps.at(l)[i][j];
                        }
                    }
                }
            }
        }
        stop = omp_get_wtime();
        duration = stop - start;

        if (flag)
        {
            ofstream ost("output_array.txt");
            // ofstream ost1("output_array1.txt");
            // ofstream ost2("output_array2.txt");
            // ofstream ost3("output_array3.txt");
            print_array_txt(ost, arr, n, k);
            // print_array_txt(ost1, maps[1], n, k);
            // print_array_txt(ost2, maps[2], n, k);
            // print_array_txt(ost3, maps[3], n, k);
            ost.close();
            // ost1.close();
            // ost2.close();
            // ost3.close();
        }

        cout << "Time start: " << start << ", time end: " << stop << ", duration: " << duration;

        fill_maps_zeros(maps, count_core + 1, n, k, 1);

        cout << "\n\nEnter count of threads (enter -1 to exit from program): ";
        cin >> threads;
    }

    release_array(arr, n);
    for (size_t i = 0; i < count_core; i++)
    {
        release_array(cores[i], size_core);
        release_array(maps[i], n);
    }
    release_array(maps.back(), n);

    return 0;
}