#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "omp.h"

using std::cout;
using std::cin;
using std::ofstream;
using std::ostream;

struct Node
{
	double data;
	Node* next;
};
class List
{
	Node* head;
	Node* last;
	int size;
public:
	List() :head(NULL), last(NULL), size(0) {};

	// Добавление элемента в список
	void AddList(double value)
	{
		Node* temp = new Node;
		temp->next = head;
		temp->data = value;
		if (head != NULL)
		{
			last->next = temp;
			last = temp;
		}
		else  
			head = last = temp;
	}

	// Удаление списка
	void DeleteList()
	{
		Node* temp = head;
		while (head->next != NULL)
		{
			temp = head->next;
			delete[] head;
			head = temp;
		}
		delete[] head;
		delete[] temp;
	}

	// Вывод списка
	void PrintList(ostream& ost)
	{
		if (head == NULL)
		{
			ost << "Список пуст";
		}
		else
		{
			Node *tmp = head;
			do
			{
				cout << "(" << tmp->data << ") -> ";
				tmp = tmp->next;
			} while (tmp != head); 
			cout << "\nКонец цикла";
		}
	}
};

int main()
{
	while (true)
	{
		srand(time(nullptr));
		setlocale(LC_ALL, "");

		double min = -1, max = 1;
		long N;
		int k, flag, g;
		double start, end;

		cout << "Введите размер массива: ";
		cin >> N;

		if (N < 0)
			break;

		cout << "Введите количество потоков: ";
		cin >> k;

		cout << "Число интервалов гистограммы: ";
		cin >> g;

		cout << "Выберите режим вывода: 0 - нет, 1 - консоль, 2 - файл:\n>> ";
		cin >> flag;

		long double* arr = new long double[N];
		List list;
		int* hist_counter = new int[g];

		if (flag == 0)
		{
			// Инициализация массива
			//cout << "Исходный массив: " << '\n';
			for (int i = 0; i < N; i++)
				arr[i] = ((float)rand() / RAND_MAX) * 2 - 1;

			// Задание 1. Элементы массива с четными номерами
			cout << "\nПервое задание. Вывод элементов с четными номерами." << '\n';

			start = omp_get_wtime();
#pragma omp parallel num_threads(k)
			{
#pragma omp for
				for (int i = 0; i < N; i = i + 2)
				{
#pragma omp critical
					 cout << "Поток №" << omp_get_thread_num() << ": arr[" << i << "] = " << arr[i] << '\n';
				}
			}
			end = omp_get_wtime();
			cout << "\nВремя выполнения первого задания: " << end - start;

			// Задание 2. Создание массива из элементов массива, значения которых меньше значения предыдущего элемента.
			// Вид списка: Кольцевой список
			cout << "\nВторое задание. Массив из значений, меньше предыдущего." << '\n';

			
			start = omp_get_wtime();
#pragma omp parallel num_threads(k)
			{
#pragma omp for
				for (int i = 1; i < N; i++)
				{
					if (arr[i] < arr[i - 1])
					{
#pragma omp critical
						{
							list.AddList(arr[i]);
						}
					}
				}
			}
			end = omp_get_wtime();
			// list.PrintList(cout);
			cout << "\nВремя выполнения второго задания: " << end - start << '\n';

			// Задание 3. Гистограмма распределения массива в области [-1, 1]
			cout << "\nТретье задание. Гистограмма распределения массива в области [-1, 1]" << '\n';

			double chunk_hist = (max - min) / g;
			int indent = ceil(g / (max - min)) - 1;

#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < g; i++)
				{
					hist_counter[i] = 0;
				}
			}

			start = omp_get_wtime();
#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < N; i++)
				{
					int index_hist = ceil(arr[i] / chunk_hist + indent);
					if (index_hist >= g)
						index_hist = g - 1;
#pragma omp atomic
					hist_counter[index_hist]++;
				}
			}
			end = omp_get_wtime();

			double step = -1;
			int i = 0;
			while (step < 1 - step)
			{
				cout << "Интервал [" << step << ", " << step + chunk_hist << "] : " << hist_counter[i] << " число элементов" << '\n';
				step += chunk_hist;
				i++;
			}
			cout << "Интервал [" << step << ", 1" << "] : " << hist_counter[i] << " число элементов" << '\n';
			cout << "\nВремя выполнения второго задания: " << end - start << '\n';
		}
		else
		{
			ofstream ost("result.txt");

			// Инициализация массива
			cout << "Исходный массив: " << '\n';
			for (int i = 0; i < N; i++)
			{
				arr[i] = ((float)rand() / RAND_MAX) * 2 - 1;

				if (flag == 1)
					cout << "arr[" << i << "] = " << arr[i] << '\n';
			}

			// Вывод в консоль или файл (flag == 1 || flag == 2)
			if (flag != 0)
			{
				for (int i = 0; i < N; i++)
				{
					if (flag == 1)
						cout << "arr[" << i << "] = " << arr[i] << '\n';
					else
						ost << "arr[" << i << "] = " << arr[i] << '\n';
				}

			}

			// Задание 1. Элементы массива с четными номерами
			cout << "\nПервое задание. Вывод элементов с четными номерами." << '\n';
			if (flag == 2)
				ost << "\nПервое задание. Вывод элементов с четными номерами." << '\n';

			start = omp_get_wtime();
	#pragma omp parallel num_threads(k)
			{
	#pragma omp for
				for (int i = 0; i < N; i = i + 2)
				{
					if (flag == 1)
					{
	#pragma omp critical
						cout << "Поток №" << omp_get_thread_num() << ": arr[" << i << "] = " << arr[i] << '\n';
					}
					else if (flag == 2)
					{
	#pragma omp critical
						ost << "Поток №" << omp_get_thread_num() << ": arr[" << i << "] = " << arr[i] << '\n';
					}
				}
			}
			end = omp_get_wtime();
			cout << "\nВремя выполнения первого задания: " << end - start;
			if (flag == 2)
				ost << "\nВремя выполнения первого задания: " << end - start;

			// Задание 2. Создание массива из элементов массива, значения которых меньше значения предыдущего элемента.
			// Вид списка: Кольцевой список
			cout << "\nВторое задание. Массив из значений, меньше предыдущего." << '\n';
			if (flag == 2)
				ost << "\nВторое задание. Массив из значений, меньше предыдущего." << '\n';

			start = omp_get_wtime();
	#pragma omp parallel num_threads(k)
			{
	#pragma omp for
				for (int i = 1; i < N; i++)
				{
					if (arr[i] < arr[i - 1])
					{
	#pragma omp critical
						{
							list.AddList(arr[i]);
						}
					}
				}
			}
			end = omp_get_wtime();
			cout << "\nВремя выполнения второго задания: " << end - start << '\n';
			if (flag == 2)
				ost << "\nВремя выполнения второго задания: " << end - start << '\n';


			//if (flag == 1)
				//list.PrintList(cout);
			//else if (flag == 2)
				//list.PrintList(ost);


			// Задание 3. Гистограмма распределения массива в области [-1, 1]
			cout << "\nТретье задание. Гистограмма распределения массива в области [-1, 1]" << '\n';
			if (flag == 2)
				ost << "\nТретье задание. Гистограмма распределения массива в области [-1, 1]" << '\n';

			double chunk_hist = (max - min) / g;
			int indent = ceil(g / (max - min)) - 1;

#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < g; i++)
				{
					hist_counter[i] = 0;
				}
			}

			start = omp_get_wtime();
#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < N; i++)
				{
					int index_hist = ceil(arr[i] / chunk_hist + indent);
					if (index_hist >= g)
						index_hist = g - 1;
#pragma omp atomic
					hist_counter[index_hist]++;
				}
			}
			end = omp_get_wtime();

			double step = -1;
			int i = 0;
			if (flag == 1)
			{
				while (step < 1 - step * 2)
				{
					cout << "Интервал [" << step << ", " << step + chunk_hist << "[ : " << hist_counter[i] << " число элементов" << '\n';
					step += chunk_hist;
					i++;
				}
				cout << "Интервал [" << step << ", 1" << "] : " << hist_counter[i] << " число элементов" << '\n';
				
			}
			else if (flag == 2)
			{
				while (step < 1 - step * 2)
				{
					ost << "Интервал [" << step << ", " << step + chunk_hist << "[ : " << hist_counter[i] << " число элементов" << '\n';
					step += chunk_hist;
					i++;
				}
				ost << "Интервал [" << step << ", 1" << "] : " << hist_counter[i] << " число элементов" << '\n';
				ost << "\nВремя выполнения второго задания: " << end - start << '\n';
			}
			cout << "\nВремя выполнения второго задания: " << end - start << '\n';
		}
	}
}