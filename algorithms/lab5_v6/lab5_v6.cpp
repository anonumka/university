#include <iostream>

using namespace std;

int correct(int* arr, int len)
{
    while (len-- > 0)
        if (arr[len - 1] > arr[len])
            return 0;
    return 1;
}

void shuffle(int* arr, int len)
{
    for (int i = 0; i < len; ++i)
        std::swap(arr[i], arr[(rand() % len)]);
}

void bogoSort(int* arr, int len) {
    while (!correct(arr, len))
        shuffle(arr, len);
}

void shell_sort(int* arr, int len)
{
    for (int s = len / 2; s > 0; s /= 2)
    {
        for (int i = s; i < len; ++i)
        {
            for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s)
            {
                swap(arr[j], arr[j + s]);
            }
        }
    }
}

void quickSort(int* numbers, int left, int right)
{
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}

void print_array(int* arr, int len)
{
    for (size_t i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void fill_array(int* arr, int* arr1, int* arr2, int len)
{
    for (size_t i = 0; i < len; i++)
    {
        arr[i] = rand() % 256;
        arr1[i] = arr[i];
        arr2[i] = arr[i];
    }
        
}

int main()
{
    setlocale(LC_ALL, "");
    for (size_t i = 10; i < 100000; i*=10)
    {
        int* arr = new int[i];
        int* arr1 = new int[i];
        int* arr2 = new int[i];
        fill_array(arr, arr1, arr2, i);
        cout << "Исходный массив: " << endl;
        print_array(arr, i);

        //Сортировка Шелла
        cout << "\nСортировка Шелла: " << endl;
        shell_sort(arr2, i);
        print_array(arr2, i);

        //Быстрая сортировка
        cout << "\nБыстрая сортировка: " << endl;
        quickSort(arr, 0, i - 1);
        print_array(arr, i);

        //Сортировка Богосорт
        cout << "\nСортировка Богосорт: " << endl;
        bogoSort(arr1, i);
        print_array(arr1, i);

        delete[] arr;
        delete[] arr1;
        delete[] arr2;
    }
}