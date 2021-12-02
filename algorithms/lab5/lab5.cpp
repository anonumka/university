#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void createDownLayer(int* arr, int root, int bottom)
{
	int maxChild;
	bool stop = false;
	while ((root * 2 <= bottom) && (!stop))
	{
		if (root * 2 == bottom)
			maxChild = root * 2;
		else if (arr[root * 2] > arr[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		if (arr[root] < arr[maxChild])
		{
			swap(arr[root], arr[maxChild]);
			root = maxChild;
		}
		else
			stop = true;
	}
}

void sorting_heap(int* arr, size_t len)
{
	for (int i = (len / 2) - 1; i >= 0; i--)
		createDownLayer(arr, i, len);
	for (int i = len - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);
		createDownLayer(arr, 0, i - 1);
	}
}

void merge(int* arr, int left, int right, int mid)
{
	if (left >= right || mid < left || mid > right) return;
	if (right == left + 1 && arr[left] > arr[right]) {
		swap(arr[left], arr[right]);
		return;
	}
	int* tmp = new int[right - left + 1];
	for (int i = left, j = 0; i <= right; i++, j++)
		tmp[j] = arr[i];
	for (int i = left, j = 0, k = mid - left + 1; i <= right; i++) {
		if (j > mid - left)
			arr[i] = tmp[k++];
		else if (k > right - left)
			arr[i] = tmp[j++];
		else
		{
			if (tmp[j] < tmp[k])
				arr[i] = tmp[j++];
			else
				arr[i] = tmp[k++];
		}
	}
}

void mergerSort(int* arr, int left, int right)
{
	if (left >= right) return;
	int mid = (left + right) / 2;
	mergerSort(arr, left, mid);
	mergerSort(arr, mid + 1, right);
	merge(arr, left, right, mid);
}


void stupid_sorting(int* arr , int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			swap(arr[i], arr[i + 1]);
			i = -1;
		}
	}
}

int generate_number()
{
	int n = rand() % 256 + 1;
	return n;
}

void fill_array(int* arr1, int* arr2, int* arr3, int n)
{
	for (int i = 0; i < n; i++)
	{
		arr1[i] = generate_number();
		arr3[i] = arr2[i] = arr1[i];
	}
}

void print_array(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main()
{
    setlocale(LC_ALL, "");

	for (int i = 500; i <= 10000; i += 500)
	{
		int* arr1 = new int[i];
		int* arr2 = new int[i];
		int* arr3 = new int[i];

		fill_array(arr1, arr2, arr3, i);

		cout << "---------------------------\n";
		cout << "Исходный массив состоит из " << i << " элементов.\n";

		auto t1 = high_resolution_clock::now();
		stupid_sorting(arr1, i);
		auto t2 = high_resolution_clock::now();
		float res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
		cout << "Глупая сортировка заняла " << res << " мс.\n";

		t1 = high_resolution_clock::now();
		sorting_heap(arr2, i);
		t2 = high_resolution_clock::now();
		res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
		cout << "Cортировка кучей заняла " << res << " мс.\n";

		t1 = high_resolution_clock::now();
		mergerSort(arr3, 0, i - 1);
		t2 = high_resolution_clock::now();
		res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
		cout << "Cортировка слиянием заняла " << res << " мс.\n";

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
	}
}