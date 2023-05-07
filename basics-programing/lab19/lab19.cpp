// 19 лабораторная, 3 вариант, 100%
#include <iostream>
#include <fstream>

using std::cout;
using std::istream;

void print_array(int** arr, int n, int m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            cout << arr[i][j] << " ";
        cout << '\n';
    }
}

int count_obj(int** arr, int n, int m, int cur_n, int cur_m, int count)
{
    if (cur_n + 1 < n)
        if (arr[cur_n + 1][cur_m] == 1)
        {
            arr[cur_n][cur_m] = 2;
            arr[cur_n + 1][cur_m] = 2;
            count = count_obj(arr, n, m, cur_n + 1, cur_m, count + 1);
        }
    if (cur_m + 1 < m)
        if (arr[cur_n][cur_m + 1] == 1)
        {
            arr[cur_n][cur_m] = 2;
            arr[cur_n][cur_m + 1] = 2;
            count = count_obj(arr, n, m, cur_n, cur_m + 1, count + 1);
        }
    if (cur_n - 1 >= 0)
        if (arr[cur_n - 1][cur_m] == 1)
        {
            arr[cur_n][cur_m] = 2;
            arr[cur_n - 1][cur_m] = 2;
            count = count_obj(arr, n, m, cur_n - 1, cur_m, count + 1);
        }
    if (cur_m - 1 >= 0)
        if (arr[cur_n][cur_m - 1] == 1)
        {
            arr[cur_n][cur_m] = 2;
            arr[cur_n][cur_m - 1] = 2;
            count = count_obj(arr, n, m, cur_n, cur_m - 1, count + 1);
        }
    arr[cur_n][cur_m] = 0;
    return count;
}

int check_count_obj(int** arr, int n, int m)
{
    int count = 0;
    int tmp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j])
            {
                tmp = count_obj(arr, n, m, i, j, 0);
                if (tmp) count++;
            }
        }
    return count;
}

int** read_array(istream& ist, int n, int m)
{
    int** arr = new int* [n];
    bool tmp; // временная переменная
    for (int i = 0; i < n; i++) arr[i] = new int[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (ist >> tmp)
                arr[i][j] = tmp;
            else
            {
                arr = NULL;
                break;
            }
    if (!ist.eof())
        arr = NULL;
    return arr;
}

void remove_array(int** arr, int n, int m)
{
    for (size_t i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}

int main()
{
    setlocale(LC_ALL, "");
    std::ifstream ist("in.txt");
    if (!ist.is_open())
    {
        cout << "Произошла ошибка.\nНевозможно открыть файл.";
        return 0;
    }
    int n; int m;
    ist >> n; ist >> m;
    if (n < 0 || m < 0)
    {
        cout << "Количество строк или столбцов '<' или '=' 0";
        return 0;
    }
    int** arr = read_array(ist, n, m);
    if (arr == NULL)
    {
        cout << "Неправильно задан размер матрицы или используются числа кроме '0' и '1'.";
        return 0;
    }
    print_array(arr, n, m);
    int res = check_count_obj(arr, n, m);
    cout << "Количество объектов: " << res;
    remove_array(arr, n, m);
    return 0;
}