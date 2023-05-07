/*
* Лабораторная работа №15
* Тема: Двоичные файлы
* Выполнил: Анциферов Д. А.
* Группа: КИ20-06б
* Вариант: 3
* Задание:  Считать исходный текстовый файл,
*           в котором первые два числа размер матрицы,
*           а остальные - матрица вида NxM вида, и записать
*           в другой двоичный файл, оформить как отдельную
*           функцию и следом, работая с этим двоичным файлом
*           проверить, расположены ли элементы в порядке возрастания.
*           Если да, определить, встречается ли значение k в этой строке,
*           используя алгоритм двоичного поиска, оформив как новую функцию
*
*/

#include <iostream>
#include <fstream>


using std::cin;
using std::cout;
using std::ios;
using std::ios_base;
using std::ifstream;

/*
* Функция для преобразования текста в отедльный двоичный файл
* Параметры:
* ist - входной текстовый файл
* ost - двоичный файл на выходе
*/

void text2bin(std::istream& ist, std::ofstream& ost)
{
    ist.seekg(ios_base::beg);
    int n, m, tmp; // n и m - размер массива, tmp - временная переменная
    ist >> n >> m;
    ost.write((char*)(&n), sizeof(int)); ost.write((char*)(&m), sizeof(int));
    cout << "Reading 'in.txt' and convert to binary file...\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            ist >> tmp;
            ost.write((char*)&tmp, sizeof(int));
        }
    cout << "File succeful converting to binary file!\n";
}

/*
* Функция для считывания двоичного файла в одномерный массив и
* проверка на возрастание и совпадение числа и массива
* Параметры:
* ist - входной двоичный файл
*/

void my_task(std::istream& ist)
{
    int n = 0, m = 0;
    ist.read((char*)&n, sizeof(int));
    ist.read((char*)&m, sizeof(int));
    int size = n * m;
    bool c = true; bool equal = false; bool check = true;
    // c - это проверка четности, equal - это проверка на равенство, check - проверка на k<=n
    int k;
    cout << "Enter number which will be check for a match: ";
    cin >> k;
    if ((k > n) || (k < 0)) check = false;
    int* a = new int[size];
    int i = 0;
    while (ist.read((char*)(&a[i]), sizeof(int))) i++;
    for (int j = m * (k - 1) + 1; j < m * k; j++)
    {
        if (a[j - 1] == a[j])
            c = false;
        if ((a[j - 1] == k) || (a[j] == k))
            equal = true;
    }
    if (!check)
        cout << "Wrong number!\nNumber should be < or = n (" << n << ")";
    else if (!c)
        cout << "Numbers don't increase"; // числа не возрастают
    else if (equal)
        cout << "Coincidence"; // совпадение
    else
        cout << "Numbers increase but not coincidence"; // возрастание без совпадения
}

int main()
{
    cout << "Welcome to laboratory work N15\n";
    cout << "Wait. The program checks the data.\n";
    ifstream ist("in.txt");
    if (!ist.is_open()) // проверка на наличие файла
    {
        cout << "The program terminated with errors.\nFailed open a file.";
        return 0;
    }
    cout << "File 'in.txt' successfully opened\n";
    int n, m;
    ist >> n >> m;
    if ((n <= 0) || (m <= 0)) // проверка на правильность введенных данных
    {
        cout << "Someone variables '<' or '=' 0!\nn = " << n << ", m = " << m;
        return 0;
    }
    cout << "The variables are entered correctly!\n";
    std::ofstream ost("in.bin", ios::binary);
    text2bin(ist, ost);
    ist.close(); ost.close();
    ifstream ist_new("in.bin", ios::binary);
    my_task(ist_new);
    return 0;
}
