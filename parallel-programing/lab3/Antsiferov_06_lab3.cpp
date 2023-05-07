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

int** fill_array_convolutional(std::ifstream& file, int n, int k, int step)
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

int** fill_array_polling(int n, int k)
{
    int** arr = new int* [n];
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = new int[k];
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

void pooling_array(int** arr, int** arr_, int n, int k, int w, int h)
{
    int max = INT_MIN;
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (arr[n + i][k + j] > max)
                max = arr[n + i][k + j];
        }
    }
    arr_[w][h] = max;
}

int main() {
    
    setlocale(LC_ALL, "");
    
    int n, k;

    ifstream file_array("input_array6.txt");
    file_array >> n;
    file_array >> k;

    // Инициализация переменных для Pooling(p)
    int n_p = (n % 4 == 0) ? n / 2 : ((4 - n % 4) + n) / 2;
    int k_p = (k % 4 == 0) ? k / 2 : ((4 - k % 4) + k) / 2;
    int** arr2 = fill_array_polling(n_p, k_p);

    // Инициализация переменных для свертки
    ifstream file_cores("input_cores.txt");
    int count_core, size_core;
    file_cores >> count_core;
    file_cores >> size_core;

    int step = (size_core - 1) / 2;
    n = n + step * 2;
    k = k + step * 2;

    int** arr = fill_array_convolutional(file_array, n, k, step);
    cout << "Файл с входным массивом считан\n";
    file_array.close();

    vector <int**> cores;
    for (size_t i = 0; i < count_core; i++)
    {
        int** core = fill_cores(file_cores, count_core);
        cores.push_back(core);
    }
    file_cores.close();
    cout << "Файл с ядрами считан\n";

    vector <int**> maps;
    fill_maps_zeros(maps, count_core + 1, n, k, 0);

    cout << "Программа готова к работе\n";

    int flag;
    cout << "\nВывод результата (0 - no, 1 - yes)? ";
    cin >> flag;

    int threads;
    cout << "\nВведите количество потоков (введите отрицательные значения для завершения работы программы): ";
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
                        bundle_array(arr, maps[l], cores[l], i - step, j - step, size_core);
                    }
                }
            }
            for (int i = 0; i < n_p; i++)
            {
                for (int j = 0; j < k_p; j++)
                {
                    if ((((i + i) + 1) < n) && (((j + j) + 1) < k))
                    {
                        pooling_array(arr, arr2, i + i, j + j, i, j);
                    }
                }
            }
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
        else
        {
#pragma omp parallel sections num_threads(threads)
            {
                start = omp_get_wtime();
#pragma omp section
                {
                    int cur_thread = omp_get_thread_num();
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
                }
#pragma omp section
                {
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
#pragma omp section
                {
                    for (int i = 0; i < n_p; i++)
                    {
                        for (int j = 0; j < k_p; j++)
                        {
                            if ((((i + i) + 1) < n) && (((j + j) + 1) < k))
                            {
                                pooling_array(arr, arr2, i + i, j + j, i, j);
                            }
                        }
                    }
                }
            }
        }

        stop = omp_get_wtime();
        duration = stop - start;

        if (flag)
        {
            ofstream ost("output_convolutional.txt");
            ofstream ost1("output_podding.txt");
            print_array_txt(ost, arr, n, k);
            print_array_txt(ost1, arr2, n_p, k_p);
            ost1.close();
        }

        cout << "Разница: " << duration;

        fill_maps_zeros(maps, count_core + 1, n, k, 1);

        cout << "\nВведите количество потоков (введите отрицательные. значения для завершения работы программы): ";
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