#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
#include "omp.h"

using std::cout;
using std::cin;

int main()
{
	setlocale(LC_ALL, "");
	int N, k; // Размер массива и количество потоков
	float x; // Элемент массива
	double start, stop, duration; // Переменные для опредения времени выполнения

	cout << "Введите размер массива: "; 
	cin >> N;
	while (N != 0)
	{
		cout << "Введите элемент массива: "; 
		cin >> x;
		cout << "Введите количество потоков: "; 
		cin >> k;

		float* a = new float[N];
		float* b = new float[N];
		float* c = new float[N];

		a[0] = x;
		b[0] = 1.0 / x;

		// out << "a[" << 0 << "] = " << a[0] << '\n';
		// out << "b[" << 0 << "] = " << b[0] << '\n';

		if (k == 1)
		{
			start = omp_get_wtime();
			// Инициализация массивов
			for (int i = 1; i < N; i++)
			{
				a[i] = sin(x * i) + x * x / i;
				b[i] = (b[i - 1] + x) / i;
			}

			// Вычисления
			for (int i = 0; i < N; i++)
			{
				c[i] = a[i] - b[N - i - 1];
				// out << "c[" << i << "] = " << c[i] << '\n';
			}

			for (int i = 0; i < N; i++)
			{
				b[i] = (a[i] + c[i]) / 2;
				// out << "b[" << i << "] = " << b[i] << '\n';
			}
		}
		else
		{
			int chunk = N / ( k - 1);
			omp_set_num_threads(k);
			start = omp_get_wtime();
			// Инициализация массивов
			#pragma omp parallel
			{
				int cur_thread = omp_get_thread_num();
				if (k - 1 != cur_thread)
				{
					int begin = cur_thread * chunk;
					if (cur_thread == 0)
						begin = 1;

					int end = (cur_thread + 1) * chunk;
					if (cur_thread == k - 2)
						end = N;

					for (int i = begin; i < end; i++)
					{
						a[i] = sin(x * i) + x * x / i;
						// out << "a[" << i << "] = " << a[i] << '\n';
					}
				}
				else
				{
					for (int i = 1; i < N; i++)
					{
						b[i] = (b[i - 1] + x) / (i * 1.0);
					}
				}
				/*#pragma omp critical
				{
					cout << "Параллельная секция 1. Поток: " << cur_thread
						<< " Начало с: " << (cur_thread * chunk) + 1
						<< " Конец: " << (cur_thread + 1) * chunk << '\n';
				}*/
			}
			chunk = N \ k;
			// Вычисления
			#pragma omp parallel
			{
				int cur_thread = omp_get_thread_num();
				int end = (cur_thread + 1) * chunk;
				if (k - 1 == cur_thread)
					end = N;

				for (int i = cur_thread * chunk; i < end; i++)
				{
					c[i] = a[i] - b[N - i - 1];
				}
				/*#pragma omp critical
				{
					cout << "Параллельная секция 2. Поток: " << cur_thread
						<< " Начало с: " << (cur_thread * chunk) + 1
						<< " Конец: " << (cur_thread + 1) * chunk << '\n';
				}*/
			}

			#pragma omp parallel
			{
				int cur_thread = omp_get_thread_num();
				int end = chunk * (cur_thread + 1);
				if (k - 1 == cur_thread)
					end = N;

				for (int i = cur_thread * chunk; i < end; i++)
				{
					b[i] = (a[i] + c[i]) / 2;
				}
				/*#pragma omp critical
				{
					cout << "Параллельная секция 3. Поток: " << cur_thread
						<< " Начало с: " << (cur_thread * chunk) + 1
						<< " Конец: " << (cur_thread + 1) * chunk << '\n';
				}*/
			}
		}
		stop = omp_get_wtime();
		duration = stop - start;

		cout << "\nНачало в: " << start
			<< " Конец в: " << stop
			<< " Разница: " << duration << '\n';

		delete[] a;
		delete[] b;
		delete[] c;

		cout << "\nВведите размер массива: "; 
		cin >> N;
	}
	return 0;
}