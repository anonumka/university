#include <iostream>
#include <iomanip> 
#include <fstream>
#include <vector>
#include "mpi.h"
#include "omp.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::setw;

void print_array(int** arr, int n, int k)
{
    ofstream ost("res.txt");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            ost << setw(5) << arr[i][j];
        }
        ost << '\n';
    }
    ost << '\n';
    ost.close();
}

void fill_array(std::ifstream& file, int** arr, int n, int k, int step)
{
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
}

void fill_cores(std::ifstream& file, int** core, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            file >> core[i][j];
        }
    }
}

void fill_maps_zeros(int** maps, int n, int k)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            maps[i][j] = 0;
        }
    }

}

// Функция по освобождению памяти двумерного массива
void release_array(int*** arr)
{
    free(&((*arr)[0][0]));

    /* free the pointers into the memory */
    free(*arr);
}

// Функция, в которой происходит процесс свертки
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

// Функция, которая создает двумерный массив, нужный для передачи между процессами
void malloc2dint(int*** array, int n, int m)
{
    int* p = (int*)malloc(n * m * sizeof(int));

    (*array) = (int**)malloc(n * sizeof(int*));
    if (!(*array)) {
        free(p);
    }

    for (int i = 0; i < n; i++)
        (*array)[i] = &(p[i * m]);

}

int main()
{
    /* Инициализация */
    MPI_Init(NULL, NULL);
    int rank, size; // номер и количество процессов

    double start, stop; // переменные, в которых будут хранится время начала и конца

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n, k; // размерность входного массива
    int step; // шаг ядра
    int count_core, size_core; // количество и размер ядра (ядер)

    /* В первый процесс записывается размерность входного массива, ядра (ядер) и 
       высчитывается шаг */
    if (rank == 0) 
    {
        ifstream file_array("input_array1_1.txt");
        file_array >> n;
        file_array >> k;
        file_array.close();

        ifstream file_cores("input_cores.txt");
        file_cores >> count_core;
        file_cores >> size_core;

        step = (size_core - 1) / 2;
        n = n + step * 2;
        k = k + step * 2;

        file_cores.close();
    }

    // Полученные значения рассылаются остальным процессам
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&step, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&count_core, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_core, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // arr - основной массив, по которому проходятся ядром (ядрами)
    int** arr;
    malloc2dint(&arr, n, k);

    // cores - вектор с ядрами
    vector <int**> cores;
    for (int i = 0; i < count_core; i++)
    {
        int** core;
        malloc2dint(&core, size_core, size_core);
        cores.push_back(core);
    }

    // maps - вектор с результатами каждого ядра
    vector <int**> maps;
    for (int i = 0; i < count_core + 1; i++)
    {
        int** map;
        malloc2dint(&map, n, k);
        fill_maps_zeros(map, n, k);
        maps.push_back(map);
    }

    // считываем значения из файлов
    if (rank == 0)
    {
        ifstream file_cores("input_cores.txt");
        file_cores >> count_core;
        file_cores >> size_core;

        ifstream file_array("input_array1_1.txt");
        file_array >> n;
        file_array >> k;

        step = (size_core - 1) / 2;
        n = n + step * 2;
        k = k + step * 2;

        for (size_t i = 0; i < count_core; i++)
        {
            fill_cores(file_cores, cores[i], count_core);
        }
        file_cores.close();
        cout << "Finish! Cores was writed\n";

        fill_array(file_array, arr, n, k, step);
        file_array.close();
        cout << "Finish! Array was writed\n";

        cout << "Program ready to work\n";
        start = omp_get_wtime();
    }

    /* Передача данных процессам */
    MPI_Bcast(&(arr[0][0]), n * k, MPI_INT, 0, MPI_COMM_WORLD); // Передача основного массива    
    for (int i = 0; i < count_core; i++) // Передача ядер процессам
        MPI_Bcast(&((cores[i])[0][0]), size_core * size_core, MPI_INT, 0, MPI_COMM_WORLD);

    /* Начинается отсчет времени */
    if (rank == 0)
    {
        start = omp_get_wtime();
    }

    /* Разделение строк по количеству процессов */
    int chunk = n / size;
    int begin = rank * chunk;
    if (rank == 0)
        begin = 0 + step;
    int end = (rank + 1) * chunk;
    if (rank == size - 1)
        end = n - step - 1;

    /* Вычисления */
    // Каждое ядро проходится по каждому элементу массива
    for (int i = begin; i <= end; i++)
    {
        for (int j = 0 + step; j < k - step; j++)
        {
            for (int l = 0; l < count_core; l++)
            {
                bundle_array(arr, maps[l], cores[l], i - step, j - step, size_core);
            }
        }
    }

    // Сумма пройденных ядер
    for (int i = begin; i < end; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int l = 0; l < count_core; l++)
            {
                maps.back()[i][j] += maps.at(l)[i][j];
            }
        }
    }

    /* Сбор вычислений в первый процесс */
    if (rank != 0) // Если не первый процесс, то отправить вычисленные значения
    {
        if (rank == size - 1)
            end = n;

        for (int i = begin; i < end; i++)
            MPI_Send(maps.back()[i], k, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }
    else // Если первый, то собрать значения с других процессов
    {
        for (int i = 1; i < size; i++)
        {
            chunk = n / size;
            begin = i * chunk;
            end = (i + 1) * chunk;
            if (i == size - 1)
                end = n;

            for (int j = begin; j < end; j++)
                MPI_Recv(maps.back()[j], k, MPI_INT, i, 99, MPI_COMM_WORLD, &status);
        }
    }

    /* Вывод информации */
    if (rank == 0)
    {
        stop = omp_get_wtime();
        cout << "Time duration: " << stop - start << '\n';

        bool flag = false;
        cout << "Output res (0 - no, 1 - yes)\n>> "; cin >> flag;
        if (flag)
            print_array(maps.back(), n, k);
    }

    /* Очистка памяти */
    release_array(&arr);
    for (size_t i = 0; i < count_core; i++)
    {
        release_array(&cores[i]);
        release_array(&maps[i]);
    }
    release_array(&maps.back());

    /* Завершение работы процессора */
    MPI_Finalize();
}